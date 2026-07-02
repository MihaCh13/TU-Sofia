#include <stdio.h>
#include <stdlib.h>

# define MAX 999
# define MIN -999

int main() {
    int C[10][10];
    // Добре е да нулираш масивите за броене, макар че ги пълниш после
    int negative_in_row[10], negative_in_col[10];

    // --- 1. ВХОД (Кодът ти е супер тук) ---
    printf("Enter matrix elements (-999 to 999):\n");
    for (int i = 0; i < 10; i++) {
      for (int j = 0; j < 10; j++) {
        scanf("%d", &C[i][j]);
        if (C[i][j] < MIN || C[i][j] > MAX) {
          printf("Invalid input\n");
          j--;
        }
      }
    }

    // --- 2. ИЗВЕЖДАНЕ НА ВХОДА ---
    printf("The matrix elements are:\n");
    for (int i = 0; i < 10; i++) {
      for (int j = 0; j < 10; j++) {
        printf("%d\t", C[i][j]); // Сложих \t за красота
      }
      printf("\n");
    }

    // --- 3. БРОЕНЕ ПО РЕДОВЕ ---
    for (int i = 0; i < 10; i++) {
      int count = 0; // Ползвам count вместо row, за да не се бърка с индекса
      for (int j = 0; j < 10; j++) {
        if (C[i][j] < 0) {
           count++;
        }
      }
      negative_in_row[i] = count;
    }

    // --- 4. БРОЕНЕ ПО КОЛОНИ ---
    for (int j = 0; j < 10; j++) {
      int count = 0;
      for (int i = 0; i < 10; i++) {
        if (C[i][j] < 0) {
          count++;
        }
      }
      negative_in_col[j] = count;
    }

    // --- 5. ПРИНТИРАНЕ НА БРОЙКИТЕ ---
    for (int i = 0; i < 10; i++) {
      // ПОПРАВКА: i+1 за колоните, не i+2
      printf("Row %d has %d negatives. | Col %d has %d negatives.\n",
             (i+1), negative_in_row[i], (i+1), negative_in_col[i]);
    }

    // --- 6. ТЪРСЕНЕ НА НАЙ-МАЛКО (MINIMUM) ---
    // ВАЖНО: Инициализираме с първите елементи, а не с 0!

    int min_row_val = negative_in_row[0]; // Колко отрицателни има в ред 0
    int min_row_idx = 0;                  // Индексът е 0

    int min_col_val = negative_in_col[0]; // Колко отрицателни има в колона 0
    int min_col_idx = 0;                  // Индексът е 0

    for (int i = 1; i < 10; i++) { // Започваме от 1, защото 0 вече сме взели

        // Проверка за РЕДОВЕ
        if (negative_in_row[i] < min_row_val) { // Търсим по-малко (<)
            min_row_val = negative_in_row[i];
            min_row_idx = i;
        }

        // Проверка за КОЛОНИ
        if (negative_in_col[i] < min_col_val) { // Търсим по-малко (<)
            min_col_val = negative_in_col[i];
            min_col_idx = i;
        }
    }

    // --- 7. РЕЗУЛТАТ ---
    printf("\nRow with LEAST negative elements is: %d (count: %d)\n", min_row_idx + 1, min_row_val);
    printf("Col with LEAST negative elements is: %d (count: %d)\n", min_col_idx + 1, min_col_val);

    return 0;
}