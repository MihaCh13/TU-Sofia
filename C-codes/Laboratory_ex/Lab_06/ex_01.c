#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, m;
    int *arr1, *arr2;
    int sum1 = 0, sum2 = 0;
    double avg1, avg2;

    printf("Enter the size of the array (n): ");
    scanf("%d", &n);
    printf("Enter the size of the array (m): ");
    scanf("%d", &m);

    arr1 = (int*) malloc(n * sizeof(int));
    arr2 = (int*) malloc(m * sizeof(int));

    if (arr1 == NULL || arr2 == NULL) {
        printf("Memory allocation error.\n");
        return 1;
    }

    printf("Enter %d element for the first array:\n", n);
    for (int i = 0; i < n; i++) {
        printf("arr1[%d]: ", i);
        scanf("%d", &arr1[i]);
        sum1 += arr1[i]; 
    }

    printf("Enter %d element for the second array:\n", m);
    for (int i = 0; i < m; i++) {
        printf("arr2[%d]: ", i);
        scanf("%d", &arr2[i]);
        sum2 += arr2[i]; 
    }

    avg1 = (double) sum1 / n;
    avg2 = (double) sum2 / m;

    printf("\nSum of elements in the first array: %d\n", sum1);
    printf("Average sum of the elements in the first array: %.2f\n", avg1);

    printf("\nSum of elements in the second array: %d\n", sum2);
    printf("Average sum of the elements in the second array: %.2f\n", avg2);

    free(arr1);
    free(arr2);

    return 0;
}
