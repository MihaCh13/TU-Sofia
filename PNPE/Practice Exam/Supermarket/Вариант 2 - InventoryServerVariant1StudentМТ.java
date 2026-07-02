import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.EOFException;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;

/**
 * Вариант 1 – учителско решение, многонишков сървър.
 *
 * Порт: 8080
 * Команди:
 *   LIST_ALL
 *   LIST_BY_TYPE
 *   STATUS_BY_DATE
 *   QUIT
 */
public class InventoryServerVariant1SolutionMT {

    private final List<Product> inventory = new ArrayList<>();

    public static void main(String[] args) {
        InventoryServerVariant1SolutionMT server = new InventoryServerVariant1SolutionMT();
        server.initSampleData();
        server.start();
    }

    public void start() {
        try (ServerSocket serverSocket = new ServerSocket(8080)) {
            System.out.println("Variant1 (solution, multithreaded) server started on port 8080...");

            while (true) {
                Socket client = serverSocket.accept();
                System.out.println("Client connected: " + client.getRemoteSocketAddress());

                ClientHandler handler = new ClientHandler(client, inventory);
                handler.start(); // нова нишка за всеки клиент
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    // ------------ Примерни данни ------------

    private void initSampleData() {
        inventory.add(new FoodProduct(
                1, "Milk", 2.50, 20, "food",
                LocalDate.now().plusDays(1)
        ));
        inventory.add(new FoodProduct(
                2, "Yogurt", 1.20, 30, "food",
                LocalDate.now().minusDays(1)
        ));
        inventory.add(new NonFoodProduct(
                3, "Toaster", 49.99, 5, "nonfood",
                LocalDate.now().plusMonths(6)
        ));
        inventory.add(new NonFoodProduct(
                4, "Old TV", 299.00, 2, "nonfood",
                LocalDate.now().minusMonths(2)
        ));
        inventory.add(new ShortLifeProduct(
                5, "Bread", 1.10, 15, "shortlife",
                LocalDate.now().minusDays(1)
        ));
        inventory.add(new ShortLifeProduct(
                6, "Cake", 3.50, 3, "shortlife",
                LocalDate.now()
        ));
    }

    // ------------ Модели ------------

    public static abstract class Product {
        private int id;
        private String name;
        private double basePrice;
        private int quantity;
        private String category;

        public Product(int id, String name, double basePrice, int quantity, String category) {
            this.id = id;
            this.name = name;
            this.basePrice = basePrice;
            this.quantity = quantity;
            this.category = category;
        }

        public int getId() {
            return id;
        }

        public String getName() {
            return name;
        }

        public double getBasePrice() {
            return basePrice;
        }

        public int getQuantity() {
            return quantity;
        }

        public String getCategory() {
            return category;
        }

        @Override
        public String toString() {
            return "Product{" +
                    "id=" + id +
                    ", name='" + name + '\'' +
                    ", basePrice=" + basePrice +
                    ", quantity=" + quantity +
                    ", category='" + category + '\'' +
                    '}';
        }
    }

    public interface Expirable {
        LocalDate getExpirationDate();
        boolean isExpired(LocalDate onDate);
    }

    public interface WarrantyHolder {
        LocalDate getWarrantyEndDate();
        boolean isInWarranty(LocalDate onDate);
    }

    public static class FoodProduct extends Product implements Expirable {
        private LocalDate expirationDate;

        public FoodProduct(int id, String name, double basePrice, int quantity, String category,
                           LocalDate expirationDate) {
            super(id, name, basePrice, quantity, category);
            this.expirationDate = expirationDate;
        }

        @Override
        public LocalDate getExpirationDate() {
            return expirationDate;
        }

        @Override
        public boolean isExpired(LocalDate onDate) {
            return onDate.isAfter(expirationDate);
        }
    }

    public static class NonFoodProduct extends Product implements WarrantyHolder {
        private LocalDate warrantyEndDate;

        public NonFoodProduct(int id, String name, double basePrice, int quantity, String category,
                              LocalDate warrantyEndDate) {
            super(id, name, basePrice, quantity, category);
            this.warrantyEndDate = warrantyEndDate;
        }

        @Override
        public LocalDate getWarrantyEndDate() {
            return warrantyEndDate;
        }

        @Override
        public boolean isInWarranty(LocalDate onDate) {
            return !onDate.isAfter(warrantyEndDate);
        }
    }

    public static class ShortLifeProduct extends Product {
        private LocalDate productionDate;

        public ShortLifeProduct(int id, String name, double basePrice, int quantity, String category,
                                LocalDate productionDate) {
            super(id, name, basePrice, quantity, category);
            this.productionDate = productionDate;
        }

        public LocalDate getProductionDate() {
            return productionDate;
        }
    }

    // ------------ МНОГОНИШКОВ ClientHandler ------------

    public static class ClientHandler extends Thread {

        private final Socket socket;
        private final List<Product> inventory;

        public ClientHandler(Socket socket, List<Product> inventory) {
            this.socket = socket;
            this.inventory = inventory;
        }

        @Override
        public void run() {
            System.out.println("Handler started for client: " + socket.getRemoteSocketAddress());
            try (Socket s = socket;
                 DataInputStream in = new DataInputStream(s.getInputStream());
                 DataOutputStream out = new DataOutputStream(s.getOutputStream())) {

                while (true) {
                    String command;
                    try {
                        command = in.readUTF();
                    } catch (EOFException eof) {
                        break;
                    }

                    if ("LIST_ALL".equalsIgnoreCase(command)) {
                        handleListAll(out);
                    } else if ("LIST_BY_TYPE".equalsIgnoreCase(command)) {
                        handleListByType(in, out);
                    } else if ("STATUS_BY_DATE".equalsIgnoreCase(command)) {
                        handleStatusByDate(in, out);
                    } else if ("QUIT".equalsIgnoreCase(command)) {
                        break;
                    } else {
                        out.writeUTF("ERROR: Unknown command: " + command);
                        out.flush();
                    }
                }

            } catch (IOException e) {
                System.out.println("Error handling client: " + e.getMessage());
            } finally {
                System.out.println("Client finished: " + socket.getRemoteSocketAddress());
            }
        }

        private void handleListAll(DataOutputStream out) throws IOException {
            out.writeUTF(Integer.toString(inventory.size()));
            for (Product p : inventory) {
                String line = p.getId() + ";" +
                        p.getName() + ";" +
                        p.getCategory() + ";" +
                        p.getBasePrice() + ";" +
                        p.getQuantity();
                out.writeUTF(line);
            }
            out.flush();
        }

        private void handleListByType(DataInputStream in, DataOutputStream out) throws IOException {
            String type = in.readUTF(); // "food", "nonfood", "shortlife"
            List<Product> filtered = new ArrayList<>();
            for (Product p : inventory) {
                if ("food".equalsIgnoreCase(type) && p instanceof FoodProduct) {
                    filtered.add(p);
                } else if ("nonfood".equalsIgnoreCase(type) && p instanceof NonFoodProduct) {
                    filtered.add(p);
                } else if ("shortlife".equalsIgnoreCase(type) && p instanceof ShortLifeProduct) {
                    filtered.add(p);
                }
            }

            out.writeUTF(Integer.toString(filtered.size()));
            for (Product p : filtered) {
                String line = p.getId() + ";" +
                        p.getName() + ";" +
                        p.getBasePrice() + ";" +
                        p.getQuantity();
                out.writeUTF(line);
            }
            out.flush();
        }

        private void handleStatusByDate(DataInputStream in, DataOutputStream out) throws IOException {
            String dateStr = in.readUTF(); // YYYY-MM-DD
            LocalDate date = LocalDate.parse(dateStr);

            List<FoodProduct> expiredFood = new ArrayList<>();
            List<NonFoodProduct> outOfWarranty = new ArrayList<>();
            List<ShortLifeProduct> shortLifeList = new ArrayList<>();

            for (Product p : inventory) {
                if (p instanceof FoodProduct) {
                    FoodProduct fp = (FoodProduct) p;
                    if (fp.isExpired(date)) {
                        expiredFood.add(fp);
                    }
                } else if (p instanceof NonFoodProduct) {
                    NonFoodProduct nfp = (NonFoodProduct) p;
                    if (!nfp.isInWarranty(date)) {
                        outOfWarranty.add(nfp);
                    }
                } else if (p instanceof ShortLifeProduct) {
                    ShortLifeProduct slp = (ShortLifeProduct) p;
                    shortLifeList.add(slp);
                }
            }

            // EXPIRED_FOOD
            out.writeUTF("EXPIRED_FOOD:" + expiredFood.size());
            for (FoodProduct fp : expiredFood) {
                String line = fp.getId() + ";" +
                        fp.getName() + ";" +
                        fp.getExpirationDate();
                out.writeUTF(line);
            }

            // OUT_OF_WARRANTY
            out.writeUTF("OUT_OF_WARRANTY:" + outOfWarranty.size());
            for (NonFoodProduct nfp : outOfWarranty) {
                String line = nfp.getId() + ";" +
                        nfp.getName() + ";" +
                        nfp.getWarrantyEndDate();
                out.writeUTF(line);
            }

            // SHORT_LIFE
            out.writeUTF("SHORT_LIFE:" + shortLifeList.size());
            for (ShortLifeProduct slp : shortLifeList) {
                String line = slp.getId() + ";" +
                        slp.getName() + ";" +
                        slp.getProductionDate() + ";" +
                        slp.getQuantity();
                out.writeUTF(line);
            }

            out.flush();
        }
    }
}
