#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, new_n;
    int *arr;
    char choice;

    printf("Enter the number of elements (n): ");
    scanf("%d", &n);

    arr = (int*) malloc(n * sizeof(int));

    if (arr == NULL) {
        printf("Memory allocation error.\n");
        return 1;
    }

    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++) {
        printf("arr[%d]: ", i);
        scanf("%d", &arr[i]);
    }

    printf("Do you want to add more elements? (y/n): ");
    getchar();  // Clear the buffer from the previous getchar()
    scanf("%c", &choice);

    if (choice == 'y' || choice == 'Y') {
        // Input the number of new elements to add
        printf("Enter the number of new elements you want to add: ");
        scanf("%d", &new_n);

        arr = (int*) realloc(arr, (n + new_n) * sizeof(int));

        if (arr == NULL) {
            printf("Memory reallocation error.\n");
            return 1;
        }

        printf("Enter %d new elements:\n", new_n);
        for (int i = n; i < n + new_n; i++) {
            printf("arr[%d]: ", i);
            scanf("%d", &arr[i]);
        }

        n = n + new_n;
    }

    printf("\nElements in the array after addition:\n");
    for (int i = 0; i < n; i++) {
        printf("arr[%d]: %d\n", i, arr[i]);
    }

    free(arr);

    return 0;
}
