package Library;

import java.io.IOException;
import java.io.PrintStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Library {
    public int id;
    public String isbn;
    public String title;
    public String author;
    public boolean availability;
   public String library;
}

class Server{
    public static void main(String[] args) {
        try {
            ServerSocket serverSocket = new ServerSocket(5678);
            System.out.println("Waiting for connection...");
            List<Library> books = new ArrayList<Library>();

            while (true) {
                Socket clientSocket = serverSocket.accept();

                ClientHandler handler = new ClientHandler();
                handler.socket = clientSocket;
                handler.books = books;

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
    public List<Library> books;
    public ArrayList<Library> wishlist =  new ArrayList<Library>();

    @Override
    public void run() {
        try {
            Scanner in = new Scanner(socket.getInputStream());
            PrintStream out = new PrintStream(socket.getOutputStream());

            while (true) {
                out.println("========== MENU ==========");
                out.println("1. Find Book");
                out.println("2. Take Book");
                out.println("3. Show All Books In Some Library");
                out.println("Please choose an option");

                int command = in.nextInt();
                in.nextLine();

                if (command == 1) {
                    out.print("Book Title: ");
                    String title = in.nextLine();

                    ArrayList<Library> foundBooks = new ArrayList<Library>();

                    for (Library book : books) {
                        if (book.title.equalsIgnoreCase(title)) {
                            foundBooks.add(book);
                        }
                    }

                    if (foundBooks.isEmpty()) {
                        out.print("Book Not Found");
                    }
                    else {
                        for (Library book : foundBooks) {
                            out.println(book.library);
                            if (book.availability) {
                                out.println("Book is Available");
                            }
                            else {
                                out.println("Book is not Available");
                            }
                        }
                    }
                }
                else if (command == 2) {
                    out.print("Please Enter Book ID: ");
                    int bookID = in.nextInt();
                    boolean found = false;
                    for (Library book : wishlist) {
                        if (book.id == bookID) {
                            found = true;
                            break;
                        }
                    }
                    if (found) {
                        out.print("The book is already in your wishlist");
                    }
                    else {
                        boolean exists = true;
                        Library wishlistBook = new Library();
                        for (Library book : books) {
                            if (book.id == bookID) {
                                exists = true;
                                wishlistBook.title = book.title;
                                wishlistBook.isbn = book.isbn;
                                wishlistBook.author = book.author;
                                wishlistBook.availability = book.availability;
                                wishlistBook.library = book.library;
                                wishlistBook.id = book.id;
                                break;
                            }
                        }
                        if (!exists && wishlistBook.availability) {
                            wishlist.add(wishlistBook);
                            out.print("The book was added to the wishlist");
                        }
                        else {
                            out.println("Book with this ID does not exist");
                        }
                    }

                }
                else if (command == 3) {
                    out.print("Please Enter Library Name: ");
                    String libraryName = in.nextLine();

                    ArrayList<String> library = new ArrayList<String>();
                    boolean found = false;
                    for (Library book : books) {
                        if (book.library.equalsIgnoreCase(libraryName)) {
                            found = true;
                            library.add(book.title);
                        }
                    }
                    if (library.isEmpty()) {
                        if (!found) {
                            out.print("Library Not Found");
                        }
                        else {
                            out.print("There is no book in this library name");
                        }
                    }
                    else {
                        for (String book : library) {
                            out.println(book);
                        }
                    }
                }
            }
        }
        catch (IOException e) {
            e.printStackTrace();
        }
    }
}