#include <stdio.h>
#include <stdlib.h>

# define MAX 999
#define MIN -999

int main() {
    int A[10][10], i, j, r, a, b;
    int sum = 0;
    int count = 0;
    double avg;

    printf("ZADACHA 1: Obrabotka na masiv A[10][10]\n");
    printf("AVTOR: Ime Familiya, Fak. Nomer: .....\n");
    printf("----------------------------------------\n");

    // 2. ВЪВЕЖДАНЕ НА ВСИЧКИ УСЛОВИЯ (Липсваше R) !!!
    printf("Enter R (kratno) = ");
    scanf("%d", &r);

    printf("Enter interval start A = ");
    scanf("%d", &a);
    printf("Enter interval end B = ");
    scanf("%d", &b);

    printf("Vyvedete 100 chisla (Red po red):\n");

    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            printf("A[%d][%d] = ", i, j);
            scanf("%d", &A[i][j]);

            if (A[i][j] >= MIN && A[i][j] <= MAX) {
                if (i < j && A[i][j] % r == 0 && A[i][j] >= a && A[i][j] <= b) {
                    sum += A[i][j];
                    count++;
                }
            }
            else {
                printf("Invalid Input (Out of -999 to 999)\n");
                j--; // Връщаме назад
            }
        }
    }

    // Извеждане на матрицата
    printf("The matrix is :\n");
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            printf("%d\t", A[i][j]);
        }
        printf("\n");
    }

    // 3. ПРОВЕРКА ЗА ДЕЛЕНИЕ НА НУЛА И КАСТВАНЕ !!!
    if (count > 0) {
        avg = (double)sum / count; // (double) за да не отреже запетаята
        printf("Found %d elements.\n", count);
        printf("Sum: %d\n", sum);
        printf("Average: %.2f\n", avg);
    } else {
        printf("No elements found matching criteria.\n");
    }
    return 0;
}