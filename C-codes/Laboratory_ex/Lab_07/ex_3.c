#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BRAND 30
#define MAX_MODEL 6  

typedef struct {
    char brand[MAX_BRAND];
    char model[MAX_MODEL];
    float engine_volume;
    float price;
    char registered;
} Car;

void write_car_to_text(FILE *file, Car *car) {
    fprintf(file, "%s %s %.2f %.2f %c\n",
        car->brand, car->model, car->engine_volume, car->price, car->registered);
}

void add_new_car(FILE *bin, FILE *txt) {
    Car car;

    printf("Enter brand: ");
    scanf(" %[^\n]", car.brand); 

    printf("Enter model (5 characters): ");
    scanf("%5s", car.model);

    printf("Enter engine volume: ");
    scanf("%f", &car.engine_volume);

    printf("Enter price: ");
    scanf("%f", &car.price);

    printf("Is it registered? (Y/N): ");
    scanf(" %c", &car.registered);

    fwrite(&car, sizeof(Car), 1, bin);
    write_car_to_text(txt, &car);

    printf("Record added successfully.\n");
}

void read_binary_file() {
    FILE *file = fopen("cars.bin", "rb");
    if (!file) {
        perror("Failed to open binary file");
        return;
    }

    Car car;
    printf("\n--- Cars from Binary File ---\n");
    while (fread(&car, sizeof(Car), 1, file) == 1) {
        printf("Brand: %s | Model: %s | Engine: %.2f | Price: %.2f | Registered: %c\n",
            car.brand, car.model, car.engine_volume, car.price, car.registered);
    }

    fclose(file);
}

void read_text_file() {
    FILE *file = fopen("cars.txt", "r");
    if (!file) {
        perror("Failed to open text file");
        return;
    }

    Car car;
    printf("\n--- Cars from Text File ---\n");
    while (fscanf(file, "%s %s %f %f %c",
        car.brand, car.model, &car.engine_volume, &car.price, &car.registered) == 5) {
        printf("Brand: %s | Model: %s | Engine: %.2f | Price: %.2f | Registered: %c\n",
            car.brand, car.model, car.engine_volume, car.price, car.registered);
    }

    fclose(file);
}

int main() {
    FILE *bin = fopen("cars.bin", "ab"); 
    FILE *txt = fopen("cars.txt", "a");  
    if (!bin || !txt) {
        perror("Failed to open files");
        return 1;
    }

    int choice;

    do {
        printf("\n===== Menu =====\n");
        printf("1. Add a new car to the database\n");
        printf("2. Read and compare cars from binary file\n");
        printf("3. Read and compare cars from text file\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_new_car(bin, txt);
                break;
            case 2:
                read_binary_file();
                break;
            case 3:
                read_text_file();
                break;
            case 0:
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid option. Please choose 0–3.\n");
        }
    } while (choice != 0);

    fclose(bin);
    fclose(txt);

    return 0;
}
