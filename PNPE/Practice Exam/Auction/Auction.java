package Auction;

import java.io.IOException;
import java.io.PrintStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Auction {
    public int id;
    public String objName;
    public float price;
    public String participantName;
    public boolean end; // True -> finish   False -> not finished yet
}

class Surver{
    public static void main (String [] args){
        try {
            ServerSocket serverSocket = new ServerSocket(9999);
            System.out.println("Waiting for client on port 9999");

            List<Auction> auctions = new ArrayList<Auction>();
            String[] objName = {"Laptop", "Gittar", "Gun", "Coins", "Watch", "Vase", "Funko Pop", "Games", "Tickets", "Artwork"};

            for(int i = 0; i < 10; i++){
                Auction auction = new Auction();
                auction.id = i;
                auction.objName = objName[i];
                auction.end = false;
                auctions.add(auction);
            }

            while(true){
                Socket clientSocket = serverSocket.accept();

                ClientHandler handler = new ClientHandler();
                handler.socket = clientSocket;
                handler.auctions = auctions;

                Thread thread = new Thread(handler);
                thread.start();
            }
        }
        catch (IOException e){
            e.printStackTrace();
        }
    }
}

class ClientHandler implements Runnable{
    public Socket socket;
    public List<Auction> auctions;

    @Override
    public void run() {
        try {
            Scanner in = new Scanner(socket.getInputStream());
            PrintStream out = new PrintStream(socket.getOutputStream());

            while (true) {
                out.println("========== MENU ========");
                out.println("1. Show Auction List");
                out.println("2. Bidding");
                out.println("3. End the Auction");
                out.println("Please choose an option");

                int command = in.nextInt();
                in.nextLine();

                if (command == 1){
                    for (Auction auction : auctions) {
                        out.println(auction.id);
                        out.println(auction.objName);
                        out.println(auction.price);
                        out.println(auction.participantName);
                        if (auction.end){
                            out.println("The auction already ended");
                        }
                        else  {
                            out.println("The auction is still open");
                        }
                        out.println("=============================");
                    }
                }
                else if (command == 2){
                    out.println("Please enter object id");
                    int objectID = in.nextInt();
                    out.println("Please new price");
                    float objPrice = in.nextFloat();
                    in.nextLine();
                    out.println("Please enter participant name");
                    String pName = in.nextLine();
                    boolean found = false;

                    for (Auction auction : auctions) {
                        synchronized (auction) {
                            if (auction.id==objectID){
                                found = true;
                                if(!auction.end){
                                    if (auction.price < objPrice){
                                        auction.participantName = pName;
                                        auction.price = objPrice;
                                    }
                                    else {
                                        out.println("You can't bid lower than the current price");
                                    }
                                }
                                else {
                                    out.println("Sorry, the auction already ended");
                                }
                                break;
                            }
                        }
                    }
                    if (!found){
                        out.println("The object does not exist");
                    }
                }
                else if (command == 3){
                    out.println("Please enter object id");
                    int objectID = in.nextInt();

                    boolean found = false;

                    for(Auction auction : auctions){
                        synchronized (auction) {
                            if (auction.id==objectID){
                                found = true;
                                if(!auction.end){
                                    auction.end = true;
                                    out.println("The auction was closed successfully");
                                }
                                else {
                                    out.println("You can't close the auctionq because is already ended");
                                }
                            }
                        }
                    }
                    if (!found){
                        out.println("Sorry, the object does not exist");
                    }
                }
            }
        }
        catch (IOException e)
        {
            e.printStackTrace();
        }
    }
}
