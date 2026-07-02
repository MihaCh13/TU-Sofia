import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

/**
 * Главен клас – стартира многонишковия сървър на порт 5678.
 * За всеки клиент създава нов ClientHandler (Thread).
 */
public class AutoServiceServer {

    private static final int PORT = 5678;

    private final ServiceCenter serviceCenter = new ServiceCenter();

    public static void main(String[] args) {
        AutoServiceServer server = new AutoServiceServer();
        server.start();
    }

    public void start() {
        try (ServerSocket serverSocket = new ServerSocket(PORT)) {
            System.out.println("AutoServiceServer started on port " + PORT);

            while (true) {
                Socket clientSocket = serverSocket.accept();
                ClientHandler handler = new ClientHandler(clientSocket, serviceCenter);
                handler.start(); // нова нишка за всеки клиент
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}