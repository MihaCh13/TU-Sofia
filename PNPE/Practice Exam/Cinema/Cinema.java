package Cinema;

import java.io.PrintStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Cinema {
    public int id;
    public int row;
    public int seat;
    public float price;
    public String customerName;
    public boolean sold;
}

class Surver{
    public static void main(String[] args) {
        try {
            ServerSocket serverSocket = new ServerSocket(3333);
            System.out.println("Waiting for client on port 3333");

            List<Cinema> tickets = new ArrayList<>();
            for (int i = 0; i < 10; i++) {
                Cinema ticket = new Cinema();
                ticket.id = i;
                ticket.row = i;
                ticket.seat = i;
                ticket.price = 11.45f;
                tickets.add(ticket);
            }

            while(true){
                Socket clientSocket = serverSocket.accept();

                ClientHandler handler = new ClientHandler();
                handler.socket = clientSocket;
                handler.tickets = tickets;

                Thread thread = new Thread(handler);
                thread.start();
            }
        }
        catch (Exception e) {
            System.out.println (e);
        }
    }
}

class ClientHandler implements Runnable{
    public Socket socket;
    public List<Cinema> tickets;

    @Override
    public void run(){
        try {
            Scanner in = new Scanner(socket.getInputStream());
            PrintStream out = new PrintStream(socket.getOutputStream());

            while (true) {
                out.println("========== MENU ==========");
                out.println("1. Free seeds");
                out.println("2. Byu a ticket");
                out.println("3. Return ticket");
                out.println("Please choose one of the options above");

                int choice = in.nextInt();
                in.nextLine();
                int freeSpases = 0;

                if(choice == 1){
                    for (Cinema ticket : tickets) {
                        if (!ticket.sold) {
                            freeSpases++;
                            out.println("Ticket id: " + ticket.id + "\nRow: " + ticket.row + "\n Seat: " + ticket.seat + "\nPrice: " + ticket.price);
                        }
                    }
                    if(freeSpases == 0){
                        out.println("Everithing is soldout");
                    }
                }
                else if(choice == 2){
                    out.println("Please enter ticket id: ");
                    int ticketID = in.nextInt();
                    in.nextLine();
                    boolean ticketFound = false;
                    String name = in.nextLine();

                    for(Cinema ticket : tickets){
                        synchronized (ticket){
                            if (ticket.id == ticketID && !ticket.sold){
                                ticketFound = true;
                                out.println("Please enter your name: ");
                                ticket.customerName = name;
                                ticket.sold = true;
                                break;
                            }
                            else if (ticket.sold && ticket.id == ticketID){
                                out.println("Ticket is already sold ");
                                break;
                            }
                        }
                    }
                    if(ticketFound == false){
                        out.println("Ticket not found");
                    }
                }
                else if(choice == 3){
                    out.println("Please enter ticket id: ");
                    int ticketID = in.nextInt();
                    in.nextLine();
                    boolean ticketFound = false;

                    for(Cinema ticket : tickets){
                        synchronized (ticket){
                            if (ticket.id == ticketID && ticket.sold){
                                ticketFound = true;
                                ticket.sold = false;
                                ticket.customerName = null;
                                out.println("Ticket was return successfully");
                            }
                            else if (!ticket.sold && ticket.id == ticketID){
                                ticketFound = true;
                                out.println("Ticket can't be returned, because it's not sold");
                            }
                        }
                    }
                    if(ticketFound == false){
                        out.println("Ticket not found");
                    }
                }
                else{
                    out.println("Please enter valid choice");
                }
            }
        }
        catch (Exception e) {
            System.out.println (e);
        }
    }
}