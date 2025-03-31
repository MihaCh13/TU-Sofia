#include <stdio.h>
#include <stdlib.h>

void sortArray(int *arr, int size) {
    int temp;
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (arr[i] > arr[j]) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

int main() {
    int n, m;

    printf("Enter the size of the first array (n): ");
    scanf("%d", &n);
    printf("Enter the size of the second array (m): ");
    scanf("%d", &m);

    int *arr1 = (int*) malloc(n * sizeof(int));
    int *arr2 = (int*) malloc(m * sizeof(int));

    if (arr1 == NULL || arr2 == NULL) {
        printf("Memory allocation error.\n");
        return 1;
    }

    printf("Enter %d elements for the first array:\n", n);
    for (int i = 0; i < n; i++) {
        printf("arr1[%d]: ", i);
        scanf("%d", &arr1[i]);
    }

    printf("Enter %d elements for the second array:\n", m);
    for (int i = 0; i < m; i++) {
        printf("arr2[%d]: ", i);
        scanf("%d", &arr2[i]);
    }

    int *mergedArr = (int*) malloc((n + m) * sizeof(int));

    if (mergedArr == NULL) {
        printf("Memory allocation error for merged array.\n");
        free(arr1);
        free(arr2);
        return 1;
    }

    for (int i = 0; i < n; i++) {
        mergedArr[i] = arr1[i];
    }

    for (int i = 0; i < m; i++) {
        mergedArr[n + i] = arr2[i];
    }

    sortArray(mergedArr, n + m);

    printf("\nMerged and sorted array:\n");
    for (int i = 0; i < n + m; i++) {
        printf(" %d ", mergedArr[i]);
    }

    free(arr1);
    free(arr2);
    free(mergedArr);

    return 0;
}
