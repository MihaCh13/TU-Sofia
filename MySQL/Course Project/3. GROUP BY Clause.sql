-- Извеждане на домоуправители, които управляват повече от една сграда/вход
SELECT 
    u.First_Name AS 'Име',
    u.Last_Name AS 'Фамилия',
    COUNT(b.Building_ID) AS 'Брой управлявани сгради'
FROM Users u
JOIN Buildings b ON u.User_ID = b.User_ID
GROUP BY u.User_ID, u.First_Name, u.Last_Name
HAVING COUNT(b.Building_ID) > 1;

-- Извеждане на общия брой домашни любимци за всяка сграда
SELECT 
    b.City AS 'Град',
    b.Address AS 'Адрес на сградата',
    SUM(a.Pets_Count) AS 'Общ брой домашни любимци'
FROM Apartments a
JOIN Buildings b ON a.Building_ID = b.Building_ID
GROUP BY b.Building_ID, b.City, b.Address
ORDER BY SUM(a.Pets_Count) DESC;

-- Изчисляване на средния размер на платените такси, групирани по град
SELECT 
    b.City AS 'Град',
    AVG(f.Amount) AS 'Средно платена такса (лв.)'
FROM Fees f
JOIN Apartments a ON f.Apartment_ID = a.Apartment_ID
JOIN Buildings b ON a.Building_ID = b.Building_ID
WHERE f.Is_Paid = 'Yes'
GROUP BY b.City
ORDER BY AVG(f.Amount) DESC;