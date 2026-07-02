package Parking;

// 1. Импортите са винаги тези
import java.io.*;
import java.net.*;
import java.util.*;

public class Poleta {
    //===============;
    //===============;
}

public class Server {
    public static void main(String[] args) {
        try {
            ServerSocket serverSocket = new ServerSocket(PORT_NUMBER);
            System.out.println("Сървърът работи на порт...");

            List<Poleta> name = new ArrayList<>();
            // Тук пълниш с for цикъл или оставяш празно (според условието)

            while (true) {
                Socket clientSocket = serverSocket.accept();

                ClientHandler handler = new ClientHandler();
                handler.socket = clientSocket;
                handler.name = name; // Предаваш списъка

                Thread thread = new Thread(handler);
                thread.start();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}

static class ClientHandler implements Runnable {
    public Socket socket;
    public List<Poleta> name;

    @Override
    public void run() {
        try {
            Scanner in = new Scanner(socket.getInputStream());
            PrintStream out = new PrintStream(socket.getOutputStream());

            while (true) {
                out.println("========== MENU ==========");

                int command = in.nextInt(); // Четеш командата
                in.nextLine(); // Чистиш буфера (Винаги задължително!)

                if (command == 1) {
                    // Логика за команда 1
                } else if (command == 2) {
                    // ТУК ОБИКНОВЕНО Е СИНХРОНИЗАЦИЯТА
                    for (Poleta name : name) {
                        synchronized (name) {
                            //===========
                        }
                    }
                } else if (command == 3) {
                    // Логика за команда 3
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}