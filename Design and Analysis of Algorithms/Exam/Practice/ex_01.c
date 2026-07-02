#include <stdio.h>
#include <stdlib.h>
#include <string.h>

# define MIN_VALUE -999.9
# define MAX_VALUE 999.9

void bubbleSort(float arr[], int n) {
  float temp;
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - i - 1; j++) {
      if (arr[j] > arr[j + 1]) {
        temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
    }
  }
}

int main() {
    float A[10][10];
    float positive[100];
    int p_num_counter = 0;
    int i, j;

    // --- 1. ИЗВЕЖДАНЕ НА УСЛОВИЕ И АВТОР ---
    printf("ZADACHA 1: Obrabotka na masiv A[10][10]\n");
    printf("AVTOR: Ime Familiya, Fak. Nomer: .....\n");
    printf("----------------------------------------\n");

    // --- 2. ВЪВЕЖДАНЕ НА ВХОДНИ ДАННИ ---
    printf("Vyvedete 100 chisla (Red po red):\n");

    for (i = 0; i < 10; i++) {       // Декларираме i, j горе, тук само ползваме
      for (j = 0; j < 10; j++) {

        printf("A[%d][%d] = ", i, j); // Добавих подсказка, за да е ясно
        scanf("%f", &A[i][j]);

        // ВАЛИДАЦИЯ
        if (A[i][j] < MIN_VALUE || A[i][j] > MAX_VALUE) {
          printf("Invalid input! Try again.\n");
          j--;       // Връщаме стъпка назад
          continue;  // <--- ВАЖНО: Прескачаме всичко останало и въртим цикъла наново!
        }

        // ПЪЛНЕНЕ НА НОВИЯ МАСИВ (Само ако входът е бил валиден)
        if (A[i][j] > 0) {
          positive[p_num_counter] = A[i][j];
          p_num_counter++;
        }
      }
    }

    // --- 3. ИЗВЕЖДАНЕ НА ВХОДНИТЕ ДАННИ (Матрицата) ---
    printf("\nVyvedenata matrica e:\n");
    for (i = 0; i < 10; i++) {
      for (j = 0; j < 10; j++) {
        printf("%.2f\t", A[i][j]);
      }
      printf("\n");
    }

    // --- 4. СОРТИРАНЕ И ИЗВЕЖДАНЕ ---
    bubbleSort(positive, p_num_counter);

    // Директно принтираме positive. Той вече е сортиран.
    // Няма нужда от sorted_arr!
    printf("\nSorted positive numbers:\n");
    for (i = 0; i < p_num_counter; i++) {
      printf("%.2f, ", positive[i]);
    }
    printf("\n");

    return 0;
}