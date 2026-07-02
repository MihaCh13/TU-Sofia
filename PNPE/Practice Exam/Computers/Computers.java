package Computers;


import java.io.IOException;
import java.io.PrintStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Computers{
    public int id;
    public String laptopName;
    public String studentName;
    public boolean busy; // True = busy    False = free
}

class Server {
    public static void main(String[] args) {
        try {
            ServerSocket serverSocket = new ServerSocket(1234);
            System.out.println("Waiting for connection...");
            List<Computers> laptops = new ArrayList<Computers>();

            for(int i = 0; i < 10; i++){
                Computers computers = new Computers();
                computers.id = i;
                computers.laptopName = "Laptop " + i;
                laptops.add(computers);
            }

            while (true) {
                Socket clientSocket = serverSocket.accept();

                ClientHandler handler = new ClientHandler();
                handler.socket = clientSocket;
                handler.laptops = laptops;

                Thread thread = new Thread(handler);
                thread.start();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}

class ClientHandler implements Runnable{
    public Socket socket;
    public List<Computers> laptops;

    @Override
    public void run() {
        try {
            Scanner in = new Scanner(socket.getInputStream());
            PrintStream out = new PrintStream(socket.getOutputStream());

            while (true) {
                out.println("========== MENU ========");
                out.println("1. Show All Computer");
                out.println("2. Borrow Computer");
                out.println("3. Check Computer");
                out.println("Please choose an option");

                int command = in.nextInt();
                in.nextLine();

                if (command == 1 ) {
                    for(Computers computers : laptops){
                        out.println("Computer Name: " + computers.laptopName);
                        out.println("Computer ID: " + computers.id);
                        out.println("Student Name: " +computers.studentName);
                        if(computers.busy == true){
                            out.println("Computer status: Borrowed");
                        }
                        else{
                            out.println("Computer status: Free");
                        }
                    }
                }
                else if (command == 2){
                    out.println("Please enter computer id");
                    int computerId = in.nextInt();
                    in.nextLine(); // Чистене на буфера - Супер!

                    out.println("Please enter your name");
                    String sName = in.nextLine();

                    boolean found = false; // 1. Създаваме флага

                    // 2. Започваме да търсим в списъка
                    for(Computers computers : laptops){
                        synchronized (computers){ // Синхронизацията е отлична идея тук
                            if(computers.id == computerId){
                                found = true; // Намерихме го!

                                if(!computers.busy){
                                    computers.studentName = sName;
                                    computers.busy = true;
                                    out.println("You successfully Borrowed Computer: " + computers.laptopName);
                                }
                                else {
                                    out.println("Sorry, you can't borrow this computer, it's already taken ");
                                }
                                break; // Спираме да търсим
                            }
                        }
                    }

                    // 3. Ако след целия цикъл не сме го намерили
                    if (!found) {
                        out.println("Computer with ID: "  + computerId + " does not exist");
                    }
                }
                else if (command == 3){
                    out.println("Please enter computer id");
                    int computerId = in.nextInt();
                    in.nextLine();

                    boolean found = false;

                    for(Computers computers : laptops){
                        if (computers.id == computerId){
                            found = true;
                            if(!computers.busy){
                                out.println("Computer is free");
                            }
                            else{
                                out.println("Computer is already borrowed by " + computers.studentName);
                            }
                            break;
                        }
                    }

                    if(!found){
                        out.println("Computer with ID: "  + computerId + " does not exist");
                    }
                }
            }
        }
        catch (IOException e) {
            e.printStackTrace();
        }
    }
}