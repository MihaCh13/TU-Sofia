-- ------------------------------------------
-- Лаб 6

DELIMITER |
CREATE PROCEDURE getAllSportGroupsWithSports()
BEGIN
    SELECT sg.location AS locationofGroup,
           sg.dayOfWeek AS trainingDay,
           sg.hourOfTraining AS trainingHour,
           sp.name AS sportName
    FROM sportgroups AS sg
    JOIN sports AS sp
        ON sg.sport_id = sp.id;
END |
DELIMITER ;
CALL getAllSportGroupsWithSports();

-- --------------------------------------------------
SET @coaches_name = 'Иван Тодоров Петров';
SELECT * 
FROM teachers
WHERE name = @coaches_name;

-- --------------------------------------------

DROP PROCEDURE IF EXISTS proc_in;
DELIMITER |
CREATE PROCEDURE proc_in (IN var VARCHAR(225))
BEGIN
    SET @coach_name = var;
END |
DELIMITER ;
CALL proc_in('Ilian Todorov');
SELECT * 
FROM teachers
WHERE name = @coach_name;

-- -------------------------------------------

DROP PROCEDURE IF EXISTS proc_in_withchange;
DELIMITER |
CREATE PROCEDURE proc_in_withchange (INOUT var VARCHAR(225))
BEGIN
    SET var = 'Ilian Todorov';
END |
DELIMITER ;
SET @testcoach_name = 'Ilian Todorov';
CALL proc_in_withchange(@testcoach_name);
SELECT @testcoach_name;

-- ---------------------------------------------------------

DROP PROCEDURE IF EXISTS out_Proc;

DELIMITER |
CREATE PROCEDURE out_Proc (OUT var VARCHAR(50))
BEGIN
    SELECT var; -- only for test
    SET var = 'Ilian Todorov';
END |
DELIMITER ;
SET @testOutParam = 'Some name';
CALL out_Proc(@testOutParam);
SELECT @testOutParam;

-- ---------------------------------------

DELIMITER |
CREATE PROCEDURE proc_in_out (INOUT var VARCHAR(225))
BEGIN
select var; # only for test
    SET var = 'Иван Тодоров Петров';
END |
DELIMITER ;
SET @test_in_out_var = 'Some name';
CALL proc_in_out(@test_in_out_var);

-- ----------------------------------------------------
-- задача 1
-- Процедура, която да показва децата, които тренират два или повече вида спорт

DROP PROCEDURE IF EXISTS students_with_two_sports;

DELIMITER |
CREATE PROCEDURE students_with_two_sports()
BEGIN
    SELECT 
        st.id,
        st.name,
        GROUP_CONCAT(DISTINCT sp.name SEPARATOR ', ') AS sports
    FROM students st
    JOIN student_sport ss 
        ON st.id = ss.student_id
    JOIN sportGroups sg 
        ON ss.sportGroup_id = sg.id
    JOIN sports sp
        ON sg.sport_id = sp.id
    GROUP BY st.id, st.name
    HAVING COUNT(DISTINCT sg.sport_id) >= 2;
END |
DELIMITER ;

CALL students_with_two_sports();