#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, number, i, j;
    int *arr;
    int found = 0;

    printf("Enter the number of elements (n): ");
    scanf("%d", &n);

    arr = (int*) malloc(n * sizeof(int));

    if (arr == NULL) {
        printf("Memory allocation error.\n");
        return 1;
    }

    printf("Enter %d elements:\n", n);
    for (i = 0; i < n; i++) {
        printf("arr[%d]: ", i);
        scanf("%d", &arr[i]);
    }

    printf("Enter the number to remove: ");
    scanf("%d", &number);

    for (i = 0; i < n; i++) {
        if (arr[i] == number) {
            found = 1;
            for (j = i; j < n - 1; j++) {
                arr[j] = arr[j + 1];
            }
            n--;
            break;
        }
    }

    if (found) {
        printf("\nArray after removing %d:\n", number);
        for (i = 0; i < n; i++) {
            printf("arr[%d]: %d\n", i, arr[i]);
        }
    } else {
        printf("\nThe number %d was not found in the array.\n", number);
    }

    free(arr);

    return 0;
}
