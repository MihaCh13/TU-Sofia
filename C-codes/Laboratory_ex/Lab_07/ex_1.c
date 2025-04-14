#include <stdio.h>
#include <stdlib.h>

int my_abs(int num) {
    if (num < 0) {
        return -num;
    }
    return num;
}

void quicksort(int *arr, int low, int high) {
    if (low < high) {
        int pivot = arr[high];
        int i = low - 1;

        for (int j = low; j < high; j++) {
            if (arr[j] <= pivot) {
                i++;
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }

        int temp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = temp;

        int pi = i + 1;
        quicksort(arr, low, pi - 1);  
        quicksort(arr, pi + 1, high);  
    }
}

void create_binary_file() {
    FILE *file = fopen("data.bin", "wb");
    if (!file) {
        perror("Failed to open file for writing");
        return;
    }

    int N;
    printf("Enter the number of integers (N): ");
    scanf("%d", &N);

    int arr[N];
    printf("Enter %d integers:\n", N);
    for (int i = 0; i < N; i++) {
        printf("Number %d: ", i + 1);
        scanf("%d", &arr[i]);
    }

    fwrite(&N, sizeof(int), 1, file);
    fwrite(arr, sizeof(int), N, file);
    fclose(file);

    printf("Binary file 'data.bin' created successfully.\n");
}

int count_even_digits(int num) {
    int count = 0;
    num = my_abs(num); 
    if (num == 0) return 1;
    while (num > 0) {
        int digit = num % 10;
        if (digit % 2 == 0)
            count++;
        num /= 10;
    }
    return count;
}

int count_odd_digits(int num) {
    int count = 0;
    num = my_abs(num); 
    while (num > 0) {
        int digit = num % 10;
        if (digit % 2 != 0)
            count++;
        num /= 10;
    }
    return count;
}
void count_digits_from_file() {
    FILE *file = fopen("data.bin", "rb");
    if (!file) {
        perror("Failed to open 'data.bin' for reading");
        return;
    }

    int N;
    fread(&N, sizeof(int), 1, file);
    int *arr = malloc(N * sizeof(int));
    fread(arr, sizeof(int), N, file);
    fclose(file);

    int even_digits = 0, odd_digits = 0;

    for (int i = 0; i < N; i++) {
        even_digits += count_even_digits(arr[i]);
        odd_digits += count_odd_digits(arr[i]);
    }

    printf("Total even digits: %d\n", even_digits);
    printf("Total odd digits: %d\n", odd_digits);

    free(arr);
}

void sort_and_save_to_text_file() {
    FILE *file = fopen("data.bin", "rb");
    if (!file) {
        perror("Failed to open 'data.bin' for reading");
        return;
    }

    int N;
    fread(&N, sizeof(int), 1, file);
    int *arr = malloc(N * sizeof(int));
    fread(arr, sizeof(int), N, file);
    fclose(file);

    quicksort(arr, 0, N - 1); 

    FILE *out = fopen("sorted.txt", "w");
    if (!out) {
        perror("Failed to open 'sorted.txt' for writing");
        free(arr);
        return;
    }

    for (int i = 0; i < N; i++) {
        fprintf(out, "%d\n", arr[i]);
    }

    fclose(out);
    free(arr);

    printf("Sorted numbers saved to 'sorted.txt'\n");
}

int main() {
    int choice;

    do {
        printf("\n--- Menu ---\n");
        printf("1. Create binary file\n");
        printf("2. Count even and odd digits\n");
        printf("3. Sort and save numbers to text file\n");
        printf("0. Exit\n");
        printf("Choose an option: ");
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
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please select 0–3.\n");
        }
    } while (choice != 0);

    return 0;
}
