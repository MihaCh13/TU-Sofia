-- Проверка в кои апартаменти живеят най-много души.
SELECT 
    b.City AS 'Град',
    CONCAT(b.Address, ', № ', b.Building_Num, ', ап. ', a.Apartment_Num) AS 'Адрес',
    a.Apartment_Type AS 'Тип',
    COUNT(ap.Person_ID) AS 'Брой обитатели'
FROM Apartments a
JOIN Buildings b ON a.Building_ID = b.Building_ID
JOIN Apartment_Persons ap ON a.Apartment_ID = ap.Apartment_ID
GROUP BY a.Apartment_ID
HAVING COUNT(ap.Person_ID) > 2
ORDER BY COUNT(ap.Person_ID) DESC;

