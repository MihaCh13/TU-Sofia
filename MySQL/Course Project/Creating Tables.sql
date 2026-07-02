-- 1. Създаване на базата данни
CREATE DATABASE IF NOT EXISTS BuildingManagement;
USE BuildingManagement;

-- -------------------------------------------------------------------------
-- 1. Таблица за ролите - разделяме администратора от домоуправителите
-- -------------------------------------------------------------------------
CREATE TABLE Roles (
	Role_ID INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
	Role_Type ENUM('Administrator', 'Manager') NOT NULL
);

INSERT INTO Roles (Role_Type) VALUES
('Administrator'),
('Manager');

-- -------------------------------------------------------------------------
-- 2. Таблица за потребители - хората, които влизат в системата с парола
-- -------------------------------------------------------------------------
CREATE TABLE Users (
    User_ID INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    Username VARCHAR(50) NOT NULL UNIQUE,
    Password_Hash VARCHAR(255) NOT NULL,
    First_Name VARCHAR(50) NOT NULL,
    Last_Name VARCHAR(50) NOT NULL,
    Phone VARCHAR(20) NOT NULL UNIQUE,
    Email VARCHAR(100) NOT NULL UNIQUE,
    Role_ID INT,
    CONSTRAINT fk_users_roles FOREIGN KEY (Role_ID) REFERENCES Roles(Role_ID)
);

INSERT INTO Users (Username, Password_Hash, First_Name, Last_Name, Phone, Email, Role_ID) VALUES 
('admin_alex', 'admin_pass_77', 'Aleksandar', 'Georgiev', '0888000111', 'admin@abv.bg', 1),
('m_petrov', 'Pepsi23', 'Petar', 'Petrov', '0899111222', 'p.petrov@gmail.com', 2),
('m_ivanova', 'M_Ipas#456', 'Maria', 'Ivanova', '0877222333', 'm.ivanova@gmail.com', 2),
('m_dimitrov', 'ds_pass97', 'Stefan', 'Dimitrov', '0866444555', 's.dimitrov@gmail.com', 2),
('m_nikolova', 'El@Ni_27', 'Elena', 'Nikolova', '0855666777', 'e.nikolova@gmail.com', 2),
('m_kolev', 'pass123', 'Nikolay', 'Kolev', '0844888999', 'n.kolev@gmail.com', 2),
('m_stoyanov', 'stoy_123', 'Stoyan', 'Stoyanov', '0833111222', 's.stoyanov@gmail.com', 2),
('m_marinova', 'mari_456', 'Aneliya', 'Marinova', '0822333444', 'a.marinova@gmail.com', 2),
('m_vasilev', 'vasi_789', 'Vasil', 'Vasilev', '0811555666', 'v.vasilev@gmail.com', 2),
('m_todorova', 'todo_000', 'Tsvetana', 'Todorova', '0800777888', 'ts.todorova@gmail.com', 2);

-- -------------------------------------------------------------------------
-- 3. Таблица за сградите - входовете/блоковете, които се управляват
-- -------------------------------------------------------------------------
CREATE TABLE Buildings (
	Building_ID INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
	City VARCHAR(100) NOT NULL,
	Address VARCHAR(255) NOT NULL,
	Building_Num VARCHAR(20) NOT NULL,
	Entrance VARCHAR(10) NOT NULL,
	User_ID INT,
CONSTRAINT fk_buildings_users FOREIGN KEY (User_ID) REFERENCES Users(User_ID)
);

INSERT INTO Buildings (City, Address, Building_Num, Entrance, User_ID) VALUES 
('Sofia', 'jk. Mladost 1, bl. 15', '15', 'A', 2),
('Sofia', 'jk. Musagenica, bl. 40', '40', 'B', 3),
('Sofia', 'kv. Dragalevci, ul. Iv. Vazov', '12', '1', 4),
('Sofia', 'kv. Manastirski livadi, ul. Pirin', '5', 'A', 5),
('Sofia', 'jk. Mladost 4, bl. 420', '420', '3', 6),
('Plovdiv', 'bul. Ruski', '№ 10', 'Vhod 1', 7),
('Plovdiv', 'ul. Gladston', '№ 5', 'A', 8),
('Varna', 'jk. Chaika, bl. 18', '18', '2', 9),
('Burgas', 'jk. Lazur, bl. 5', '5', '3', 10),
('Ruse', 'ul. Aleksandrovska', '№ 22', 'B', 7); 

-- -------------------------------------------------------------------------
-- 4. Таблица за апартаменти - описание на самите жилища във всяка сграда
-- -------------------------------------------------------------------------
CREATE TABLE Apartments (
	Apartment_ID INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    Apartment_Num VARCHAR(10) NOT NULL,
    Area DECIMAL(10, 2) NOT NULL,
    Pets_Count INT NOT NULL DEFAULT 0,
    Floor INT NOT NULL,
	Apartment_Type VARCHAR(100) NOT NULL,
	Building_ID INT,
CONSTRAINT fk_apartment_buildings FOREIGN KEY (Building_ID) REFERENCES Buildings(Building_ID)
);

INSERT INTO Apartments (Apartment_Num, Area, Pets_Count, Floor, Apartment_Type, Building_ID) VALUES 

-- 1. Sofia (Mladost 1, bl. 15) - 8 etaja x 2 ap. (Building_ID 1)
('1', 65.00, 0, 1, 'Dvustaen', 1), ('2', 90.00, 1, 1, 'Tristaen', 1),
('3', 65.00, 0, 2, 'Dvustaen', 1), ('4', 90.00, 0, 2, 'Tristaen', 1),
('5', 65.00, 1, 3, 'Dvustaen', 1), ('6', 90.00, 0, 3, 'Tristaen', 1),
('7', 65.00, 0, 4, 'Dvustaen', 1), ('8', 90.00, 0, 4, 'Tristaen', 1),
('9', 65.00, 0, 5, 'Dvustaen', 1), ('10', 90.00, 2, 5, 'Tristaen', 1),
('11', 65.00, 0, 6, 'Dvustaen', 1), ('12', 90.00, 0, 6, 'Tristaen', 1),
('13', 65.00, 1, 7, 'Dvustaen', 1), ('14', 90.00, 0, 7, 'Tristaen', 1),
('15', 120.00, 0, 8, 'Mezonet', 1), ('16', 120.00, 0, 8, 'Mezonet', 1),

-- 2. Sofia (Musagenica, bl. 40) - 5 etaja x 3 ap. (Building_ID 2)
('1', 45.00, 0, 1, 'Atelie', 2), ('2', 60.00, 0, 1, 'Dvustaen', 2), ('3', 60.00, 1, 1, 'Dvustaen', 2),
('4', 45.00, 0, 2, 'Atelie', 2), ('5', 60.00, 0, 2, 'Dvustaen', 2), ('6', 60.00, 0, 2, 'Dvustaen', 2),
('7', 45.00, 1, 3, 'Atelie', 2), ('8', 60.00, 0, 3, 'Dvustaen', 2), ('9', 60.00, 0, 3, 'Dvustaen', 2),
('10', 45.00, 0, 4, 'Atelie', 2), ('11', 60.00, 0, 4, 'Dvustaen', 2), ('12', 60.00, 0, 4, 'Dvustaen', 2),
('13', 45.00, 0, 5, 'Atelie', 2), ('14', 60.00, 0, 5, 'Dvustaen', 2), ('15', 60.00, 1, 5, 'Dvustaen', 2),

-- 3. Sofia (Dragalevci) - 3 etaja x 2 ap. (Building_ID 3)
('1', 110.00, 2, 1, 'Tristaen', 3), ('2', 110.00, 0, 1, 'Tristaen', 3),
('3', 110.00, 0, 2, 'Tristaen', 3), ('4', 110.00, 0, 2, 'Tristaen', 3),
('5', 220.00, 1, 3, 'Penthouse', 3), ('6', 220.00, 0, 3, 'Penthouse', 3),

-- 4. Sofia (Manastirski livadi) - 6 etaja x 2 ap. (Building_ID 4)
('101', 55.00, 0, 1, 'Dvustaen', 4), ('102', 75.00, 0, 1, 'Dvustaen', 4),
('201', 55.00, 1, 2, 'Dvustaen', 4), ('202', 75.00, 0, 2, 'Dvustaen', 4),
('301', 55.00, 0, 3, 'Dvustaen', 4), ('302', 75.00, 0, 3, 'Dvustaen', 4),
('401', 55.00, 0, 4, 'Dvustaen', 4), ('402', 75.00, 1, 4, 'Dvustaen', 4),
('501', 55.00, 0, 5, 'Dvustaen', 4), ('502', 75.00, 0, 5, 'Dvustaen', 4),
('601', 100.00, 0, 6, 'Tristaen', 4), ('602', 100.00, 0, 6, 'Tristaen', 4),

-- 5. Sofia (Mladost 4, bl. 420) - 8 etaja x 3 ap. (Building_ID 5)
('1', 40.00, 0, 1, 'Garsoniera', 5), ('2', 70.00, 1, 1, 'Dvustaen', 5), ('3', 70.00, 0, 1, 'Dvustaen', 5),
('4', 40.00, 0, 2, 'Garsoniera', 5), ('5', 70.00, 0, 2, 'Dvustaen', 5), ('6', 70.00, 1, 2, 'Dvustaen', 5),
('7', 40.00, 0, 3, 'Garsoniera', 5), ('8', 70.00, 0, 3, 'Dvustaen', 5), ('9', 70.00, 0, 3, 'Dvustaen', 5),
('10', 40.00, 1, 4, 'Garsoniera', 5), ('11', 70.00, 0, 4, 'Dvustaen', 5), ('12', 70.00, 0, 4, 'Dvustaen', 5),
('13', 40.00, 0, 5, 'Garsoniera', 5), ('14', 70.00, 0, 5, 'Dvustaen', 5), ('15', 70.00, 0, 5, 'Dvustaen', 5),
('16', 40.00, 0, 6, 'Garsoniera', 5), ('17', 70.00, 0, 6, 'Dvustaen', 5), ('18', 70.00, 1, 6, 'Dvustaen', 5),
('19', 40.00, 0, 7, 'Garsoniera', 5), ('20', 70.00, 0, 7, 'Dvustaen', 5), ('21', 70.00, 0, 7, 'Dvustaen', 5),
('22', 150.00, 0, 8, 'Mezonet', 5), ('23', 150.00, 0, 8, 'Mezonet', 5), ('24', 150.00, 0, 8, 'Mezonet', 5),

-- 6. Plovdiv (Bul. Ruski) - 5 etaja x 2 ap. (Building_ID 6)
('1', 80.00, 0, 1, 'Tristaen', 6), ('2', 80.00, 0, 1, 'Tristaen', 6),
('3', 80.00, 1, 2, 'Tristaen', 6), ('4', 80.00, 0, 2, 'Tristaen', 6),
('5', 80.00, 0, 3, 'Tristaen', 6), ('6', 80.00, 0, 3, 'Tristaen', 6),
('7', 80.00, 0, 4, 'Tristaen', 6), ('8', 80.00, 0, 4, 'Tristaen', 6),
('9', 160.00, 0, 5, 'Mezonet', 6), ('10', 160.00, 1, 5, 'Mezonet', 6),

-- 7. Plovdiv (ul. Gladston) - 5 etaja x 1 ap. (Building_ID 7)
('1', 90.00, 0, 1, 'Tristaen', 7),
('2', 90.00, 1, 2, 'Tristaen', 7),
('3', 90.00, 0, 3, 'Tristaen', 7),
('4', 90.00, 0, 4, 'Tristaen', 7),
('5', 90.00, 0, 5, 'Tristaen', 7),

-- 8. Varna (Chaika) - 5 etaja x 2 ap. (Building_ID 8)
('1', 60.00, 1, 1, 'Dvustaen', 8), ('2', 60.00, 0, 1, 'Dvustaen', 8),
('3', 60.00, 0, 2, 'Dvustaen', 8), ('4', 60.00, 0, 2, 'Dvustaen', 8),
('5', 60.00, 0, 3, 'Dvustaen', 8), ('6', 60.00, 0, 3, 'Dvustaen', 8),
('7', 60.00, 1, 4, 'Dvustaen', 8), ('8', 60.00, 0, 4, 'Dvustaen', 8),
('9', 110.00, 0, 5, 'Tristaen', 8), ('10', 110.00, 0, 5, 'Tristaen', 8),

-- 9. Burgas (Lazur) - 5 etaja x 1 ap. (Building_ID 9)
('1', 100.00, 2, 1, 'Tristaen', 9),
('2', 100.00, 0, 2, 'Tristaen', 9),
('3', 100.00, 0, 3, 'Tristaen', 9),
('4', 100.00, 0, 4, 'Tristaen', 9),
('5', 100.00, 1, 5, 'Tristaen', 9),

-- 10. Ruse (ul. Aleksandrovska) - 5 etaja x 1 ap. (Building_ID 10)
('1', 45.00, 0, 1, 'Atelie', 10),
('2', 45.00, 0, 2, 'Atelie', 10),
('3', 45.00, 1, 3, 'Atelie', 10),
('4', 45.00, 0, 4, 'Atelie', 10),
('5', 45.00, 0, 5, 'Atelie', 10);

-- -------------------------------------------------------------------------
-- 5. Таблица за хора - списък с всички физически лица, независимо дали 
--    са собственици, или наематели.
-- -------------------------------------------------------------------------
CREATE TABLE Persons (
	Person_ID INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    First_Name VARCHAR(50) NOT NULL,
    Last_Name VARCHAR(50) NOT NULL,
    Phone VARCHAR(20) NOT NULL UNIQUE,
    Email VARCHAR(100) NOT NULL UNIQUE
);

INSERT INTO Persons (First_Name, Last_Name, Phone, Email) VALUES 

-- Живущи в Building 1: Sofia, jk. Mladost 1, bl. 15
('Ivan', 'Ivanov', '0887111221', 'i.ivanov@gmail.com'),
('Maria', 'Petrova', '0887222332', 'm.petrova@abv.bg'),
('Georgi', 'Dimitrov', '0887333443', 'g.dimitrov@yahoo.com'),
('Elena', 'Stoyanova', '0887444554', 'e.stoyanova@gmail.com'),
('Stefan', 'Kolev', '0887555665', 's.kolev@abv.bg'),
('Petya', 'Nikolova', '0887666776', 'p.nikolova@gmail.com'),
('Dimitar', 'Vasilev', '0887777887', 'd.vasilev@mail.bg'),
('Aneliya', 'Kostova', '0887888998', 'a.kostova@gmail.com'),
('Hristo', 'Yanev', '0887999009', 'h.yanev@abv.bg'),
('Desislava', 'Miteva', '0887000110', 'd.miteva@gmail.com'),
('Martin', 'Angelov', '0886111221', 'm.angelov@yahoo.com'),
('Vesela', 'Ilieva', '0886222332', 'v.ilieva@gmail.com'),
('Kiril', 'Popov', '0886333443', 'k.popov@abv.bg'),
('Nadezhda', 'Toneva', '0886444554', 'n.toneva@gmail.com'),
('Radoslav', 'Genov', '0886555665', 'r.genov@mail.bg'),
('Boryana', 'Simeonova', '0886666776', 'b.simeonova@gmail.com'),

-- Живущи в Building 2: Sofia, jk. Musagenica, bl. 40
('Vasil', 'Vasilev', '0878111222', 'v.vasilev@gmail.com'),
('Gergana', 'Pashova', '0878222333', 'g.pashova@abv.bg'),
('Simeon', 'Borisov', '0878333444', 's.borisov@yahoo.com'),
('Teodora', 'Koleva', '0878444555', 't.koleva@gmail.com'),
('Nikola', 'Ganchev', '0878555666', 'n.ganchev@abv.bg'),
('Ralitsa', 'Iordanova', '0878666777', 'r.iordanova@gmail.com'),
('Andrei', 'Stoev', '0878777888', 'a.stoev@mail.bg'),
('Kameliya', 'Dobreva', '0878888999', 'k.dobreva@gmail.com'),
('Plamen', 'Zhelev', '0878999000', 'p.zhelev@abv.bg'),
('Monika', 'Slavova', '0878000111', 'm.slavova@gmail.com'),
('Viktor', 'Yankov', '0879111222', 'v.yankov@yahoo.com'),
('Svetlana', 'Marinova', '0879222333', 's.marinova@gmail.com'),
('Emil', 'Hristov', '0879333444', 'e.hristov@abv.bg'),
('Albena', 'Vitanova', '0879444555', 'a.vitanova@gmail.com'),
('Lubomir', 'Tsvetkov', '0879555666', 'l.tsvetkov@mail.bg'),

-- Живущи в Building 3: Sofia, kv. Dragalevci, ul. Iv. Vazov
('Yuliyan', 'Simeonov', '0885111222', 'y.simeonov@vip.bg'),
('Kristina', 'Deneva', '0885222333', 'k.deneva@lux.bg'),
('Bogdan', 'Andreev', '0885333444', 'b.andreev@business.com'),
('Ralica', 'Tsvetkova', '0885555666', 'r.tsvetkova@mail.bg'),
('Viktor', 'Sotirov', '0885777888', 'v.sotirov@invest.bg'),
('Mariya-Magdalena', 'Popova', '0885999000', 'm.popova@art.bg'),

-- Живущи в Building 4: Sofia, kv. Manastirski livadi, ul. Pirin
('Blagovest', 'Arnaudov', '0895111001', 'b.arnaudov@gmail.com'),
('Ivelina', 'Chaneva', '0895111002', 'i.chaneva@abv.bg'),
('Kalin', 'Vrachanski', '0895111003', 'k.vrachanski@yahoo.com'),
('Simona', 'Zagorova', '0895111004', 's.zagorova@gmail.com'),
('Denis', 'Teofikov', '0895111005', 'd.teofikov@mail.bg'),
('Lora', 'Karadjova', '0895111006', 'l.karadjova@abv.bg'),
('Pavel', 'Nikolov', '0895111007', 'p.nikolov@gmail.com'),
('Ventsi', 'Vents', '0895111008', 'v.vents@yahoo.com'),
('Zlatka', 'Raykova', '0895111009', 'z.raykova@gmail.com'),
('Blagoy', 'Georgiev', '0895111010', 'b.georgiev@abv.bg'),
('Kristiyan', 'Kirilov', '0895111011', 'k.kirilov@mail.bg'),
('Zhana', 'Bergendorff', '0895111012', 'zh.berg@gmail.com'),

-- Живущи в Building 5: Sofia, jk. Mladost 4, bl. 420
('Asparuh', 'Khanov', '0884100200', 'a.khanov@mail.bg'),
('Tervel', 'Pobedov', '0884100201', 't.pobedov@gmail.com'),
('Krum', 'Zakonov', '0884100202', 'k.zakonov@abv.bg'),
('Omurtag', 'Stroitelov', '0884100203', 'o.stroitelov@yahoo.com'),
('Boris', 'Pokrustitel', '0884100204', 'b.pokrust@mail.bg'),
('Simeon', 'Velikov', '0884100205', 's.velikov@gmail.com'),
('Petar', 'Svetov', '0884100206', 'p.svetov@abv.bg'),
('Samuil', 'Tragiov', '0884100207', 's.tragiov@yahoo.com'),
('Kaloyan', 'Rimalov', '0884100208', 'k.rimalov@mail.bg'),
('Ivan', 'Asen', '0884100209', 'i.asen@gmail.com'),
('Teodor', 'Svetoslav', '0884100210', 't.svetoslav@abv.bg'),
('Ivailo', 'Burdokva', '0884100211', 'i.burdokva@yahoo.com'),
('Konstantin', 'Tih', '0884100212', 'k.tih@mail.bg'),
('Mihail', 'Shishman', '0884100213', 'm.shishman@gmail.com'),
('Aleksandar', 'Nevski', '0884100214', 'a.nevski@abv.bg'),
('Ferdinand', 'Sakskoburggotski', '0884100215', 'f.saks@yahoo.com'),
('Boris', 'Treti', '0884100216', 'b.treti@mail.bg'),
('Zhelyu', 'Zhelev', '0884100217', 'zh.zhelev@gmail.com'),
('Petar', 'Stoyanov', '0884100218', 'p.stoyanov@abv.bg'),
('Georgi', 'Parvanov', '0884100219', 'g.parvanov@yahoo.com'),
('Rosen', 'Plevneliev', '0884100220', 'r.plevneliev@mail.bg'),
('Rumen', 'Radev', '0884100221', 'r.radev@gmail.com'),
('Boyko', 'Borisov', '0884100222', 'b.borisov@abv.bg'),
('Kiril', 'Petkov', '0884100223', 'k.petkov@yahoo.com'),

-- Живущи в Building 6: Plovdiv, bul. Ruski, bl. 10
('Stoyan', 'Zaimov', '0883000401', 's.zaimov@plovdiv.bg'),
('Rada', 'Gospodinova', '0883000402', 'r.gospodinova@abv.bg'),
('Panayot', 'Volov', '0883000403', 'p.volov@yahoo.com'),
('Rayna', 'Knyaginya', '0883000404', 'r.knyaginya@mail.bg'),
('Zahari', 'Stoyanov', '0883000405', 'z.stoyanov@gmail.com'),
('Hristo', 'Danov', '0883000406', 'h.danov@abv.bg'),
('Nayden', 'Gerov', '0883000407', 'n.gerov@yahoo.com'),
('Joakim', 'Gruev', '0883000408', 'j.gruev@mail.bg'),
('Dimitar', 'Kudoglu', '0883000409', 'd.kudoglu@gmail.com'),
('Konstantin', 'Stoilov', '0883000410', 'k.stoilov@abv.bg'),

-- Живущи в Building 7: Plovdiv, ul. Gladston, № 5
('Peyo', 'Yavorov', '0883111501', 'p.yavorov@plovdiv.bg'),
('Lora', 'Karavelova', '0883111502', 'l.karavelova@abv.bg'),
('Dimcho', 'Debelyanov', '0883111503', 'd.debelyanov@yahoo.com'),
('Elin', 'Pelin', '0883111504', 'e.pelin@mail.bg'),
('Yordan', 'Yovkov', '0883111505', 'y.yovkov@gmail.com'),

-- Живущи в Building 8: Varna, jk. Chaika, bl. 18
('Morski', 'Kaspiyski', '0882111001', 'm.kaspiyski@varna.bg'),
('okean', 'Siniev', '0882111002', 'o.siniev@abv.bg'),
('Kapitan', 'Petko', '0882111003', 'k.petko@yahoo.com'),
('Marina', 'Yatova', '0882111004', 'm.yatova@mail.bg'),
('Galyo', 'Varnata', '0882111005', 'g.varnata@gmail.com'),
('Svetlin', 'Kuvadjiev', '0882111006', 's.kuvadjiev@abv.bg'),
('Nikoleta', 'Lozanova', '0882111007', 'n.lozanova@varna.bg'),
('Valeri', 'Bojinov', '0882111008', 'v.bojinov@mail.bg'),
('Krum', 'Savov', '0882111009', 'k.savov@gmail.com'),
('Desi', 'Slava', '0882111010', 'd.slava@abv.bg'),

-- Живущи в Building 9: Burgas, jk. Lazur, bl. 5
('Dimitur', 'Rachkov', '0881111222', 'd.rachkov@burgas.bg'),
('Maria', 'Ignatova', '0881222333', 'm.ignatova@abv.bg'),
('Toni', 'Dimitrova', '0881333444', 't.dimitrova@yahoo.com'),
('Stefan', 'Diomov', '0881444555', 's.diomov@mail.bg'),
('Petya', 'Dubarova', '0881555666', 'p.dubarova@gmail.com'),

-- Живущи в Building 10: Ruse, ul. Aleksandrovska
('Baba', 'Tonka', '0880111222', 'b.tonka@ruse.bg'),
('Angel', 'Kanchev', '0880222333', 'a.kanchev@abv.bg'),
('Stefan', 'Karadja', '0880333444', 's.karadja@yahoo.com'),
('Lyuben', 'Karavelov', '0880444555', 'l.karavelov@mail.bg'),
('Nikola', 'Obretenov', '0880555666', 'n.obretenov@gmail.com'),

-- Втори и трети обитатели за Building 1 (Mladost 1)
('Petya', 'Ivanova', '0887111229', 'p.ivanova@gmail.com'),    -- В ап. 1 при Ivan Ivanov
('Nikolay', 'Petrov', '0887222339', 'n.petrov@abv.bg'),      -- В ап. 2 при Maria Petrova
('Ivan', 'Dimitrov', '0887333449', 'i.dimitrov@yahoo.com'),  -- В ап. 3 при Georgi Dimitrov
('Gergana', 'Stoyanova', '0887444559', 'g.stoyanova@gmail.com'), -- В ап. 4 при Elena

-- Втори обитатели за Building 2 (Musagenica)
('Svetla', 'Vasileva', '0878111225', 's.vasileva@gmail.com'), -- В ап. 17 при Vasil
('Boryana', 'Pashova', '0878222335', 'b.pashova@abv.bg'),     -- В ап. 18 при Gergana
('Kaloyan', 'Borisov', '0878333445', 'k.borisov@yahoo.com'),  -- В ап. 19 при Simeon

-- Втори обитатели за Building 3 (Dragalevci - големи имоти)
('Aneliya', 'Simeonova', '0885111229', 'a.simeonova@vip.bg'), -- В ап. 32 (Penthouse)
('Stoyan', 'Andreev', '0885333449', 's.andreev@business.com'), -- В ап. 34

-- Втори обитатели за Building 4 (Manastirski livadi)
('Mariya', 'Arnaudova', '0895111101', 'm.arnaudova@gmail.com'), -- В ап. 38
('Plamen', 'Chanev', '0895111102', 'p.chanev@abv.bg'),          -- В ап. 39

-- Семейства за Building 5 (Mladost 4, bl. 420)
('Desislava', 'Khanova', '0884100300', 'd.khanova@mail.bg'),    -- В ап. 50
('Kubrat', 'Pobedov', '0884100301', 'k.pobedov@gmail.com'),     -- В ап. 51
('Raya', 'Zakonova', '0884100302', 'r.zakonova@abv.bg'),        -- В ап. 52
('Veselin', 'Velikov', '0884100305', 'v.velikov@gmail.com'),    -- В ап. 55

-- Пловдив (Bul. Ruski & Gladston)
('Katerina', 'Zaimova', '0883000501', 'k.zaimova@plovdiv.bg'),  -- В ап. 74
('Hristo', 'Gospodinov', '0883000502', 'h.gospodinov@abv.bg'),  -- В ап. 75
('Mina', 'Todorova', '0883111601', 'mina.t@plovdiv.bg'),        -- В ап. 84 (Gladston)
('Yavor', 'Yavorov', '0883111602', 'y.yavorov@abv.bg'),         -- В ап. 84 (Gladston)

-- Варна, Бургас и Русе
('Siana', 'Kaspiyska', '0882111111', 's.kaspiyska@varna.bg'),   -- В ап. 89
('Raina', 'Rachkova', '0881111333', 'r.rachkova@burgas.bg'),    -- В ап. 99
('Georgi', 'Ignatov', '0881222444', 'g.ignatov@abv.bg'),        -- В ап. 100
('Petar', 'Kanchev', '0880222444', 'p.kanchev@abv.bg'),         -- В ап. 105 (Ruse)
('Evelina', 'Karavelova', '0880444666', 'e.karavelova@mail.bg'),-- В ап. 107 (Ruse)
('Simeon', 'Obretenov', '0880555777', 's.obretenov@gmail.com'); -- В ап. 108 (Ruse)

-- -------------------------------------------------------------------------
-- 6. Свързваща таблица - връзката Много-към-Много (един човек може да има
--    много апартамента, а в един апартамент може да живеят много души)
-- -------------------------------------------------------------------------
CREATE TABLE Apartment_Persons (
    Apartment_ID INT NOT NULL,
    Person_ID INT NOT NULL,
    Is_Owner ENUM ('Yes', 'No') NOT NULL,
    Is_Resident ENUM ('Yes', 'No') NOT NULL,
    
    PRIMARY KEY (Apartment_ID, Person_ID),
    CONSTRAINT fk_ap_pers_apartment FOREIGN KEY (Apartment_ID) REFERENCES Apartments(Apartment_ID),
    CONSTRAINT fk_ap_pers_person FOREIGN KEY (Person_ID) REFERENCES Persons(Person_ID)
);

INSERT INTO Apartment_Persons (Apartment_ID, Person_ID, Is_Owner, Is_Resident) VALUES 

-- Живущи (наемател / собственик) в Building 1: Sofia, jk. Mladost 1, bl. 15
(1, 1, 'Yes', 'Yes'),
(2, 2, 'Yes', 'Yes'),
(3, 3, 'No', 'Yes'),
(4, 4, 'Yes', 'No'),
(4, 5, 'No', 'Yes'),
(5, 6, 'Yes', 'Yes'),
(6, 7, 'Yes', 'Yes'),
(7, 8, 'Yes', 'Yes'),
(8, 9, 'Yes', 'Yes'),
(9, 10, 'Yes', 'Yes'),
(10, 11, 'Yes', 'Yes'),
(11, 12, 'Yes', 'Yes'),
(12, 13, 'Yes', 'Yes'),
(13, 14, 'Yes', 'Yes'),
(14, 15, 'Yes', 'Yes'),
(15, 16, 'Yes', 'Yes'),
(16, 1, 'Yes', 'No'),

-- Живущи (наемател / собственик)  в Building 2: Sofia, jk. Musagenica, bl. 40
(17, 17, 'Yes', 'Yes'),
(18, 18, 'Yes', 'Yes'),
(19, 19, 'Yes', 'Yes'),
(20, 20, 'No', 'Yes'),
(21, 21, 'Yes', 'Yes'),
(22, 22, 'Yes', 'Yes'),
(23, 23, 'Yes', 'Yes'),
(24, 24, 'Yes', 'Yes'),
(25, 25, 'Yes', 'No'),
(26, 26, 'Yes', 'Yes'),
(27, 27, 'Yes', 'Yes'),
(28, 28, 'Yes', 'Yes'),
(29, 29, 'Yes', 'Yes'),
(30, 30, 'Yes', 'Yes'),
(31, 31, 'Yes', 'Yes'),

-- Живущи (наемател / собственик) в Building 3: Sofia, kv. Dragalevci, ul. Iv. Vazov
(32, 32, 'Yes', 'Yes'),
(33, 33, 'Yes', 'Yes'),
(34, 34, 'Yes', 'No'),
(35, 35, 'No', 'Yes'),
(36, 36, 'Yes', 'Yes'),
(37, 37, 'Yes', 'Yes'),

-- Живущи (наемател / собственик) в Building 4: Sofia, kv. Manastirski livadi, ul. Pirin
(38, 38, 'Yes', 'Yes'),
(39, 39, 'Yes', 'Yes'),
(40, 40, 'No', 'Yes'),
(41, 41, 'Yes', 'Yes'),
(42, 42, 'Yes', 'Yes'),
(43, 43, 'Yes', 'Yes'),
(44, 44, 'Yes', 'No'),
(45, 45, 'Yes', 'Yes'),
(46, 46, 'No', 'Yes'),
(47, 47, 'Yes', 'Yes'),
(48, 48, 'Yes', 'Yes'),
(49, 49, 'Yes', 'Yes'),

-- Живущи (наемател / собственик) в Building 5: Sofia, jk. Mladost 4, bl. 420
(50, 50, 'Yes', 'Yes'),
(51, 51, 'Yes', 'Yes'),
(52, 52, 'No', 'Yes'),
(53, 53, 'Yes', 'Yes'),
(54, 54, 'Yes', 'Yes'),
(55, 55, 'Yes', 'Yes'),
(56, 56, 'Yes', 'Yes'),
(57, 57, 'Yes', 'Yes'),
(58, 58, 'Yes', 'No'),
(59, 59, 'Yes', 'Yes'),
(60, 60, 'Yes', 'Yes'),
(61, 61, 'No', 'Yes'),
(62, 62, 'Yes', 'Yes'),
(63, 63, 'Yes', 'Yes'),
(64, 64, 'Yes', 'Yes'),
(65, 65, 'Yes', 'Yes'),
(66, 66, 'Yes', 'Yes'),
(67, 67, 'Yes', 'Yes'),
(68, 68, 'Yes', 'Yes'),
(69, 69, 'Yes', 'Yes'),
(70, 70, 'Yes', 'Yes'),
(71, 71, 'Yes', 'Yes'),
(72, 72, 'Yes', 'Yes'),
(73, 73, 'Yes', 'Yes'),

-- Живущи (наемател / собственик) в Building 6: Plovdiv, bul. Ruski, bl. 10
(74, 74, 'Yes', 'Yes'),
(75, 75, 'Yes', 'Yes'),
(76, 76, 'No', 'Yes'),
(77, 77, 'Yes', 'Yes'),
(78, 78, 'Yes', 'No'),
(79, 79, 'Yes', 'Yes'),
(80, 80, 'Yes', 'Yes'),
(81, 81, 'Yes', 'Yes'),
(82, 82, 'Yes', 'Yes'),
(83, 83, 'Yes', 'Yes'),

-- Живущи (наемател / собственик) в Building 7: Plovdiv, ul. Gladston, № 5
(84, 84, 'Yes', 'Yes'),
(85, 85, 'Yes', 'Yes'),
(86, 86, 'Yes', 'Yes'),
(87, 87, 'No', 'Yes'),
(88, 88, 'Yes', 'No'),

-- Живущи (наемател / собственик) в Building 8: Varna, jk. Chaika, bl. 18
(89, 89, 'Yes', 'Yes'),
(90, 90, 'Yes', 'Yes'),
(91, 91, 'No', 'Yes'),
(92, 92, 'Yes', 'Yes'),
(93, 93, 'Yes', 'Yes'),
(94, 94, 'Yes', 'Yes'),
(95, 95, 'Yes', 'No'),
(96, 96, 'Yes', 'Yes'),
(97, 97, 'Yes', 'Yes'),
(98, 98, 'Yes', 'Yes'),

-- Живущи (наемател / собственик) в Building 9: Burgas, jk. Lazur, bl. 5
(99, 99, 'Yes', 'Yes'),
(100, 100, 'Yes', 'Yes'),
(101, 101, 'No', 'Yes'),
(102, 102, 'Yes', 'Yes'),
(103, 103, 'Yes', 'Yes'),

-- Живущи (наемател / собственик) в Building 10: Ruse, ul. Aleksandrovska
(104, 104, 'Yes', 'Yes'),
(105, 105, 'Yes', 'Yes'),
(106, 106, 'Yes', 'Yes'),
(107, 107, 'No', 'Yes'),
(108, 108, 'Yes', 'No'),

-- Допълнителни живущи, които не са собственици 
(1, 109, 'No', 'Yes'),
(2, 110, 'No', 'Yes'),
(3, 111, 'No', 'Yes'),
(4, 112, 'No', 'Yes'),
(17, 113, 'No', 'Yes'),
(18, 114, 'No', 'Yes'),
(19, 115, 'No', 'Yes'),
(32, 116, 'No', 'Yes'),
(34, 117, 'No', 'Yes'),
(38, 118, 'No', 'Yes'),
(39, 119, 'No', 'Yes'),
(50, 120, 'No', 'Yes'),
(51, 121, 'No', 'Yes'),
(52, 122, 'No', 'Yes'),
(55, 123, 'No', 'Yes'),
(74, 124, 'No', 'Yes'),
(75, 125, 'No', 'Yes'),
(84, 126, 'No', 'Yes'),
(84, 127, 'No', 'Yes'),
(89, 128, 'No', 'Yes'),
(99, 129, 'No', 'Yes'),
(100, 130, 'No', 'Yes'),
(105, 131, 'No', 'Yes'),
(107, 132, 'No', 'Yes'),
(108, 133, 'No', 'Yes');

-- -------------------------------------------------------------------------
-- 7. Таблица за ремонти - за състоянието и историята на ремонтите във 
--    всеки вход.
-- -------------------------------------------------------------------------
CREATE TABLE Repairs (
    Repair_ID INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    Description TEXT NOT NULL,                             
    Status ENUM('Planned', 'In Progress', 'Completed') NOT NULL DEFAULT 'Planned',
    Cost DECIMAL(10, 2) NOT NULL,                          
    Date_Logged TIMESTAMP DEFAULT CURRENT_TIMESTAMP,       
    Building_ID INT,
    CONSTRAINT fk_repair_buildings FOREIGN KEY (Building_ID) REFERENCES Buildings(Building_ID)
);

INSERT INTO Repairs (Description, Status, Cost, Building_ID) VALUES 
-- Ремонти за Building 1 (Младост 1)
('Цялостен ремонт на покрива', 'Completed', 12500.00, 1),
('Смяна на осветлението със сензори', 'Completed', 850.00, 1),
('Боядисване на входа', 'Planned', 2200.00, 1),

-- Ремонти за Building 2 (Мусагеница)
('Смяна на главното ел. табло', 'Completed', 1800.00, 2),
('Подмяна на дограмата по етажите', 'In Progress', 4500.00, 2),

-- Ремонти за Building 3 (Драгалевци - луксозния блок)
('Озеленяване на вътрешния двор', 'Completed', 3200.00, 3),
('Профилактика на видеонаблюдението', 'Planned', 600.00, 3),

-- Ремонти за Building 4 (Манастирски ливади)
('Поправка на хидравликата на асансьора', 'Completed', 1100.00, 4),
('Ремонт на входната врата и контрола на достъп', 'In Progress', 450.00, 4),

-- Ремонти за Building 5 (Младост 4 - големия блок)
('Хидроизолация на покрива', 'In Progress', 18500.00, 5),
('Подмяна на пощенските кутии', 'Completed', 950.00, 5),

-- Ремонти за Пловдив (Buildings 6 и 7)
('Реставрация на фасадата', 'Planned', 25000.00, 6), -- Бул. Руски
('Смяна на щрангове - общи части', 'Completed', 5600.00, 7), -- Гладстон

-- Ремонти за Варна и Бургас (Buildings 8 и 9)
('Измазване на общите части след теч', 'Completed', 1300.00, 8),
('Почистване на улуци и водосточни тръби', 'Planned', 350.00, 9),

-- Ремонти за Русе (Building 10)
('Смяна на домофонната система', 'Completed', 1200.00, 10);

-- ----------------------------------------------------------------------------
-- 8. Таблица за задължения - кой апартамент колко дължи и дали си е платил
-- ----------------------------------------------------------------------------
CREATE TABLE Fees (
    Fee_ID INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    Fee_Month INT NOT NULL,               
    Fee_Year INT NOT NULL,
    Amount DECIMAL(10, 2) NOT NULL,
    Is_Paid ENUM('Yes', 'No') NOT NULL DEFAULT 'No',
    Payment_Date DATE DEFAULT NULL,      
    Apartment_ID INT,
    CONSTRAINT fk_fees_apartments FOREIGN KEY (Apartment_ID) REFERENCES Apartments(Apartment_ID)
);

-- Разпределение на таксите:

-- Гарсониера - 20.00 лв.
-- Ателие - 20.00 лв
-- Двустайни: 25.00 лв.
-- Тристайни: 35.00 лв.
-- Мезонети: 45.00 лв.
-- Penthouse - 45.00 лв.


-- ТАКСИ ЗА BUILDING 1 (Mladost 1, bl. 15) - Януари до Април 2026
-- =========================================================================

-- Месец 1: Януари 2026 (Неплатили: ап. 3, 14, 16)
INSERT INTO Fees (Fee_Month, Fee_Year, Amount, Is_Paid, Payment_Date, Apartment_ID) VALUES 
(1, 2026, 25.00, 'Yes', '2026-01-05', 1), (1, 2026, 35.00, 'Yes', '2026-01-05', 2),
(1, 2026, 25.00, 'No', NULL, 3),          (1, 2026, 35.00, 'Yes', '2026-01-10', 4),
(1, 2026, 25.00, 'Yes', '2026-01-12', 5), (1, 2026, 35.00, 'Yes', '2026-01-12', 6),
(1, 2026, 25.00, 'Yes', '2026-01-15', 7), (1, 2026, 35.00, 'Yes', '2026-01-15', 8),
(1, 2026, 25.00, 'Yes', '2026-01-18', 9), (1, 2026, 35.00, 'Yes', '2026-01-18', 10),
(1, 2026, 25.00, 'Yes', '2026-01-20', 11),(1, 2026, 35.00, 'Yes', '2026-01-20', 12),
(1, 2026, 25.00, 'Yes', '2026-01-22', 13),(1, 2026, 35.00, 'No', NULL, 14),
(1, 2026, 45.00, 'Yes', '2026-01-25', 15),(1, 2026, 45.00, 'No', NULL, 16);

-- Месец 2: Февруари 2026 (Неплатили: ап. 3, 9, 15)
INSERT INTO Fees (Fee_Month, Fee_Year, Amount, Is_Paid, Payment_Date, Apartment_ID) VALUES 
(2, 2026, 25.00, 'Yes', '2026-02-05', 1), (2, 2026, 35.00, 'Yes', '2026-02-06', 2),
(2, 2026, 25.00, 'No', NULL, 3),          (2, 2026, 35.00, 'Yes', '2026-02-10', 4),
(2, 2026, 25.00, 'Yes', '2026-02-11', 5), (2, 2026, 35.00, 'Yes', '2026-02-12', 6),
(2, 2026, 25.00, 'Yes', '2026-02-15', 7), (2, 2026, 35.00, 'Yes', '2026-02-16', 8),
(2, 2026, 25.00, 'No', NULL, 9),          (2, 2026, 35.00, 'Yes', '2026-02-18', 10),
(2, 2026, 25.00, 'Yes', '2026-02-20', 11),(2, 2026, 35.00, 'Yes', '2026-02-21', 12),
(2, 2026, 25.00, 'Yes', '2026-02-22', 13),(2, 2026, 35.00, 'Yes', '2026-02-24', 14),
(2, 2026, 45.00, 'No', NULL, 15),         (2, 2026, 45.00, 'Yes', '2026-02-28', 16);

-- Месец 3: Март 2026 (Неплатили: ап. 7, 9, 16)
INSERT INTO Fees (Fee_Month, Fee_Year, Amount, Is_Paid, Payment_Date, Apartment_ID) VALUES 
(3, 2026, 25.00, 'Yes', '2026-03-04', 1), (3, 2026, 35.00, 'Yes', '2026-03-05', 2),
(3, 2026, 25.00, 'Yes', '2026-03-08', 3), (3, 2026, 35.00, 'Yes', '2026-03-10', 4),
(3, 2026, 25.00, 'Yes', '2026-03-12', 5), (3, 2026, 35.00, 'Yes', '2026-03-12', 6),
(3, 2026, 25.00, 'No', NULL, 7),          (3, 2026, 35.00, 'Yes', '2026-03-15', 8),
(3, 2026, 25.00, 'No', NULL, 9),          (3, 2026, 35.00, 'Yes', '2026-03-18', 10),
(3, 2026, 25.00, 'Yes', '2026-03-20', 11),(3, 2026, 35.00, 'Yes', '2026-03-21', 12),
(3, 2026, 25.00, 'Yes', '2026-03-22', 13),(3, 2026, 35.00, 'Yes', '2026-03-23', 14),
(3, 2026, 45.00, 'Yes', '2026-03-25', 15),(3, 2026, 45.00, 'No', NULL, 16);

-- Месец 4: Април 2026 (Неплатили: ап. 3, 9, 12, 16 - повече длъжници, тъй като месецът тече)
INSERT INTO Fees (Fee_Month, Fee_Year, Amount, Is_Paid, Payment_Date, Apartment_ID) VALUES 
(4, 2026, 25.00, 'Yes', '2026-04-03', 1), (4, 2026, 35.00, 'Yes', '2026-04-05', 2),
(4, 2026, 25.00, 'No', NULL, 3),          (4, 2026, 35.00, 'Yes', '2026-04-08', 4),
(4, 2026, 25.00, 'Yes', '2026-04-10', 5), (4, 2026, 35.00, 'Yes', '2026-04-12', 6),
(4, 2026, 25.00, 'Yes', '2026-04-14', 7), (4, 2026, 35.00, 'Yes', '2026-04-15', 8),
(4, 2026, 25.00, 'No', NULL, 9),          (4, 2026, 35.00, 'Yes', '2026-04-18', 10),
(4, 2026, 25.00, 'Yes', '2026-04-19', 11),(4, 2026, 35.00, 'No', NULL, 12),
(4, 2026, 25.00, 'Yes', '2026-04-22', 13),(4, 2026, 35.00, 'Yes', '2026-04-24', 14),
(4, 2026, 45.00, 'Yes', '2026-04-26', 15),(4, 2026, 45.00, 'No', NULL, 16);


-- ТАКСИ ЗА BUILDING 2 (Musagenica, bl. 40) - Януари до Април 2026
-- =========================================================================

-- Месец 1: Януари 2026 (Неплатили: ап. 19, 23)
INSERT INTO Fees (Fee_Month, Fee_Year, Amount, Is_Paid, Payment_Date, Apartment_ID) VALUES 
(1, 2026, 20.00, 'Yes', '2026-01-04', 17), (1, 2026, 25.00, 'Yes', '2026-01-05', 18), (1, 2026, 25.00, 'No', NULL, 19),
(1, 2026, 20.00, 'Yes', '2026-01-08', 20), (1, 2026, 25.00, 'Yes', '2026-01-09', 21), (1, 2026, 25.00, 'Yes', '2026-01-10', 22),
(1, 2026, 20.00, 'No', NULL, 23),          (1, 2026, 25.00, 'Yes', '2026-01-12', 24), (1, 2026, 25.00, 'Yes', '2026-01-14', 25),
(1, 2026, 20.00, 'Yes', '2026-01-15', 26), (1, 2026, 25.00, 'Yes', '2026-01-16', 27), (1, 2026, 25.00, 'Yes', '2026-01-18', 28),
(1, 2026, 20.00, 'Yes', '2026-01-20', 29), (1, 2026, 25.00, 'Yes', '2026-01-22', 30), (1, 2026, 25.00, 'Yes', '2026-01-24', 31);

-- Месец 2: Февруари 2026 (Неплатили: ап. 19, 23, 28)
INSERT INTO Fees (Fee_Month, Fee_Year, Amount, Is_Paid, Payment_Date, Apartment_ID) VALUES 
(2, 2026, 20.00, 'Yes', '2026-02-03', 17), (2, 2026, 25.00, 'Yes', '2026-02-05', 18), (2, 2026, 25.00, 'No', NULL, 19),
(2, 2026, 20.00, 'Yes', '2026-02-06', 20), (2, 2026, 25.00, 'Yes', '2026-02-10', 21), (2, 2026, 25.00, 'Yes', '2026-02-12', 22),
(2, 2026, 20.00, 'No', NULL, 23),          (2, 2026, 25.00, 'Yes', '2026-02-14', 24), (2, 2026, 25.00, 'Yes', '2026-02-15', 25),
(2, 2026, 20.00, 'Yes', '2026-02-18', 26), (2, 2026, 25.00, 'Yes', '2026-02-19', 27), (2, 2026, 25.00, 'No', NULL, 28),
(2, 2026, 20.00, 'Yes', '2026-02-22', 29), (2, 2026, 25.00, 'Yes', '2026-02-23', 30), (2, 2026, 25.00, 'Yes', '2026-02-25', 31);

-- Месец 3: Март 2026 (Неплатили: ап. 19, 23, 31)
INSERT INTO Fees (Fee_Month, Fee_Year, Amount, Is_Paid, Payment_Date, Apartment_ID) VALUES 
(3, 2026, 20.00, 'Yes', '2026-03-02', 17), (3, 2026, 25.00, 'Yes', '2026-03-05', 18), (3, 2026, 25.00, 'No', NULL, 19),
(3, 2026, 20.00, 'Yes', '2026-03-08', 20), (3, 2026, 25.00, 'Yes', '2026-03-10', 21), (3, 2026, 25.00, 'Yes', '2026-03-12', 22),
(3, 2026, 20.00, 'No', NULL, 23),          (3, 2026, 25.00, 'Yes', '2026-03-14', 24), (3, 2026, 25.00, 'Yes', '2026-03-15', 25),
(3, 2026, 20.00, 'Yes', '2026-03-16', 26), (3, 2026, 25.00, 'Yes', '2026-03-18', 27), (3, 2026, 25.00, 'Yes', '2026-03-20', 28),
(3, 2026, 20.00, 'Yes', '2026-03-21', 29), (3, 2026, 25.00, 'Yes', '2026-03-23', 30), (3, 2026, 25.00, 'No', NULL, 31);

-- Месец 4: Април 2026 (Неплатили: ап. 19, 21, 23, 30)
INSERT INTO Fees (Fee_Month, Fee_Year, Amount, Is_Paid, Payment_Date, Apartment_ID) VALUES 
(4, 2026, 20.00, 'Yes', '2026-04-03', 17), (4, 2026, 25.00, 'Yes', '2026-04-05', 18), (4, 2026, 25.00, 'No', NULL, 19),
(4, 2026, 20.00, 'Yes', '2026-04-06', 20), (4, 2026, 25.00, 'No', NULL, 21),          (4, 2026, 25.00, 'Yes', '2026-04-10', 22),
(4, 2026, 20.00, 'No', NULL, 23),          (4, 2026, 25.00, 'Yes', '2026-04-12', 24), (4, 2026, 25.00, 'Yes', '2026-04-14', 25),
(4, 2026, 20.00, 'Yes', '2026-04-15', 26), (4, 2026, 25.00, 'Yes', '2026-04-16', 27), (4, 2026, 25.00, 'Yes', '2026-04-18', 28),
(4, 2026, 20.00, 'Yes', '2026-04-20', 29), (4, 2026, 25.00, 'No', NULL, 30),          (4, 2026, 25.00, 'Yes', '2026-04-22', 31);


-- ТАКСИ ЗА BUILDING 3 (Dragalevci, ul. Iv. Vazov) - Януари до Април 2026
-- =========================================================================

-- Месец 1: Януари 2026 (Неплатили: ап. 34)
INSERT INTO Fees (Fee_Month, Fee_Year, Amount, Is_Paid, Payment_Date, Apartment_ID) VALUES 
(1, 2026, 35.00, 'Yes', '2026-01-05', 32), (1, 2026, 35.00, 'Yes', '2026-01-06', 33),
(1, 2026, 35.00, 'No', NULL, 34),          (1, 2026, 35.00, 'Yes', '2026-01-10', 35),
(1, 2026, 45.00, 'Yes', '2026-01-12', 36), (1, 2026, 45.00, 'Yes', '2026-01-15', 37);

-- Месец 2: Февруари 2026 (Неплатили: ап. 34, 37)
INSERT INTO Fees (Fee_Month, Fee_Year, Amount, Is_Paid, Payment_Date, Apartment_ID) VALUES 
(2, 2026, 35.00, 'Yes', '2026-02-05', 32), (2, 2026, 35.00, 'Yes', '2026-02-08', 33),
(2, 2026, 35.00, 'No', NULL, 34),          (2, 2026, 35.00, 'Yes', '2026-02-11', 35),
(2, 2026, 45.00, 'Yes', '2026-02-14', 36), (2, 2026, 45.00, 'No', NULL, 37);

-- Месец 3: Март 2026 (Неплатили: ап. 34, 35, 37)
INSERT INTO Fees (Fee_Month, Fee_Year, Amount, Is_Paid, Payment_Date, Apartment_ID) VALUES 
(3, 2026, 35.00, 'Yes', '2026-03-04', 32), (3, 2026, 35.00, 'Yes', '2026-03-05', 33),
(3, 2026, 35.00, 'No', NULL, 34),          (3, 2026, 35.00, 'No', NULL, 35),
(3, 2026, 45.00, 'Yes', '2026-03-15', 36), (3, 2026, 45.00, 'No', NULL, 37);

-- Месец 4: Април 2026 (Неплатили: ап. 32, 34, 37)
INSERT INTO Fees (Fee_Month, Fee_Year, Amount, Is_Paid, Payment_Date, Apartment_ID) VALUES 
(4, 2026, 35.00, 'No', NULL, 32),          (4, 2026, 35.00, 'Yes', '2026-04-06', 33),
(4, 2026, 35.00, 'No', NULL, 34),          (4, 2026, 35.00, 'Yes', '2026-04-10', 35),
(4, 2026, 45.00, 'Yes', '2026-04-12', 36), (4, 2026, 45.00, 'No', NULL, 37);


-- ТАКСИ ЗА BUILDING 4 (Manastirski livadi, ul. Pirin) - Януари до Април 2026
-- =========================================================================

-- Месец 1: Януари 2026 (Неплатили: ап. 40, 49)
INSERT INTO Fees (Fee_Month, Fee_Year, Amount, Is_Paid, Payment_Date, Apartment_ID) VALUES 
(1, 2026, 25.00, 'Yes', '2026-01-05', 38), (1, 2026, 25.00, 'Yes', '2026-01-06', 39),
(1, 2026, 25.00, 'No', NULL, 40),          (1, 2026, 25.00, 'Yes', '2026-01-08', 41),
(1, 2026, 25.00, 'Yes', '2026-01-10', 42), (1, 2026, 25.00, 'Yes', '2026-01-12', 43),
(1, 2026, 25.00, 'Yes', '2026-01-14', 44), (1, 2026, 25.00, 'Yes', '2026-01-15', 45),
(1, 2026, 25.00, 'Yes', '2026-01-18', 46), (1, 2026, 25.00, 'Yes', '2026-01-20', 47),
(1, 2026, 35.00, 'Yes', '2026-01-22', 48), (1, 2026, 35.00, 'No', NULL, 49);

-- Месец 2: Февруари 2026 (Неплатили: ап. 40, 44, 49)
INSERT INTO Fees (Fee_Month, Fee_Year, Amount, Is_Paid, Payment_Date, Apartment_ID) VALUES 
(2, 2026, 25.00, 'Yes', '2026-02-04', 38), (2, 2026, 25.00, 'Yes', '2026-02-05', 39),
(2, 2026, 25.00, 'No', NULL, 40),          (2, 2026, 25.00, 'Yes', '2026-02-08', 41),
(2, 2026, 25.00, 'Yes', '2026-02-11', 42), (2, 2026, 25.00, 'Yes', '2026-02-12', 43),
(2, 2026, 25.00, 'No', NULL, 44),          (2, 2026, 25.00, 'Yes', '2026-02-15', 45),
(2, 2026, 25.00, 'Yes', '2026-02-18', 46), (2, 2026, 25.00, 'Yes', '2026-02-20', 47),
(2, 2026, 35.00, 'Yes', '2026-02-21', 48), (2, 2026, 35.00, 'No', NULL, 49);

-- Месец 3: Март 2026 (Неплатили: ап. 40, 47, 49)
INSERT INTO Fees (Fee_Month, Fee_Year, Amount, Is_Paid, Payment_Date, Apartment_ID) VALUES 
(3, 2026, 25.00, 'Yes', '2026-03-03', 38), (3, 2026, 25.00, 'Yes', '2026-03-05', 39),
(3, 2026, 25.00, 'No', NULL, 40),          (3, 2026, 25.00, 'Yes', '2026-03-07', 41),
(3, 2026, 25.00, 'Yes', '2026-03-10', 42), (3, 2026, 25.00, 'Yes', '2026-03-12', 43),
(3, 2026, 25.00, 'Yes', '2026-03-14', 44), (3, 2026, 25.00, 'Yes', '2026-03-15', 45),
(3, 2026, 25.00, 'Yes', '2026-03-18', 46), (3, 2026, 25.00, 'No', NULL, 47),
(3, 2026, 35.00, 'Yes', '2026-03-22', 48), (3, 2026, 35.00, 'No', NULL, 49);

-- Месец 4: Април 2026 (Неплатили: ап. 40, 44, 48, 49)
INSERT INTO Fees (Fee_Month, Fee_Year, Amount, Is_Paid, Payment_Date, Apartment_ID) VALUES 
(4, 2026, 25.00, 'Yes', '2026-04-02', 38), (4, 2026, 25.00, 'Yes', '2026-04-05', 39),
(4, 2026, 25.00, 'No', NULL, 40),          (4, 2026, 25.00, 'Yes', '2026-04-08', 41),
(4, 2026, 25.00, 'Yes', '2026-04-10', 42), (4, 2026, 25.00, 'Yes', '2026-04-12', 43),
(4, 2026, 25.00, 'No', NULL, 44),          (4, 2026, 25.00, 'Yes', '2026-04-15', 45),
(4, 2026, 25.00, 'Yes', '2026-04-18', 46), (4, 2026, 25.00, 'Yes', '2026-04-20', 47),
(4, 2026, 35.00, 'No', NULL, 48),          (4, 2026, 35.00, 'No', NULL, 49);


-- ТАКСИ ЗА BUILDING 5 (Mladost 4, bl. 420) - Януари до Април 2026
-- =========================================================================

-- Месец 1: Януари 2026 (Хронични длъжници: 55, 62, 72)
INSERT INTO Fees (Fee_Month, Fee_Year, Amount, Is_Paid, Payment_Date, Apartment_ID) VALUES 
(1, 2026, 20.00, 'Yes', '2026-01-05', 50), (1, 2026, 25.00, 'Yes', '2026-01-06', 51), (1, 2026, 25.00, 'Yes', '2026-01-06', 52),
(1, 2026, 20.00, 'Yes', '2026-01-08', 53), (1, 2026, 25.00, 'Yes', '2026-01-08', 54), (1, 2026, 25.00, 'No', NULL, 55),
(1, 2026, 20.00, 'Yes', '2026-01-10', 56), (1, 2026, 25.00, 'Yes', '2026-01-11', 57), (1, 2026, 25.00, 'Yes', '2026-01-12', 58),
(1, 2026, 20.00, 'Yes', '2026-01-14', 59), (1, 2026, 25.00, 'Yes', '2026-01-15', 60), (1, 2026, 25.00, 'Yes', '2026-01-15', 61),
(1, 2026, 20.00, 'No', NULL, 62),          (1, 2026, 25.00, 'Yes', '2026-01-16', 63), (1, 2026, 25.00, 'Yes', '2026-01-18', 64),
(1, 2026, 20.00, 'Yes', '2026-01-20', 65), (1, 2026, 25.00, 'Yes', '2026-01-21', 66), (1, 2026, 25.00, 'Yes', '2026-01-22', 67),
(1, 2026, 20.00, 'Yes', '2026-01-24', 68), (1, 2026, 25.00, 'Yes', '2026-01-25', 69), (1, 2026, 25.00, 'Yes', '2026-01-26', 70),
(1, 2026, 45.00, 'Yes', '2026-01-28', 71), (1, 2026, 45.00, 'No', NULL, 72),          (1, 2026, 45.00, 'Yes', '2026-01-29', 73);

-- Месец 2: Февруари 2026 (Длъжници: 55, 62, 72 + 68)
INSERT INTO Fees (Fee_Month, Fee_Year, Amount, Is_Paid, Payment_Date, Apartment_ID) VALUES 
(2, 2026, 20.00, 'Yes', '2026-02-04', 50), (2, 2026, 25.00, 'Yes', '2026-02-05', 51), (2, 2026, 25.00, 'Yes', '2026-02-06', 52),
(2, 2026, 20.00, 'Yes', '2026-02-08', 53), (2, 2026, 25.00, 'Yes', '2026-02-09', 54), (2, 2026, 25.00, 'No', NULL, 55),
(2, 2026, 20.00, 'Yes', '2026-02-10', 56), (2, 2026, 25.00, 'Yes', '2026-02-12', 57), (2, 2026, 25.00, 'Yes', '2026-02-12', 58),
(2, 2026, 20.00, 'Yes', '2026-02-14', 59), (2, 2026, 25.00, 'Yes', '2026-02-15', 60), (2, 2026, 25.00, 'Yes', '2026-02-16', 61),
(2, 2026, 20.00, 'No', NULL, 62),          (2, 2026, 25.00, 'Yes', '2026-02-18', 63), (2, 2026, 25.00, 'Yes', '2026-02-19', 64),
(2, 2026, 20.00, 'Yes', '2026-02-20', 65), (2, 2026, 25.00, 'Yes', '2026-02-21', 66), (2, 2026, 25.00, 'Yes', '2026-02-22', 67),
(2, 2026, 20.00, 'No', NULL, 68),          (2, 2026, 25.00, 'Yes', '2026-02-24', 69), (2, 2026, 25.00, 'Yes', '2026-02-25', 70),
(2, 2026, 45.00, 'Yes', '2026-02-26', 71), (2, 2026, 45.00, 'No', NULL, 72),          (2, 2026, 45.00, 'Yes', '2026-02-28', 73);

-- Месец 3: Март 2026 (Длъжници: 55, 62, 72 + 59)
INSERT INTO Fees (Fee_Month, Fee_Year, Amount, Is_Paid, Payment_Date, Apartment_ID) VALUES 
(3, 2026, 20.00, 'Yes', '2026-03-03', 50), (3, 2026, 25.00, 'Yes', '2026-03-05', 51), (3, 2026, 25.00, 'Yes', '2026-03-05', 52),
(3, 2026, 20.00, 'Yes', '2026-03-08', 53), (3, 2026, 25.00, 'Yes', '2026-03-09', 54), (3, 2026, 25.00, 'No', NULL, 55),
(3, 2026, 20.00, 'Yes', '2026-03-10', 56), (3, 2026, 25.00, 'Yes', '2026-03-11', 57), (3, 2026, 25.00, 'Yes', '2026-03-12', 58),
(3, 2026, 20.00, 'No', NULL, 59),          (3, 2026, 25.00, 'Yes', '2026-03-14', 60), (3, 2026, 25.00, 'Yes', '2026-03-15', 61),
(3, 2026, 20.00, 'No', NULL, 62),          (3, 2026, 25.00, 'Yes', '2026-03-17', 63), (3, 2026, 25.00, 'Yes', '2026-03-18', 64),
(3, 2026, 20.00, 'Yes', '2026-03-20', 65), (3, 2026, 25.00, 'Yes', '2026-03-22', 66), (3, 2026, 25.00, 'Yes', '2026-03-22', 67),
(3, 2026, 20.00, 'Yes', '2026-03-24', 68), (3, 2026, 25.00, 'Yes', '2026-03-25', 69), (3, 2026, 25.00, 'Yes', '2026-03-26', 70),
(3, 2026, 45.00, 'Yes', '2026-03-28', 71), (3, 2026, 45.00, 'No', NULL, 72),          (3, 2026, 45.00, 'Yes', '2026-03-29', 73);

-- Месец 4: Април 2026 (Длъжници: 55, 62, 72 + 51, 68 - повече неплатили в края на месеца)
INSERT INTO Fees (Fee_Month, Fee_Year, Amount, Is_Paid, Payment_Date, Apartment_ID) VALUES 
(4, 2026, 20.00, 'Yes', '2026-04-02', 50), (4, 2026, 25.00, 'No', NULL, 51),          (4, 2026, 25.00, 'Yes', '2026-04-05', 52),
(4, 2026, 20.00, 'Yes', '2026-04-06', 53), (4, 2026, 25.00, 'Yes', '2026-04-08', 54), (4, 2026, 25.00, 'No', NULL, 55),
(4, 2026, 20.00, 'Yes', '2026-04-10', 56), (4, 2026, 25.00, 'Yes', '2026-04-11', 57), (4, 2026, 25.00, 'Yes', '2026-04-12', 58),
(4, 2026, 20.00, 'Yes', '2026-04-14', 59), (4, 2026, 25.00, 'Yes', '2026-04-14', 60), (4, 2026, 25.00, 'Yes', '2026-04-15', 61),
(4, 2026, 20.00, 'No', NULL, 62),          (4, 2026, 25.00, 'Yes', '2026-04-17', 63), (4, 2026, 25.00, 'Yes', '2026-04-18', 64),
(4, 2026, 20.00, 'Yes', '2026-04-19', 65), (4, 2026, 25.00, 'Yes', '2026-04-20', 66), (4, 2026, 25.00, 'Yes', '2026-04-21', 67),
(4, 2026, 20.00, 'No', NULL, 68),          (4, 2026, 25.00, 'Yes', '2026-04-24', 69), (4, 2026, 25.00, 'Yes', '2026-04-25', 70),
(4, 2026, 45.00, 'Yes', '2026-04-26', 71), (4, 2026, 45.00, 'No', NULL, 72),          (4, 2026, 45.00, 'Yes', '2026-04-28', 73);


-- ТАКСИ ЗА BUILDING 6 (Plovdiv, bul. Ruski) - Януари до Април 2026
-- =========================================================================

-- Месец 1: Януари 2026 (Длъжници: ап. 76, 82)
INSERT INTO Fees (Fee_Month, Fee_Year, Amount, Is_Paid, Payment_Date, Apartment_ID) VALUES 
(1, 2026, 35.00, 'Yes', '2026-01-05', 74), (1, 2026, 35.00, 'Yes', '2026-01-06', 75),
(1, 2026, 35.00, 'No', NULL, 76),          (1, 2026, 35.00, 'Yes', '2026-01-09', 77),
(1, 2026, 35.00, 'Yes', '2026-01-12', 78), (1, 2026, 35.00, 'Yes', '2026-01-14', 79),
(1, 2026, 35.00, 'Yes', '2026-01-16', 80), (1, 2026, 35.00, 'Yes', '2026-01-18', 81),
(1, 2026, 45.00, 'No', NULL, 82),          (1, 2026, 45.00, 'Yes', '2026-01-22', 83);

-- Месец 2: Февруари 2026 (Длъжници: ап. 76, 82)
INSERT INTO Fees (Fee_Month, Fee_Year, Amount, Is_Paid, Payment_Date, Apartment_ID) VALUES 
(2, 2026, 35.00, 'Yes', '2026-02-04', 74), (2, 2026, 35.00, 'Yes', '2026-02-05', 75),
(2, 2026, 35.00, 'No', NULL, 76),          (2, 2026, 35.00, 'Yes', '2026-02-08', 77),
(2, 2026, 35.00, 'Yes', '2026-02-11', 78), (2, 2026, 35.00, 'Yes', '2026-02-13', 79),
(2, 2026, 35.00, 'Yes', '2026-02-15', 80), (2, 2026, 35.00, 'Yes', '2026-02-17', 81),
(2, 2026, 45.00, 'No', NULL, 82),          (2, 2026, 45.00, 'Yes', '2026-02-20', 83);

-- Месец 3: Март 2026 (Длъжници: ап. 76, 82)
INSERT INTO Fees (Fee_Month, Fee_Year, Amount, Is_Paid, Payment_Date, Apartment_ID) VALUES 
(3, 2026, 35.00, 'Yes', '2026-03-03', 74), (3, 2026, 35.00, 'Yes', '2026-03-04', 75),
(3, 2026, 35.00, 'No', NULL, 76),          (3, 2026, 35.00, 'Yes', '2026-03-07', 77),
(3, 2026, 35.00, 'Yes', '2026-03-10', 78), (3, 2026, 35.00, 'Yes', '2026-03-12', 79),
(3, 2026, 35.00, 'Yes', '2026-03-14', 80), (3, 2026, 35.00, 'Yes', '2026-03-16', 81),
(3, 2026, 45.00, 'No', NULL, 82),          (3, 2026, 45.00, 'Yes', '2026-03-19', 83);

-- Месец 4: Април 2026 (Длъжници: ап. 76, 80, 82 - ап. 80 закъснява в края на месеца)
INSERT INTO Fees (Fee_Month, Fee_Year, Amount, Is_Paid, Payment_Date, Apartment_ID) VALUES 
(4, 2026, 35.00, 'Yes', '2026-04-02', 74), (4, 2026, 35.00, 'Yes', '2026-04-05', 75),
(4, 2026, 35.00, 'No', NULL, 76),          (4, 2026, 35.00, 'Yes', '2026-04-06', 77),
(4, 2026, 35.00, 'Yes', '2026-04-09', 78), (4, 2026, 35.00, 'Yes', '2026-04-11', 79),
(4, 2026, 35.00, 'No', NULL, 80),          (4, 2026, 35.00, 'Yes', '2026-04-15', 81),
(4, 2026, 45.00, 'No', NULL, 82),          (4, 2026, 45.00, 'Yes', '2026-04-18', 83);


-- ТАКСИ ЗА BUILDING 7 (Plovdiv, ul. Gladston, № 5) - Януари до Април 2026
-- =========================================================================

-- Месец 1: Януари 2026 (Длъжници: ап. 87, 88)
INSERT INTO Fees (Fee_Month, Fee_Year, Amount, Is_Paid, Payment_Date, Apartment_ID) VALUES 
(1, 2026, 35.00, 'Yes', '2026-01-05', 84), (1, 2026, 35.00, 'Yes', '2026-01-06', 85),
(1, 2026, 35.00, 'Yes', '2026-01-10', 86), (1, 2026, 35.00, 'No', NULL, 87),
(1, 2026, 35.00, 'No', NULL, 88);

-- Месец 2: Февруари 2026 (Длъжници: ап. 85, 87)
INSERT INTO Fees (Fee_Month, Fee_Year, Amount, Is_Paid, Payment_Date, Apartment_ID) VALUES 
(2, 2026, 35.00, 'Yes', '2026-02-05', 84), (2, 2026, 35.00, 'No', NULL, 85),
(2, 2026, 35.00, 'Yes', '2026-02-10', 86), (2, 2026, 35.00, 'No', NULL, 87),
(2, 2026, 35.00, 'Yes', '2026-02-15', 88);

-- Месец 3: Март 2026 (Длъжници: ап. 86, 87)
INSERT INTO Fees (Fee_Month, Fee_Year, Amount, Is_Paid, Payment_Date, Apartment_ID) VALUES 
(3, 2026, 35.00, 'Yes', '2026-03-05', 84), (3, 2026, 35.00, 'Yes', '2026-03-06', 85),
(3, 2026, 35.00, 'No', NULL, 86),          (3, 2026, 35.00, 'No', NULL, 87),
(3, 2026, 35.00, 'Yes', '2026-03-15', 88);

-- Месец 4: Април 2026 (Длъжници: ап. 84, 87, 88)
INSERT INTO Fees (Fee_Month, Fee_Year, Amount, Is_Paid, Payment_Date, Apartment_ID) VALUES 
(4, 2026, 35.00, 'No', NULL, 84),          (4, 2026, 35.00, 'Yes', '2026-04-06', 85),
(4, 2026, 35.00, 'Yes', '2026-04-10', 86), (4, 2026, 35.00, 'No', NULL, 87),
(4, 2026, 35.00, 'No', NULL, 88);


-- ТАКСИ ЗА BUILDING 8 (Varna, Chaika, bl. 18) - Януари до Април 2026
-- =========================================================================

-- Месец 1: Януари 2026 (Длъжници: ап. 91, 98)
INSERT INTO Fees (Fee_Month, Fee_Year, Amount, Is_Paid, Payment_Date, Apartment_ID) VALUES 
(1, 2026, 25.00, 'Yes', '2026-01-05', 89), (1, 2026, 25.00, 'Yes', '2026-01-06', 90),
(1, 2026, 25.00, 'No', NULL, 91),          (1, 2026, 25.00, 'Yes', '2026-01-08', 92),
(1, 2026, 25.00, 'Yes', '2026-01-10', 93), (1, 2026, 25.00, 'Yes', '2026-01-12', 94),
(1, 2026, 25.00, 'Yes', '2026-01-14', 95), (1, 2026, 25.00, 'Yes', '2026-01-15', 96),
(1, 2026, 35.00, 'Yes', '2026-01-18', 97), (1, 2026, 35.00, 'No', NULL, 98);

-- Месец 2: Февруари 2026 (Длъжници: ап. 91, 95, 98)
INSERT INTO Fees (Fee_Month, Fee_Year, Amount, Is_Paid, Payment_Date, Apartment_ID) VALUES 
(2, 2026, 25.00, 'Yes', '2026-02-04', 89), (2, 2026, 25.00, 'Yes', '2026-02-05', 90),
(2, 2026, 25.00, 'No', NULL, 91),          (2, 2026, 25.00, 'Yes', '2026-02-08', 92),
(2, 2026, 25.00, 'Yes', '2026-02-10', 93), (2, 2026, 25.00, 'Yes', '2026-02-12', 94),
(2, 2026, 25.00, 'No', NULL, 95),          (2, 2026, 25.00, 'Yes', '2026-02-16', 96),
(2, 2026, 35.00, 'Yes', '2026-02-18', 97), (2, 2026, 35.00, 'No', NULL, 98);

-- Месец 3: Март 2026 (Длъжници: ап. 91, 93, 98)
INSERT INTO Fees (Fee_Month, Fee_Year, Amount, Is_Paid, Payment_Date, Apartment_ID) VALUES 
(3, 2026, 25.00, 'Yes', '2026-03-03', 89), (3, 2026, 25.00, 'Yes', '2026-03-04', 90),
(3, 2026, 25.00, 'No', NULL, 91),          (3, 2026, 25.00, 'Yes', '2026-03-07', 92),
(3, 2026, 25.00, 'No', NULL, 93),          (3, 2026, 25.00, 'Yes', '2026-03-12', 94),
(3, 2026, 25.00, 'Yes', '2026-03-14', 95), (3, 2026, 25.00, 'Yes', '2026-03-15', 96),
(3, 2026, 35.00, 'Yes', '2026-03-18', 97), (3, 2026, 35.00, 'No', NULL, 98);

-- Месец 4: Април 2026 (Длъжници: ап. 89, 91, 97, 98)
INSERT INTO Fees (Fee_Month, Fee_Year, Amount, Is_Paid, Payment_Date, Apartment_ID) VALUES 
(4, 2026, 25.00, 'No', NULL, 89),          (4, 2026, 25.00, 'Yes', '2026-04-05', 90),
(4, 2026, 25.00, 'No', NULL, 91),          (4, 2026, 25.00, 'Yes', '2026-04-08', 92),
(4, 2026, 25.00, 'Yes', '2026-04-10', 93), (4, 2026, 25.00, 'Yes', '2026-04-12', 94),
(4, 2026, 25.00, 'Yes', '2026-04-14', 95), (4, 2026, 25.00, 'Yes', '2026-04-16', 96),
(4, 2026, 35.00, 'No', NULL, 97),          (4, 2026, 35.00, 'No', NULL, 98);


-- ТАКСИ ЗА BUILDING 9 (Burgas, jk. Lazur, bl. 5) - Януари до Април 2026
-- =========================================================================

-- Месец 1: Януари 2026 (Длъжници: ап. 101, 103)
INSERT INTO Fees (Fee_Month, Fee_Year, Amount, Is_Paid, Payment_Date, Apartment_ID) VALUES 
(1, 2026, 35.00, 'Yes', '2026-01-05', 99), (1, 2026, 35.00, 'Yes', '2026-01-08', 100),
(1, 2026, 35.00, 'No', NULL, 101),         (1, 2026, 35.00, 'Yes', '2026-01-12', 102),
(1, 2026, 35.00, 'No', NULL, 103);

-- Месец 2: Февруари 2026 (Длъжници: ап. 101, 102)
INSERT INTO Fees (Fee_Month, Fee_Year, Amount, Is_Paid, Payment_Date, Apartment_ID) VALUES 
(2, 2026, 35.00, 'Yes', '2026-02-04', 99), (2, 2026, 35.00, 'Yes', '2026-02-09', 100),
(2, 2026, 35.00, 'No', NULL, 101),         (2, 2026, 35.00, 'No', NULL, 102),
(2, 2026, 35.00, 'Yes', '2026-02-15', 103);

-- Месец 3: Март 2026 (Длъжници: ап. 99, 101)
INSERT INTO Fees (Fee_Month, Fee_Year, Amount, Is_Paid, Payment_Date, Apartment_ID) VALUES 
(3, 2026, 35.00, 'No', NULL, 99),          (3, 2026, 35.00, 'Yes', '2026-03-05', 100),
(3, 2026, 35.00, 'No', NULL, 101),         (3, 2026, 35.00, 'Yes', '2026-03-10', 102),
(3, 2026, 35.00, 'Yes', '2026-03-14', 103);

-- Месец 4: Април 2026 (Длъжници: ап. 101, 102, 103 - в края на месеца)
INSERT INTO Fees (Fee_Month, Fee_Year, Amount, Is_Paid, Payment_Date, Apartment_ID) VALUES 
(4, 2026, 35.00, 'Yes', '2026-04-03', 99), (4, 2026, 35.00, 'Yes', '2026-04-07', 100),
(4, 2026, 35.00, 'No', NULL, 101),         (4, 2026, 35.00, 'No', NULL, 102),
(4, 2026, 35.00, 'No', NULL, 103);


-- ТАКСИ ЗА BUILDING 10 (Ruse, ul. Aleksandrovska) - Януари до Април 2026
-- =========================================================================
-
-- Месец 1: Януари 2026 (Длъжници: ап. 106, 108)
INSERT INTO Fees (Fee_Month, Fee_Year, Amount, Is_Paid, Payment_Date, Apartment_ID) VALUES 
(1, 2026, 20.00, 'Yes', '2026-01-04', 104), (1, 2026, 20.00, 'Yes', '2026-01-08', 105),
(1, 2026, 20.00, 'No', NULL, 106),          (1, 2026, 20.00, 'Yes', '2026-01-12', 107),
(1, 2026, 20.00, 'No', NULL, 108);

-- Месец 2: Февруари 2026 (Длъжници: ап. 104, 106)
INSERT INTO Fees (Fee_Month, Fee_Year, Amount, Is_Paid, Payment_Date, Apartment_ID) VALUES 
(2, 2026, 20.00, 'No', NULL, 104),          (2, 2026, 20.00, 'Yes', '2026-02-07', 105),
(2, 2026, 20.00, 'No', NULL, 106),          (2, 2026, 20.00, 'Yes', '2026-02-14', 107),
(2, 2026, 20.00, 'Yes', '2026-02-18', 108);

-- Месец 3: Март 2026 (Длъжници: ап. 106, 107)
INSERT INTO Fees (Fee_Month, Fee_Year, Amount, Is_Paid, Payment_Date, Apartment_ID) VALUES 
(3, 2026, 20.00, 'Yes', '2026-03-05', 104), (3, 2026, 20.00, 'Yes', '2026-03-09', 105),
(3, 2026, 20.00, 'No', NULL, 106),          (3, 2026, 20.00, 'No', NULL, 107),
(3, 2026, 20.00, 'Yes', '2026-03-15', 108);

-- Месец 4: Април 2026 (Длъжници: ап. 105, 106, 108)
INSERT INTO Fees (Fee_Month, Fee_Year, Amount, Is_Paid, Payment_Date, Apartment_ID) VALUES 
(4, 2026, 20.00, 'Yes', '2026-04-04', 104), (4, 2026, 20.00, 'No', NULL, 105),
(4, 2026, 20.00, 'No', NULL, 106),          (4, 2026, 20.00, 'Yes', '2026-04-10', 107),
(4, 2026, 20.00, 'No', NULL, 108);