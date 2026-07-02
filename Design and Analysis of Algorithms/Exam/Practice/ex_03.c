#include <stdio.h>
#include <stdlib.h>
#include <string.h>

# define MAX 999.999
# define MIN -999.999
int main() {
    float A[10][20], m, n, q, B[10][20];
    int count = 0;
    scanf("%f %f %f", &m, &n, q);
    printf("Enter Matrix A:\n");
    for (int i = 0; i < 10; i++) {
      for (int j = 0; j < 20; j++) {
        scanf("%f", &A[i][j]);
        if (A[i][j] < MIN || A[i][j] > MAX) {
          printf("Invalid Input\n");
          j--;
        }
        else{
          if (m<=A[i][j] && A[i][j]<=n && A[i][j]<0) {
            B[i][j] = q;
            count++;
          }
          else {
            B[i][j] = A[i][j];
          }
      }
    }

    printf("Matrix A:\n");
    for (int i = 0; i < 10; i++) {
      for (int j = 0; j < 20; j++) {
        printf("%f\t", A[i][j]);
      }
      printf("\n");
    }

    printf("New Matrix B:\n");
    for (int i = 0; i < 10; i++) {
      for (int j = 0; j < 20; j++) {
        printf("%f\t", B[i][j]);
      }
      printf("\n");
    }
    return 0;
  }
}