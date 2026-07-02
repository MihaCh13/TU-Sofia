-- Подадена така заявката ще върне грешка "Error Code: 1451. Cannot delete or update a parent row", тъй като липсва каскадно изтриване (ON DELETE CASCADE). 
-- Това предпазва базата данни от създаване на "осиротели" записи.

-- Опит за изтриване на сграда, в която има апартаменти
DELETE FROM Buildings WHERE Building_ID = 10;

-- =============================================================
-- Създаваме централизирана одитна таблица за проследяване на добавяне, изтриване и редактиране на записи. Тя няма външни ключове, за да съхранява независима и защитена история на промените.
-- =============================================================

CREATE TABLE IF NOT EXISTS Buildings_Audit_Log (
    Log_ID INT AUTO_INCREMENT PRIMARY KEY,
    Building_ID INT NOT NULL,
    City VARCHAR(100) NOT NULL,
    Address VARCHAR(255) NOT NULL,
    Action_Type ENUM('INSERTED', 'DELETED', 'UPDATED') NOT NULL,
    Action_Date TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    Action_By VARCHAR(100) NOT NULL
);

SELECT * FROM buildings_audit_log;
-- =========================================================================
-- Създаване на тригер за управление на грешки и архивиране (BEFORE DELETE)
-- Логика: За да избегнем неразбираемата системна грешка (Error 1451) при опит за изтриване на сграда с прилежащи апартаменти, създаваме този тригер. Той прихваща събитието "изтриване" и първо проверява дали сградата е празна. Ако открие свързани записи, тригерът блокира операцията и връща наше персонализирано съобщение (Custom Exception). В случай че сградата е празна, тригерът автоматично запазва данните ѝ в архивната таблица (Buildings_Archive).
-- =========================================================================

DELIMITER //

-- Премахваме старата версия на тригера (ако съществува), за да я презапишем чисто
DROP TRIGGER IF EXISTS before_building_delete //

CREATE TRIGGER before_building_delete
BEFORE DELETE ON Buildings
FOR EACH ROW
BEGIN
    -- Декларираме локална променлива, в която ще съхраним броя на апартаментите
    DECLARE apt_count INT;

    -- 1. Изчисляваме броя на апартаментите, свързани със сградата, която предстои да бъде изтрита (достъпваме нейното ID чрез OLD.Building_ID)и записваме резултата в променливата apt_count.
    SELECT COUNT(*) INTO apt_count 
    FROM Apartments 
    WHERE Building_ID = OLD.Building_ID;

    -- 2. Валидация (управление на изключения): Ако има апартаменти, спираме операцията със свое съобщение
    IF apt_count > 0 THEN
        SIGNAL SQLSTATE '45000' -- Стандар в MySQL за "Потребителско изключение" (User-defined Exception)
        SET MESSAGE_TEXT = 'ОТКАЗАН ДОСТЪП: Не можеш да изтриеш тази сграда, защото в нея все още има регистрирани апартаменти!';
    
    -- 3. Архивиране: Ако е празна, правим запис в одитната таблица преди изтриването
    ELSE
        -- Функцията USER() автоматично взима името на администратора, пуснал заявката
        INSERT INTO Buildings_Audit_Log (Building_ID, City, Address, Action_Type, Action_By)
        VALUES (OLD.Building_ID, OLD.City, OLD.Address, 'DELETED', USER());
    END IF;
    
END //

DELIMITER ;

-- ТЕСТ НА ТРИГЕРА: Благодарение на тригера, при изпълнение на тази заявка вече няма да получим системна грешка, 
-- а нашето персонализирано съобщение за отказан достъп.
DELETE FROM Buildings WHERE Building_ID = 10;

-- Тест на успешно изтриване и запис в одитната таблица
-- =========================================================================

-- 1. Добавяме нова "празна" сграда (към нея няма вързани апартаменти)
INSERT INTO Buildings (City, Address, Building_Num, Entrance, User_ID) 
VALUES ('Sofia', 'jk. Manastirski Livadi', '105A', '9', 2);

-- 2. Изтриваме току-що създадената сграда. 
-- Тригерът ще позволи операцията и ще запише данните в Buildings_Audit_Log.
DELETE FROM Buildings 
WHERE Address = 'jk. Manastirski Livadi';

-- 3. Извеждаме одитната таблица, за да докажем, че архивирането работи успешно!
SELECT 
    Log_ID AS 'ID на запис',
    Building_ID AS 'ID на изтрита сграда',
    City AS 'Град',
    Address AS 'Адрес',
    Action_Type AS 'Действие',
    DATE_FORMAT(Action_Date, '%d.%m.%Y %H:%i:%s') AS 'Дата и час',
    Action_By AS 'Извършено от'
FROM Buildings_Audit_Log;
-- ---------------------------------------------------------------------------------------------------------------

-- ====================================================================================================================
-- =============================================================
-- Създаваме AFTER INSERT тригер, с който демонстрираме работата с модификатора NEW.
-- Използваме събитието AFTER, за да имаме достъп до вече генерираното от базата данни ID.
-- Чрез NEW прехвърляме данните от новия запис директно в одитната таблица.
-- =============================================================

DELIMITER //

DROP TRIGGER IF EXISTS after_building_insert //

CREATE TRIGGER after_building_insert
AFTER INSERT ON Buildings
FOR EACH ROW
BEGIN
    -- Вмъкваме данните от току-що създадения запис в одит лога.
    -- Модификаторът NEW ни дава достъп до новите стойности (ID, град и адрес).
    INSERT INTO Buildings_Audit_Log (Building_ID, City, Address, Action_Type, Action_By)
    VALUES (NEW.Building_ID, NEW.City, NEW.Address, 'INSERTED', USER());
END //

DELIMITER ;

-- ТЕСТ: Проверка дали при вмъкване на сграда данните се отразяват в одит лога.
INSERT INTO Buildings (City, Address, Building_Num, Entrance, User_ID) 
VALUES ('Varna', 'ul. Studentska', '100', 'A', 2);

-- Резултатът трябва да покаже новата сграда със статус 'INSERTED'
SELECT * FROM Buildings_Audit_Log;

-- =============================================================
-- Създаваме AFTER UPDATE тригер за проследяване на редакции.
-- Използваме събитието AFTER, за да гарантираме, че промяната е успешна.
-- Чрез модификатора NEW записваме обновените данни на сградата в одит лога.
-- =============================================================

DELIMITER //

DROP TRIGGER IF EXISTS after_building_update //

CREATE TRIGGER after_building_update
AFTER UPDATE ON Buildings
FOR EACH ROW
BEGIN
    -- Вмъкваме новите стойности (след редакцията) в одит лога и задаваме статус 'UPDATED'.
    INSERT INTO Buildings_Audit_Log (Building_ID, City, Address, Action_Type, Action_By)
    VALUES (NEW.Building_ID, NEW.City, NEW.Address, 'UPDATED', USER());
END //

DELIMITER ;

-- =============================================================
-- ТЕСТ: Променяме адреса на съществуваща сграда (например Сграда №1).
-- ОЧАКВАН РЕЗУЛТАТ: Базата ще обнови адреса успешно (няма да има грешки). 
-- Тригерът автоматично ще създаде нов ред в Buildings_Audit_Log със статус 'UPDATED'.
-- =============================================================


-- 1. Редактираме адреса на сградата, която създадохме при теста на INSERT тригера.
UPDATE Buildings 
SET Address = 'ul. Pirotska № 14,' 
WHERE City = 'Varna' AND Address = 'ul. Studentska';

-- 2. Проверяваме одит лога, за да видим историята на промените.
SELECT * FROM Buildings_Audit_Log;


-- Списък на всички активни тригери в базата данни
SHOW TRIGGERS;


