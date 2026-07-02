-- Неплатени такси за последния месец
SELECT Fee_ID, Apartment_ID, Amount, Fee_Month 
FROM Fees 
WHERE Is_Paid = 'No' AND Fee_Month = 4;

--
-- Извеждане на длъжниците за февруари в Пловдив за сградите на домоуправител Стоян Стоянов
-- Включва форматиране на месеца и информация за текущи/планирани ремонти в сградата
SELECT 
    b.City AS 'Град',
    b.Address AS 'Адрес на сградата',
    a.Apartment_Num AS 'Ап. №',
    p.First_Name AS 'Име на длъжник',
    p.Last_Name AS 'Фамилия',
    f.Amount AS 'Дължима сума (лв.)',
    CASE 
        WHEN f.Fee_Month = 1 THEN 'Януари'
        WHEN f.Fee_Month = 2 THEN 'Февруари'
        WHEN f.Fee_Month = 3 THEN 'Март'
        WHEN f.Fee_Month = 4 THEN 'Април'
        ELSE 'Друг месец'
    END AS 'Месец на задължението',
    IFNULL(r.Description, 'Няма текущи ремонти') AS 'Текущ/Планиран ремонт в сградата',
    CONCAT(u.First_Name, ' ', u.Last_Name) AS 'Домоуправител'
FROM Fees f
JOIN Apartments a ON f.Apartment_ID = a.Apartment_ID
JOIN Buildings b ON a.Building_ID = b.Building_ID
JOIN Users u ON b.User_ID = u.User_ID
JOIN Apartment_Persons ap ON a.Apartment_ID = ap.Apartment_ID
JOIN Persons p ON ap.Person_ID = p.Person_ID
LEFT JOIN Repairs r ON b.Building_ID = r.Building_ID AND r.Status IN ('Planned', 'In Progress')
WHERE 
    f.Fee_Month = 2 
    AND f.Fee_Year = 2026
    AND f.Is_Paid = 'No' 
    AND b.City = 'Sofia' 
    AND u.First_Name = 'Nikolay'
    AND ap.Is_Owner = 'Yes';