#include <stdio.h>
#include <stdlib.h>

void create_binary_file() {
    FILE *file = fopen("data.bin", "wb");
    if (!file) {
        perror("Failed to open file for writing");
        return;
    }

    int num;
    char choice;

    do {
        printf("Enter an integer: ");
        scanf("%d", &num);
        fwrite(&num, sizeof(int), 1, file);

        printf("Add another number? (y/n): ");
        scanf(" %c", &choice); 
    } while (choice == 'y' || choice == 'Y');

    fclose(file);
    printf("Binary file 'data.bin' created successfully.\n");
}

int count_even_digits(int num) {
    int count = 0;
    num = abs(num);
    if (num == 0) return 1; 
    while (num > 0) {
        int digit = num % 10;
        if (digit % 2 == 0) count++;
        num /= 10;
    }
    return count;
}

int count_odd_digits(int num) {
    int count = 0;
    num = abs(num);
    while (num > 0) {
        int digit = num % 10;
        if (digit % 2 != 0) count++;
        num /= 10;
    }
    return count;
}

void count_digits_from_file() {
    FILE *file = fopen("data.bin", "rb");
    if (!file) {
        perror("Failed to open file for reading");
        return;
    }

    int num;
    int even_total = 0, odd_total = 0;

    while (fread(&num, sizeof(int), 1, file) == 1) {
        even_total += count_even_digits(num);
        odd_total += count_odd_digits(num);
    }

    fclose(file);

    printf("Total even digits: %d\n", even_total);
    printf("Total odd digits: %d\n", odd_total);
}

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

void sort_and_save_to_text_file() {
    FILE *file = fopen("data.bin", "rb");
    if (!file) {
        perror("Failed to open file for reading");
        return;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    int count = file_size / sizeof(int);
    int *arr = malloc(count * sizeof(int));
    if (!arr) {
        perror("Memory allocation failed");
        fclose(file);
        return;
    }

    fread(arr, sizeof(int), count, file);
    fclose(file);

    qsort(arr, count, sizeof(int), compare);

    FILE *out = fopen("sorted.txt", "w");
    if (!out) {
        perror("Failed to open output text file");
        free(arr);
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(out, "%d\n", arr[i]);
    }

    fclose(out);
    free(arr);

    printf("Sorted numbers saved to 'sorted.txt'\n");
}

int main() {
    int choice;

    do {
        printf("\n===== Menu =====\n");
        printf("1. Create binary file with integers\n");
        printf("2. Count even and odd digits\n");
        printf("3. Sort numbers and save to text file\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                create_binary_file();
                break;
            case 2:
                count_digits_from_file();
                break;
            case 3:
                sort_and_save_to_text_file();
                break;
            case 0:
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid option. Please choose 0–3.\n");
        }
    } while (choice != 0);

    return 0;
}
