create table CAR
(
  MAKE VARCHAR(50) not null primary key,
  MODEL VARCHAR(50),
  PRICE INTEGER,
  BODY_STYLE VARCHAR(30),
  COLOR VARCHAR(20),
  SUN_ROOF INTEGER default 0,
  SPOILER INTEGER default 0,
  TIRE_SIZE INTEGER,
  TIRE_TYPE INTEGER,
  MODERNNESS INTEGER
);
insert into car values ('Acura', 'NSX', 47075, 'coupe', 'yellow', 1, 1, 18, 1, 38);
insert into car values ('Audi', 'A8', 63890, 'sedan', 'black', 1, 0, 24, 0, 88);
insert into car values ('BMW', 'M-Series', 108900, 'coupe', 'red', 1, 0, 50, 0, 44);
insert into car values ('Buick', 'Lucerne', 31599, 'sedan', 'black', 1, 0, 26, 2, 65);
insert into car values ('Cadilac', 'XLR', 62777, 'convertible', 'green', 0, 0, 14, 1, 26);
insert into car values ('Chevrolet', 'Corvette', 74999, 'coupe', 'yellow', 0, 0, 53, 2, 44);
insert into car values ('Chrysler', 'Sebring', 89595, 'convertible', 'silver', 1, 1, 63, 0, 49);
insert into car values ('Daewoo', 'Leganza', 10590, 'sedan', 'blue', 1, 0, 47, 1, 66);
insert into car values ('Dodge', 'Ram 2500', 38825, 'pickup', 'white', 0, 1, 96, 1, 82);
insert into car values ('Eagle', 'Talon', 5995, 'hatchback', 'silver', 1, 1, 42, 1, 53);
insert into car values ('Ford', 'F250', 47440, 'pickup', 'orange', 0, 1, 46, 1, 57);
insert into car values ('Geo', 'Metro LSI', 3495, 'convertible', 'green', 0, 1, 54, 0, 74);
insert into car values ('GMC', 'Yukon XL Denali', 46355, 'wagon', 'gray', 0, 1, 63, 1, 45);
insert into car values ('Honda', 'Odyssey', 34895, 'coupe', 'white', 1, 1, 11, 2, 68);
insert into car values ('Hummer', 'H1', 119999, 'sedan', 'red', 1, 1, 39, 0, 17);
insert into car values ('Hyundai', 'Azera', 27950, 'sedan', 'silver', 1, 1, 13, 0, 18);
insert into car values ('Infiniti', 'QX56', 44995, 'wagon', 'green', 0, 0, 15, 2, 75);
insert into car values ('Isuzu', 'Hombre', 30545, 'wagon', 'white', 1, 0, 16, 2, 55);
insert into car values ('Jaguar', 'XK', 91675, 'convertible', 'brown', 1, 1, 17, 2, 31);
insert into car values ('Jeep', 'Commander', 37497, 'wagon', 'silver', 1, 1, 54, 0, 96);
insert into car values ('Kia', 'Amanti', 25988, 'sedan', 'gray', 1, 1, 62, 0, 100);
insert into car values ('Land Rover', 'Range Rover', 89350, 'wagon', 'black', 0, 1, 71, 0, 63);
insert into car values ('Lexus', 'SC 430', 61321, 'convertible', 'yellow', 1, 1, 81, 0, 98);
insert into car values ('Lincoln', 'Navigator', 42500, 'wagon', 'blue', 1, 1, 46, 0, 85);
insert into car values ('Mazda', 'CX-7', 27988, 'wagon', 'brown', 1, 0, 28, 0, 40);
insert into car values ('Mercedes-Benz', 'CLS Class', 86900, 'sedan', 'black', 0, 1, 99, 1, 46);
insert into car values ('Mercury', 'Mariner', 30995, 'wagon', 'red', 0, 0, 59, 2, 41);
insert into car values ('MINI', 'Cooper', 32930, 'convertible', 'silver', 0, 0, 78, 1, 98);
insert into car values ('Mitsubishi', 'Eclipse', 31995, 'convertible', 'red', 0, 0, 83, 1, 48);
insert into car values ('Nissan', 'Armada', 36777, 'wagon', 'blue', 0, 1, 11, 1, 60);
insert into car values ('Oldsmobile', 'Silhouette', 17500, 'wagon', 'blue', 1, 1, 79, 1, 27);
insert into car values ('Plymouth', 'Voyager', 9995, 'wagon', 'white', 1, 1, 37, 1, 13);
insert into car values ('Pontiac', 'Firebird', 39999, 'hatchback', 'red', 0, 0, 13, 0, 18);
insert into car values ('Porche', '911 Carrera', 399999, 'coupe', 'silver', 1, 0, 18, 2, 58);
insert into car values ('Saab', '9-3', 35999, 'convertible', 'green', 1, 1, 16, 0, 13);
insert into car values ('Saturn', 'Sky', 27499, 'convertible', 'silver', 1, 1, 25, 0, 86);
insert into car values ('Scion', 'tC', 21530, 'sedan', 'red', 0, 0, 92, 1, 37);
insert into car values ('Subaru', 'B9 Tribeca', 34999, 'wagon', 'green', 0, 1, 98, 0, 88);
insert into car values ('Suzuki', 'XL-7', 25880, 'wagon', 'brown', 1, 0, 83, 1, 16);
insert into car values ('Toytota', 'MR2 Spyder', 99999, 'convertible', 'silver', 0, 0, 21, 2, 99);
insert into car values ('Volkswagen', 'Touareg', 51274, 'wagon', 'black', 1, 0, 91, 0, 48);
insert into car values ('Volvo', 'XC90', 45845, 'wagon', 'gray', 0, 0, 31, 2, 32);
