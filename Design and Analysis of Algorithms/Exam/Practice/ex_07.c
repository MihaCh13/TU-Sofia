#include <stdio.h>
#include <stdlib.h>
#include <string.h>

# define MAX 500
# define MIN -500

int main() {
  int A[10][10], m, count_m = 0, n, count_n = 0;

  printf("Please enter m:\n");
  scanf("%d", &m);
  printf("Please enter n:\n");
  scanf("%d", &n);

  printf("Please enter matrix elements\n");
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      scanf("%d", &A[i][j]);
      if (A[i][j] < MIN || A[i][j] > MAX) {
        printf("Invalid input\n");
        j--;
      }
    }
  }

  printf("The matrix elements are:\n");
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      printf("%d ", A[i][j]);
    }
    printf("\n");
  }

  for (int i = 0; i < 10; i++) {
    int min = 500;
    int max = -500;
    int min_j = 0;
    int max_j = 0;

    for (int j = 0; j < 10; j++) {
      if (A[i][j] < min) {
        min = A[i][j];
        min_j = j;
      }
      if (A[i][j] > max) {
        max = A[i][j];
        max_j = j;
      }
    }
    A[i][min_j] = A[i][0];
    A[i][max_j] = A[i][9];
    A[i][0] = min;
    A[i][9] = max;

    if (max > m) {
      count_m ++;
    }
    if (min < n) {
      count_n ++;
    }
  }

  printf("The new matrix elements are:\n");
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      printf("%d ", A[i][j]);
    }
    printf("\n");
  }

  printf("The number of max elements bigger the M is: %d\n", count_m);
  printf("The number of min elements smaller the N is: %d\n", count_n);

    return 0;
}
