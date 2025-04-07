#include <stdio.h>
#include <string.h>


typedef struct {
    char title[100];
    char author[100];
    int year;
    float price;
} Book;


void findExpensiveAndCheapBooks(Book books[], int size) {
    Book cheapest = books[0];
    Book most_expensive = books[0];

    for (int i = 1; i < size; i++) {
        if (books[i].price < cheapest.price) {
            cheapest = books[i];
        }
        if (books[i].price > most_expensive.price) {
            most_expensive = books[i];
        }
    }

    printf("\nCheapest book: %s by %s, Price: %.2f, Year: %d\n", cheapest.title, cheapest.author, cheapest.price, cheapest.year);
    printf("Most expensive book: %s by %s, Price: %.2f, Year: %d\n", most_expensive.title, most_expensive.author, most_expensive.price, most_expensive.year);
}


float calculateAveragePrice(Book books[], int size) {
    float total = 0.0;

    for (int i = 0; i < size; i++) {
        total += books[i].price;
    }

    return total / size;
}

int main() {

    Book books[5] = {
        {"Haunting Adeline", "F. Scott Fitzgerald", 1925, 15.99},
        {"Hunting Adeline", "George Orwell", 1949, 9.99},
        {"Fourth wing", "Harper Lee", 1960, 12.99},
        {"The cruel prince", "Holly Black", 1851, 19.50},
        {"Pride and Prejudice", "Jane Austen", 1951, 10.99}
    };


    findExpensiveAndCheapBooks(books, 5);


    float average_price = calculateAveragePrice(books, 5);
    printf("\nAverage price of all books: %.2f\n", average_price);

    return 0;
}
