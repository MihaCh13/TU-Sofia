-- Извеждане на апартаменти, чиято площ е над средната за съответния град
SELECT 
    b.City AS 'Град',
    CONCAT(b.Address, ', № ', b.Building_Num) AS 'Адрес',
    a.Apartment_Num AS 'Апартамент',
    a.Area AS 'Площ'
FROM Apartments a
JOIN Buildings b ON a.Building_ID = b.Building_ID
WHERE a.Area > (
    -- Вложена заявка: изчислява средната площ само за текущия град
    SELECT AVG(a2.Area)
    FROM Apartments a2
    JOIN Buildings b2 ON a2.Building_ID = b2.Building_ID
    WHERE b2.City = b.City
)
ORDER BY b.City, a.Area DESC;

-- Справка за средната площ на апартаментите по градове
SELECT 
    b.City AS 'Град', 
    ROUND(AVG(a.Area), 2) AS 'Средна площ (кв.м.)',
    COUNT(a.Apartment_ID) AS 'Брой апартаменти'
FROM Apartments a
JOIN Buildings b ON a.Building_ID = b.Building_ID
GROUP BY b.City
ORDER BY ROUND(AVG(a.Area), 2) DESC;