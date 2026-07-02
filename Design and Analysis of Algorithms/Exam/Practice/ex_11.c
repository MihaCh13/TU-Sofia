#include <stdio.h>
#include <stdlib.h>
#include <string.h>

# define MAX 99
# define MIN 0

int main() {
    int A[60], m, n, del;

    printf("Enter number for m: \n");
    scanf("%d", &m);
    printf("Enter number for n: \n");
    scanf("%d", &n);
    printf("Enter number for deletion: \n");
    scanf("%d", &del);

    if (del == 0){
      printf("Enter valid number (!= 0): \n");
      scanf("%d", &del);
    }

    printf("Enter array elements: \n");
    for (int i = 0; i < 60; i++) {
      scanf("%d", &A[i]);
      if (A[i] > MAX || A[i] < MIN) {
        printf("Invalid input\n");
        i--;
      }
    }

    for (int i = 0; i < 60; i++) {
      printf("%d, ", A[i]);
    }
    printf("\n");
    printf("M = %d\n", m);
    printf("N = %d\n", n);
    printf("Del = %d\n", del);

    for (int i = 0; i < 60; i++) {
      if (A[i] >= m && A[i] <= n && A[i] % del == 0) {
        printf("Index %d is 0 ", i);
        A[i] = 0;
      }
    }

    for (int i = 0; i < 60; i++) {
      printf("%d, ", A[i]);
    }
    printf("\n");
}
