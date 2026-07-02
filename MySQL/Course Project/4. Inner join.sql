-- Извличане на списък със сгради и техните домоуправители (INNER JOIN)
SELECT 
    b.City AS 'Град',
    b.Address AS 'Адрес',
    b.Building_Num AS 'Блок №',
    b.Entrance AS 'Вход',
    CONCAT(u.First_Name, ' ', u.Last_Name) AS 'Домоуправител',
    u.Phone AS 'Телефон за връзка'
FROM Buildings b
INNER JOIN Users u ON b.User_ID = u.User_ID
ORDER BY b.City, b.Address;

-- Извеждане на всички ремонти в процес и сградите, в които се извършват
SELECT 
    b.City AS 'Град',
    b.Address AS 'Сграда',
    r.Description AS 'Вид ремонт',
    r.Cost AS 'Стойност (лв.)',
    DATE_FORMAT(r.Date_Logged, '%d.%m.%Y') AS 'Дата на завеждане'
FROM Repairs r
INNER JOIN Buildings b ON r.Building_ID = b.Building_ID
WHERE r.Status = 'In Progress'
ORDER BY r.Cost DESC;