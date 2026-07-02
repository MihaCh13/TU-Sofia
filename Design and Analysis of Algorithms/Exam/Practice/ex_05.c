#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 999.99
#define MIN -999.99
int main() {
    float a, b;
    int m;

    printf("Enter the size of the array: ");
    scanf("%d", &m);
    printf("Enter number between -999.99 and 999.99 for A: ");
    scanf("%f", &a);
    printf("Enter number between -999.99 and 999.99 for B (must be greater than A): ");
    scanf("%f", &b);

    float arr[m][m];
    printf("Enter array elements: ");
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < m; j++) {
        scanf("%f", &arr[i][j]);
        if (arr[i][j] < MIN || arr[i][j] > MAX) {
          printf("Array element is out of bounds\n");
          j--;
        }
        else{
          if (arr[i][j] < a || arr[i][j] > b) {
            arr[i][j] *= 2;
          }
        }
      }
    }

    printf("The array elements are:\n");
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < m; j++) {
        printf("%f\t", arr[i][j]);
      }
      printf("\n");
    }

    float T[m][m];

    for (int i = 0; i < m; i++) {
      for (int j = 0; j < m; j++) {
        T[i][j] = arr[j][i];
      }
    }

    printf("The trans array elements are:\n");
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < m; j++) {
        printf("%f\t", T[i][j]);
      }
    }
    return 0;
}
