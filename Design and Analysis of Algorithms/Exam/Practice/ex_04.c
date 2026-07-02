#include <stdio.h>
#include <stdlib.h>
#include <string.h>

# define MIN -9999
# define MAX 9999

int main() {
  int min, max, m, temp;

  printf("Enter the number of rows and columns: \n");
  scanf("%d", &m);

  int A[m][m];

  printf("Enter the elements of the matrix A[%d][%d]: \n", m, m);
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < m; j++) {
      scanf("%d", &A[i][j]);
      if (A[i][j] < MIN || A[i][j] > MAX) {
        printf("Invalid Input\n");
        j--;
      }
    }
  }

  int max_n [m];

  for (int j = 0; j < m; j++) {
    int max = -9999;
    for (int i = 0; i < m; i++) {
      if (A[i][j] > max) {
        max = A[i][j];
      }
    }
    max_n[j] = max;
  }

  printf("The matrix A is: \n");
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < m; j++) {
      printf("%d ", A[i][j]);
    }
    printf("\n");
  }

  for (int i = 0; i < m - 1; i++) {
    for (int j = 0; j < m - i - 1; j++) {

      if (max_n[j] > max_n[j + 1]) {
        temp = max_n[j];
        max_n[j] = max_n[j + 1];
        max_n[j + 1] = temp;
      }
    }
  }


  printf("The biggest number in the matrix A from all columns is: %d and the smallest big num is: %d \n", max_n[m-1], max_n[0]);
}
