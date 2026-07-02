package Parking;

import java.io.*;
import java.net.*;
import java.util.*;

// Класът за паркомястото (Изпълнява изречение 7 от условието)
/*public*/class ParkingSpot {
    public int id;              // уникален идентификатор
    public int number;          // номер на мястото
    public String clientName;   // име на клиента
    public boolean isFree;      // информация дали е заето/свободно
}

public class ParkingServer {
    public static void main(String[] args){

        try {
            ServerSocket serverSocket = new ServerSocket(1643);
            System.out.println("Сървърът е стартиран на порт 1643");

            List<ParkingSpot> spots = new ArrayList<>();
            // Създаваме 5 примерни места
            for (int i = 1; i <= 5; i++) {
                ParkingSpot p = new ParkingSpot();
                p.id = i;
                p.number = 100 + i;
                p.isFree = true; // Първоначално са свободни
                spots.add(p);
            }

            while (true) {
                Socket clientSocket = serverSocket.accept();
                System.out.println("Нов клиент се свърза.");

                ClientHandler handler = new ClientHandler();
                handler.socket = clientSocket; // Подаваме сокета директно

                // Сървърът притежава данните от списъка в main, а обекта от класа с нишките получава достъп да ги използва
                handler.spots = spots; // Подаваме списъка на нишката

                Thread thread = new Thread(handler); // Създаваме нишката
                thread.start(); // Стартираме я

            }
        }
        catch (IOException e) {
            e.printStackTrace();
        }
    }
}

// Правим го static, за да може main методът да го създава директно.
/*static*/ class ClientHandler implements Runnable {
    public Socket socket; // Публично поле, за да го зададем без конструктор
    public List<ParkingSpot> spots; //поле което сочи списъка

    @Override
    public void run() {
        try {
            // 1. Подготвяме инструментите (Вход и Изход)
            Scanner in = new Scanner(socket.getInputStream());
            PrintStream out = new PrintStream(socket.getOutputStream());

            // 2. Цикълът - върти се, докато клиентът изпраща данни
            while (true) {
                out.println("----------МЕНЮ----------");
                out.println("Моля изберете опция:");
                out.println("1. Показване на всички паркоместа.");
                out.println("2. Резервиране на паркомясто.");
                out.println("3. Освобождаване на място.");

                int command = in.nextInt();
                in.nextLine();

                if (command == 1) {
                    for (ParkingSpot spot : spots) {
                        // 1. Първо определяме текста за статуса по лесния начин
                        String status;
                        if (spot.isFree) {
                            status = "Свободно";
                        } else {
                            status = "Заето от " + spot.clientName;
                        }

                        // 2. След това сглобяваме и принтираме всичко
                        out.println("ID: " + spot.id + "\nМясто №" + spot.number + "\nСтатус: " + status + "\nСобственик: " + spot.clientName);
                    }
                }
                else if (command == 2) {
                    out.println("Въведете ID на паркомястото:");
                    int spotId = in.nextInt();
                    in.nextLine(); // Чистим буфера след числото!

                    out.println("Въведете вашето име:");
                    String clientName = in.nextLine();

                    boolean isFound = false; // Флаг: намерихме ли такова ID?

                    // Обхождаме всички места, за да намерим търсеното
                    for (ParkingSpot spot : spots) {
                        if (spot.id == spotId) {
                            isFound = true; // Открихме го!

                            // ЗАКЛЮЧВАМЕ мястото (Синхронизация)
                            // Само един клиент може да достъпи този обект в даден момент
                            // Докато той е вътре и променя данните никой друг не може да пипа точно този обект от списъка
                            synchronized (spot) {
                                if (spot.isFree) {
                                    // Ако е свободно -> ЗАЕМАМЕ ГО
                                    spot.isFree = false;          // Маркираме като заето
                                    spot.clientName = clientName; // Записваме името
                                    out.println("Успешна резервация за " + clientName + "!");
                                } else {
                                    // Ако вече е заето
                                    out.println("Грешка: Мястото вече е заето от " + spot.clientName);
                                }
                            }
                            break; // Спираме търсенето, защото ID-тата са уникални
                        }
                    }
                    // Ако претърсихме всичко и не намерихме ID-то
                    if (!isFound) {
                        out.println("Невалидно ID на паркомясто!");
                    }
                }
                else if (command == 3) {
                    out.println("Въведете ID на мястото за освобождаване:");
                    int spotId = in.nextInt();
                    in.nextLine(); // Чистим Enter-а след числото

                    boolean isFound = false;

                    for (ParkingSpot spot : spots) {
                        if (spot.id == spotId) {
                            isFound = true;

                            // Заключваме мястото, за да сме сигурни, че никой не го резервира в същия момент
                            synchronized (spot) {
                                if (!spot.isFree) {
                                    // Ако мястото Е ЗАЕТО -> Освобождаваме го
                                    spot.isFree = true;          // Вече е свободно
                                    spot.clientName = null;      // Изтриваме името на клиента

                                    out.println("Мястото с ID " + spotId + " беше освободено успешно.");
                                } else {
                                    // Ако мястото вече си е свободно
                                    out.println("Грешка: Това място вече е свободно!");
                                }
                            }
                            break; // Спираме търсенето
                        }
                    }

                    if (!isFound) {
                        out.println("Невалидно ID! Няма такова място.");
                    }
                }
                else {
                    out.println("Невалидна команда! Опитайте отново");
                }
            }
        }
        catch (IOException e) {
            e.printStackTrace();
        }
    }
}