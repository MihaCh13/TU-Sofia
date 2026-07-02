#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN 0
#define MAX 99

int main() {
    int arr[10][10], i_min = 0, i_max = 0, B[10][10];

    printf("Enter array elements: \n");
    for (int i = 0; i < 10; i++) {
      for (int j = 0; j < 10; j++) {
        scanf("%d", &arr[i][j]);
        if (arr[i][j] < MIN || arr[i][j] > MAX) {
          printf("Invalid input\n");
          j--;
        }
      }
    }

    printf("The array is: \n");
    for (int i = 0; i < 10; i++) {
      for (int j = 0; j < 10; j++) {
        printf("%d ", arr[i][j]);
      }
    }

    int min = 99, max = 0;
    for (int i = 0; i < 10; i++) {
      for (int j = 0; j < 10; j++) {
        if (arr[i][j] < min) {
          min = arr[i][j];
          i_min = i;
        }
        if (arr[i][j] > max) {
          max = arr[i][j];
          i_max = i;
        }
      }
    }

    for (int i = 0; i < 10; i++) {
      for (int j = 0; j < 10; j++) {
        if (i == i_min) {
          B[i][j] = arr[i_max][j];
        }
        else if (i == i_max) {
          B[i][j] = arr[i_min][j];
        }
        else {
          B[i][j] = arr[i][j];
        }
      }

    }

    printf("The switch array is: \n");
    for (int i = 0; i < 10; i++) {
      for (int j = 0; j < 10; j++) {
        printf("%d ", B[i][j]);
      }
    }
    return 0;
}
