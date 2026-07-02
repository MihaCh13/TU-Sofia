#include <stdio.h>
#include <stdlib.h>
#include <string.h>

# define MAX 999
# define MIN -999

int main() {
    int A[10];
    int p1 = -1, p2 = -1;
    int p1_index = 0, p2_index = 0;
    int sum_n = 0, sum_p = 0;

    printf("Please enter 10 numbers\n");
    for (int i = 0; i < 10; i++) {
      scanf("%d", &A[i]);
      if (A[i] < MIN || A[i] > MAX) {
        printf("Invalid input\n");
        i--;
      }
    }

    printf("The array is:\n");
    for (int i = 0; i < 10; i++) {
      printf("%d ", A[i]);
    }

    for (int i = 0; i < 10; i++) {
      if (A[i] > 0) {
        p1 = A[i];
        p1_index = i;
        break;
      }
    }

    for (int i = 9; i >= 0; i--) {
      if (A[i] > 0) {
        p2 = A[i];
        p2_index = i;
        break;
      }
    }

    if (p1 == -1 && p2 == -1) {
      printf("The array is have only negative numbers\n");
      return 1;
    }
    else {
      for (int i = p1_index + 1; i < p2_index; i++) {
        if (A[i] > 0) {
          sum_p += A[i];
        }
        else {
          sum_n += A[i];
        }
      }
    }

    if (sum_p % 2 == 0) {
      for (int i = 0; i < 10; i++) {
        if (A[i] > 0) {
          A[i] = 0;
        }
      }
      for (int i = 0; i < 10; i++) {
        printf("%d ", A[i]);
      }
      printf("\n");
    }

    printf("First positive number in the array is: %d\n", p1);
    printf("Last positive number in the array is: %d\n", p2);
    printf("The sum of positive numbers is %d\n", sum_p);
    printf("The sum of negative numbers is %d\n", sum_n);
    return 0;
}
