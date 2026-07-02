-- 1. Създаване на базата данни
CREATE DATABASE IF NOT EXISTS CompanyDB;
USE CompanyDB;

-- 2. Създаване на таблица employees
CREATE TABLE employees (
    id INT PRIMARY KEY AUTO_INCREMENT,
    name VARCHAR(100) NOT NULL,
    salary DECIMAL(10, 2) NOT NULL,
    position VARCHAR(50),
    created_at DATETIME DEFAULT CURRENT_TIMESTAMP
);

-- 3. Създаване на таблица work_hours
CREATE TABLE work_hours (
    id INT PRIMARY KEY AUTO_INCREMENT,
    employee_id INT,
    hours_worked INT NOT NULL,
    work_date DATE NOT NULL,
    FOREIGN KEY (employee_id) REFERENCES employees(id) ON DELETE CASCADE
);

-- 4. Създаване на таблица salary_log
CREATE TABLE salary_log (
    id INT PRIMARY KEY AUTO_INCREMENT,
    employee_id INT,
    old_salary DECIMAL(10, 2),
    new_salary DECIMAL(10, 2),
    changed_at DATETIME DEFAULT CURRENT_TIMESTAMP
);

-- =============================================================================================================

-- 1. Въвеждане на данни в таблица employees
INSERT INTO employees (name, salary, position, created_at) VALUES 
('Иван Петров', 2200.50, 'Backend Developer', NOW()),
('Мария Георгиева', 1900.00, 'QA Engineer', NOW()),
('Елена Димитрова', 3500.00, 'Project Manager', NOW()),
('Николай Колев', 1500.00, 'Junior Developer', NOW());

-- 2. Въвеждане на данни в таблица work_hours
-- (employee_id съответства на ID-тата от горната таблица)
INSERT INTO work_hours (employee_id, hours_worked, work_date) VALUES 
(1, 8, '2023-10-01'),
(1, 7, '2023-10-02'),
(2, 8, '2023-10-01'),
(2, 9, '2023-10-02'),
(3, 8, '2023-10-01'),
(4, 4, '2023-10-01');

-- 3. Въвеждане на данни в таблица salary_log
-- (Тук обикновено се пази история на промените)
INSERT INTO salary_log (employee_id, old_salary, new_salary, changed_at) VALUES 
(1, 2000.00, 2200.50, '2023-09-15 10:30:00'),
(2, 1800.00, 1900.00, '2023-09-20 11:00:00'),
(3, 3200.00, 3500.00, '2023-09-25 09:15:00');

-- ================================================================================================

-- Бърза проверка на вкарана информация
SELECT 'Служители' AS TableName, COUNT(*) FROM employees
UNION ALL
SELECT 'Отработени часове', COUNT(*) FROM work_hours
UNION ALL
SELECT 'Лог на заплати', COUNT(*) FROM salary_log;

-- ==================================================================================================

DELIMITER //

-- Създаване на тригера
CREATE TRIGGER before_employee_insert
BEFORE INSERT ON employees
FOR EACH ROW
BEGIN
    -- Проверява дали created_at е празно или задава текущото време при всеки нов запис
    IF NEW.created_at IS NULL THEN
        SET NEW.created_at = NOW();
    END IF;
END //

DELIMITER ;

-- Вмъкваме служител само с име, заплата и позиция
INSERT INTO employees (name, salary, position) 
VALUES ('Георги Петров', 2100.00, 'Support');

-- Проверяваме дали датата е попълнена автоматично
SELECT name, created_at FROM employees WHERE name = 'Георги Петров';

-- ===========================================================================================================

DELIMITER //

CREATE TRIGGER after_work_hours_insert
AFTER INSERT ON work_hours
FOR EACH ROW
BEGIN
    DECLARE total_hours INT;

    -- 1. Изчисляваме сумата на часовете за служителя за текущия месец и година
    SELECT SUM(hours_worked) INTO total_hours
    FROM work_hours
    WHERE employee_id = NEW.employee_id 
      AND MONTH(work_date) = MONTH(CURRENT_DATE())
      AND YEAR(work_date) = YEAR(CURRENT_DATE());

    -- 2. Проверяваме дали часовете надвишават 160
    IF total_hours > 160 THEN
        -- 3. Увеличаваме заплатата на служителя с 10%
        UPDATE employees 
        SET salary = salary * 1.10
        WHERE id = NEW.employee_id;
    END IF;
END //

DELIMITER ;

-- Приемаме, че служител с ID 1 има 155 часа до момента
-- Добавяме още 10 часа (общо 165)
INSERT INTO work_hours (employee_id, hours_worked, work_date) 
VALUES (1, 10, CURRENT_DATE());

-- Проверяваме дали заплатата се е вдигнала
SELECT name, salary FROM employees WHERE id = 1;

-- ==================================================================================

-- Изтриваме тригера, ако случайно вече съществува
DROP TRIGGER IF EXISTS save_old_salary_before_update;

DELIMITER //

-- Създаваме тригера с НОВО ИМЕ
CREATE TRIGGER save_old_salary_before_update
BEFORE UPDATE ON employees
FOR EACH ROW
BEGIN
    -- Проверяваме дали заплатата се променя
    IF OLD.salary <> NEW.salary THEN
        -- Записваме старата стойност в променливата
        SET @old_salary_value = OLD.salary;
    END IF;
END //

DELIMITER ;

-- 1. Изключваме Safe Updates, за да е всичко точно
SET SQL_SAFE_UPDATES = 0;

-- 2. Променяме заплатата на служител с ID 7 на 3500.00
UPDATE employees 
SET salary = 3500.00 
WHERE id = 7;

-- 3. ИЗВИКВАМЕ променливата, за да видим какво е запомнил тригерът!
SELECT @old_salary_value AS Zapomnenata_Stara_Zaplata;

-- ======================================================================================================

-- Изтриваме тригера, ако случайно вече съществува
DROP TRIGGER IF EXISTS log_salary_after_update;

DELIMITER //

CREATE TRIGGER log_salary_after_update
AFTER UPDATE ON employees
FOR EACH ROW
BEGIN
    -- Проверяваме дали имаме записана стара стойност в променливата и дали тя е различна от новата
    IF @old_salary_value IS NOT NULL AND @old_salary_value <> NEW.salary THEN
        
        -- Вмъкваме данните в лог таблицата
        INSERT INTO salary_log (employee_id, old_salary, new_salary, changed_at)
        VALUES (NEW.id, @old_salary_value, NEW.salary, NOW());
        
        -- Изчистваме променливата след като сме я използвали, за да е готова за следващ ъпдейт
        SET @old_salary_value = NULL;
        
    END IF;
END //

DELIMITER ;

-- 1. Сменяме заплатата на Петър (ID 7) на 4000.00
UPDATE employees 
SET salary = 4000.00 
WHERE id = 7;

-- 2. Проверяваме лог таблицата, за да видим дали тригерът е записал историята!
SELECT * FROM salary_log WHERE employee_id = 7;

-- =============================================================================================

-- Изтриваме тригера, ако случайно вече съществува
DROP TRIGGER IF EXISTS before_employee_delete;

DELIMITER //

CREATE TRIGGER before_employee_delete
BEFORE DELETE ON employees
FOR EACH ROW
BEGIN
    DECLARE hours_count INT;

    -- Проверяваме колко записа има този служител в таблицата work_hours
    SELECT COUNT(*) INTO hours_count
    FROM work_hours
    WHERE employee_id = OLD.id;

    -- Ако има поне един запис (hours_count > 0), спираме изтриването с грешка
    IF hours_count > 0 THEN
        SIGNAL SQLSTATE '45000'
        SET MESSAGE_TEXT = 'Грешка: Не можете да изтриете служител, който има записани отработени часове!';
    END IF;
END //

DELIMITER ;

-- ТЕСТ 1: Опит за изтриване на служител, който ИМА часове
-- ---------------------------------------------------------
DELETE FROM employees WHERE id = 1; 

-- ТЕСТ 2: Добавяне на нов човек без часове и неговото изтриване
-- ---------------------------------------------------------
INSERT INTO employees (name, salary, position) VALUES ('Човек За Изтриване', 1000.00, 'Test');

-- Взимаме неговото ID (за да сме сигурни кое е) и го запазваме в променлива
SET @test_id = LAST_INSERT_ID();

-- Опитваме да го изтрием
DELETE FROM employees WHERE id = @test_id;

-- Проверяваме дали е изтрит (резултатът трябва да е празен)


-- ===============================================================================

-- Създаваме таблица за логване на изтрити служители
CREATE TABLE IF NOT EXISTS deleted_employees_log (
    log_id INT AUTO_INCREMENT PRIMARY KEY,
    employee_id INT,
    employee_name VARCHAR(100),
    deleted_at DATETIME DEFAULT CURRENT_TIMESTAMP
);

-- Изтриваме стария тригер, ако има такъв, за да няма конфликти
DROP TRIGGER IF EXISTS log_after_employee_delete;

DELIMITER //

CREATE TRIGGER log_after_employee_delete
AFTER DELETE ON employees
FOR EACH ROW
BEGIN
    -- Записваме ID-то и Името на изтрития служител в лог таблицата
    INSERT INTO deleted_employees_log (employee_id, employee_name, deleted_at)
    VALUES (OLD.id, OLD.name, NOW());
END //

DELIMITER ;

-- 1. Добавяме нов служител специално за този тест
INSERT INTO employees (name, salary, position) 
VALUES ('Иван За Изтриване', 1500.00, 'Trainee');

-- Взимаме неговото ID, за да знаем кого точно трием
SET @delete_id = LAST_INSERT_ID();

-- 2. Изтриваме го (Тъй като няма часове в work_hours, BEFORE тригерът ще го пусне)
DELETE FROM employees WHERE id = @delete_id;

-- 3. Проверяваме лог таблицата!
SELECT 
    CONCAT('Служителят ', employee_name, ' (ID: ', employee_id, ') беше изтрит на ', deleted_at) AS Delete_Message
FROM deleted_employees_log
WHERE employee_id = @delete_id;

-- =======================================================================================================

DROP TRIGGER IF EXISTS before_employee_delete;
-- Показва таблица с всички съществуващи тригери
SHOW TRIGGERS;

-- ========================================================================================================

