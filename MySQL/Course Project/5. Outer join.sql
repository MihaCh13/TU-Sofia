-- LEFT OUTER JOIN - списък на всички апартаменти в блока, показващ кой е платил за месеца и кой не
SELECT 
    b.City AS 'Град',
    CONCAT(b.Address, ', bl. № ', b.Building_Num, ', vh. № ', b.Entrance) AS 'Пълен Адрес',
    a.Apartment_Num AS 'Апартамент', 
    f.Amount AS 'Сума',
    f.Is_Paid AS 'Платено',
    f.Payment_Date AS 'Дата'
FROM Apartments a
INNER JOIN Buildings b ON a.Building_ID = b.Building_ID
LEFT JOIN Fees f ON a.Apartment_ID = f.Apartment_ID 
    AND f.Fee_Month = 1 
WHERE a.Building_ID = 1;


-- RIGHT OUTER JOIN, списък на апартаментиje в блока, показващ къде има домашен любимец
SELECT 
    NULLIF(a.Pets_Count, 0) AS 'Брой любимци',
    a.Floor AS 'Етаж',
    a.Apartment_Num AS 'Апартамент №',
    b.City AS 'Град',
    CONCAT(b.Address, ', bl. № ', b.Building_Num, ', vhod ', b.Entrance) AS 'Пълен Адрес'
FROM (SELECT Apartment_ID FROM Apartments WHERE Pets_Count > 0) AS has_pets
RIGHT OUTER JOIN Apartments a ON has_pets.Apartment_ID = a.Apartment_ID
INNER JOIN Buildings b ON a.Building_ID = b.Building_ID
WHERE b.Building_ID = 1
ORDER BY a.Floor, a.Apartment_Num;