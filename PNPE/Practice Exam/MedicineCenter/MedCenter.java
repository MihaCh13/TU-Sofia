package MedicineCenter;

import java.io.IOException;
import java.io.PrintStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class MedCenter {
    public int id;
    public String doctorName;
    public String patientName;
    public String time;
    public boolean isFree;
}

class Server{
    public static void main(String[] args){
        try {
            ServerSocket serverSocket = new ServerSocket(7777);
            System.out.println("Server Started");

            List<MedCenter> medCenters = new ArrayList<>();
            for (int i = 1; i <= 10; i++) {
                MedCenter medCenter = new MedCenter();
                medCenter.id = i;
                if (i % 2 == 0) {
                    medCenter.doctorName = "Petrov";
                }
                else {
                    medCenter.doctorName = "Ivanov";
                }
                medCenter.isFree = true;
                medCenter.time = (i+9) + ":00";
                medCenters.add(medCenter);
            }

            while (true){
                Socket clientSocket = serverSocket.accept();
                ClientHandler handler = new ClientHandler();
                handler.socket = clientSocket;
                handler.medCenters = medCenters;

                Thread thread = new Thread(handler);
                thread.start();
            }
        }
        catch (Exception e) {
            e.printStackTrace();
        }
    }
}

class ClientHandler implements Runnable{
    public Socket socket;
    public List<MedCenter> medCenters;

    @Override
    public void run() {
        try {
            Scanner in =  new Scanner(socket.getInputStream());
            PrintStream out = new PrintStream(socket.getOutputStream());

            while (true) {
                out.println("========== Medicine centers ==========");
                out.println("1. Free hours");
                out.println("2. Book time");
                out.println("3. Canceling time");
                out.println("Please enter your choice");

                int command = in.nextInt();
                in.nextLine();

                if (command == 1){
                    int found = 0;
                    for (MedCenter medCenter : medCenters) {
                        if (medCenter.isFree){
                            found ++;
                            out.println(medCenter.time);
                            out.println(medCenter.doctorName);
                            out.println(medCenter.id);
                        }
                    }
                    if (found == 0){
                        out.println("There is no free hours");
                    }
                }
                else if (command == 2) {
                    out.println("Please enter time id");
                    int wantID = in.nextInt();
                    in.nextLine();
                    out.println("Please enter your name");
                    String name = in.nextLine();

                    boolean idExists = false; // Флаг дали ID-то въобще го има
                    boolean success = false;  // Флаг дали сме записали часа

                    for (MedCenter app : medCenters) {
                        // Първо намираме дали съществува такъв час по ID
                        if (app.id == wantID) {
                            idExists = true;

                            // Тук правим синхронизацията
                            synchronized (app) {
                                if (app.isFree) {
                                    app.patientName = name;
                                    app.isFree = false;
                                    success = true;
                                    out.println("Successfully booked appointment with " + app.doctorName);
                                } else {
                                    out.println("This time is already taken!");
                                }
                            }
                            break; // Намерили сме ID-то, няма смисъл да въртим повече
                        }
                    }

                    if (!idExists) {
                        out.println("Invalid time id provided.");
                    }
                }
                else if (command == 3){
                    out.println("Please enter time id");
                    int cancelingID = in.nextInt();
                    in.nextLine();
                    boolean found = false;

                    for (MedCenter medCenter : medCenters) {
                        synchronized (medCenter) {
                            if (medCenter.id==cancelingID && !medCenter.isFree) {
                                medCenter.isFree = true;
                                medCenter.patientName = null;
                                found = true;
                            }
                            else if (medCenter.id==cancelingID && medCenter.isFree) {
                                out.println("Is already free");
                                found = true;
                            }
                        }
                    }
                    if (found == false){
                        out.println("Invalid time id");
                    }
                }
            }
        }
        catch (IOException e) {
            e.printStackTrace();
        }
    }
}