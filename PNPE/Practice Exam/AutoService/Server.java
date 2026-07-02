package AutoService;

import java.io.IOException;
import java.io.PrintStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

class Order {
    public int id;
    public String carRegNumber;
    public String description;
    public String status; // NEW, IN_PROGRESS, DONE
}

class ClientHandler implements Runnable {
    public Socket socket;
    public List<Order> orders;

    @Override
    public void run() {
        try {
            Scanner in = new Scanner(socket.getInputStream());
            PrintStream out = new PrintStream(socket.getOutputStream());

            while (true) {
                out.println("========== MENU ==========");
                out.println("1. Create Order");
                out.println("2. Change Order Status");
                out.println("3. Search by Status");
                out.println("==========================");

                if (!in.hasNextInt()) return;
                int command = in.nextInt();
                in.nextLine();

                // --- КОМАНДА 1: РЕГИСТРАЦИЯ ---
                if (command == 1) {
                    out.println("Enter car Reg Number:");
                    String carReg = in.nextLine();
                    out.println("Enter description:");
                    String desc = in.nextLine();

                    boolean exists = false;

                    // Синхронизираме целия процес
                    synchronized (orders) {
                        // 1. Проверяваме за дубликат
                        for (Order o : orders) {
                            if (o.carRegNumber.equals(carReg) &&
                                    (o.status.equals("NEW") || o.status.equals("IN_PROGRESS"))) {
                                exists = true;
                                break;
                            }
                        }

                        if (!exists) {
                            // --- ТУК Е ПРОМЯНАТА (Генериране на ID без Сървър) ---
                            // Намираме най-голямото ID в момента и добавяме 1
                            int newId = 1;
                            for (Order o : orders) {
                                if (o.id >= newId) {
                                    newId = o.id + 1;
                                }
                            }
                            // -----------------------------------------------------

                            Order newOrder = new Order();
                            newOrder.id = newId; // Задаваме пресметнатото ID
                            newOrder.carRegNumber = carReg;
                            newOrder.description = desc;
                            newOrder.status = "NEW";

                            orders.add(newOrder);
                            out.println("Order created with ID: " + newOrder.id);
                        } else {
                            out.println("Active order already exists for this car!");
                        }
                    }
                }
                // --- КОМАНДА 2: ПРОМЯНА НА СТАТУС ---
                else if (command == 2) {
                    out.println("Enter Order ID:");
                    int searchID = in.nextInt();
                    in.nextLine();
                    out.println("Enter New Status (IN_PROGRESS / DONE):");
                    String newStatus = in.nextLine();

                    boolean found = false;

                    synchronized (orders) {
                        for (Order o : orders) {
                            if (o.id == searchID) {
                                o.status = newStatus;
                                found = true;
                                out.println("Status changed to " + newStatus);
                                break;
                            }
                        }
                    }

                    if (!found) {
                        out.println("Order with ID " + searchID + " not found.");
                    }
                }
                // --- КОМАНДА 3: ТЪРСЕНЕ ПО СТАТУС ---
                else if (command == 3) {
                    out.println("Enter status to search:");
                    String searchStatus = in.nextLine();

                    List<Order> foundOrders = new ArrayList<>();

                    synchronized (orders) {
                        for (Order o : orders) {
                            if (o.status.equalsIgnoreCase(searchStatus)) {
                                foundOrders.add(o);
                            }
                        }
                    }

                    if (foundOrders.isEmpty()) {
                        out.println("No orders found with status: " + searchStatus);
                    } else {
                        for (Order o : foundOrders) {
                            out.println(o.id + " | " + o.carRegNumber + " | " + o.status);
                        }
                    }
                }
                else {
                    out.println("Invalid command!");
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}

public class Server {
    // ВЕЧЕ Е ЧИСТ - НЯМА static полета и методи за ID
    public static void main(String[] args) {
        try {
            ServerSocket serverSocket = new ServerSocket(5678);
            System.out.println("Server started on port 5678...");

            List<Order> globalOrders = new ArrayList<>();

            while (true) {
                Socket clientSocket = serverSocket.accept();

                ClientHandler handler = new ClientHandler();
                handler.socket = clientSocket;
                handler.orders = globalOrders;

                Thread thread = new Thread(handler);
                thread.start();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}