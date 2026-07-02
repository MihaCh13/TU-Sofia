-- =========================================================================
-- Демонстрация на използването на курсор (Cursor) в съхранена процедура. 
-- Курсорът позволява обхождането на резултатен набор ред по ред. Създадената
-- процедура приема ID на сграда и връща форматиран текстов списък 
-- с всички длъжници (апартаменти и суми) в тази сграда. Използвана е класическата 
-- структура: DECLARE -> OPEN -> FETCH (в цикъл) -> CLOSE."
-- =========================================================================


-- БЛОК 1: Създаване на VIEW (Изглед) за неплатените такси

CREATE OR REPLACE VIEW View_UnpaidFees AS
SELECT 
    f.Apartment_ID,
    a.Building_ID,
    a.Apartment_Num,
    f.Amount,
    f.Fee_Month,
    f.Fee_Year
FROM Fees f
JOIN Apartments a ON f.Apartment_ID = a.Apartment_ID
WHERE f.Is_Paid = 'No';

-- -------------------------------------------------------------------
DELIMITER //

DROP PROCEDURE IF EXISTS GenerateDebtorsReport //

-- Процедурата приема ID на сграда (IN) и връща готов текстов връща таблица
CREATE PROCEDURE GenerateDebtorsReport(IN target_building_ID INT)
BEGIN
    -- 1. ДЕКЛАРИРАНЕ НА ПРОМЕНЛИВИ
    DECLARE v_ap_num VARCHAR(10);
    DECLARE v_fee_amt DECIMAL(10,2);
    -- Променлива (флаг), която ще ни каже кога курсорът е стигнал до края
    DECLARE done INT DEFAULT 0;

    -- 2. ДЕКЛАРИРАНЕ НА КУРСОР, който черпи данни директно от изгледа
    DECLARE debtors_cursor CURSOR FOR
        SELECT Apartment_Num, Amount
        FROM View_UnpaidFees
        WHERE Building_ID = target_building_ID;

    -- 3. ДЕКЛАРИРАНЕ НА ОБРАБОТЧИК НА ГРЕШКИ (HANDLER)
    DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = 1;

    -- 4. СЪЗДАВАНЕ НА ВРЕМЕННА ТАБЛИЦА - тя ще съществува само докато процедурата работи
    DROP TEMPORARY TABLE IF EXISTS Temp_Debtors;
    CREATE TEMPORARY TABLE Temp_Debtors (
        Apartment VARCHAR(10),
        Debt_Amount DECIMAL(10,2)
    );

    -- 5. ОТВАРЯНЕ НА КУРСОР
    OPEN debtors_cursor;

    -- 6. СТАРТИРАНЕ НА ЦИКЪЛ (LOOP)
    read_loop: LOOP 
        -- Взимаме стойностите от текущия ред
        FETCH debtors_cursor INTO v_ap_num, v_fee_amt;

        --  Ако сме стигнали края (done = 1), излизаме от цикъла (LEAVE)
        IF done THEN
            LEAVE read_loop;
        END IF;

        -- Вмъкваме всеки ред във временната таблица
        INSERT INTO Temp_Debtors (Apartment, Debt_Amount) 
        VALUES (v_ap_num, v_fee_amt);
    END LOOP;

    -- 7. ЗАТВАРЯНЕ НА КУРСОР
    CLOSE debtors_cursor;

        -- 8. ИЗВЕЖДАНЕ НА РЕЗУЛТАТА (Това прави красивата таблица!)
    SELECT 
		CONCAT('Апартамент № ', Apartment, ' дължи: ', Debt_Amount, ' лв.') 
        AS 'Справка за длъжници' 
        FROM Temp_Debtors;

    -- 9. ПОЧИСТВАНЕ НА ПАМЕТТА
    DROP TEMPORARY TABLE IF EXISTS Temp_Debtors;

END //
DELIMITER ;

-- =========================================================================
-- ТЕСТ НА ПРОЦЕДУРАТА С КУРСОР
-- Извикваме процедурата за Building_ID = 1 и запазваме резултата 
-- в глобалната променлива @my_report
-- =========================================================================

-- Извикване на процедурата (само с ID на сградата)
CALL GenerateDebtorsReport(1);