#include<stdio.h>
#include<stdlib.h>
#include<error.h>

void print_delim() {

    printf("--------------------\n");

}

void ex_1 () {

    char op;
    scanf("%c", &op);
    for (int i = 0; i < 10; i++) {
        printf("%c", op);
    }
    printf("\n");
    for (int i = 0; i < 3; i++) {
        for (int i = 0; i < 10; i++) {
            if (i == 0) {
                printf("%c", op);
            } else if (i == 9) {
                printf("%c\n", op);
            } else {
                printf(" ");
            }
        }
    }

    for (int i = 0; i < 10; i++) {
        printf("%c", op);
    }
    printf("\n");

}

void ex_2 () {

    int ln_cnt;
    char op;
    printf("Enter line count: ");
    scanf("%d", &ln_cnt);
    fflush(stdin);
    printf("Enter symbol: ");
    scanf("%c", &op);

    for (int i = 0; i <= ln_cnt; i++) {

        for (int s = 0; s <= ln_cnt - i; s++) {
            printf(" ");
        }
        for (int j = 0; j < (2 * i - 1); j++) {

            if (j == 0 || j == (2 * i - 2) || i == ln_cnt) {
                printf("%c", op);
            } else {
                printf(" ");
            }

        }
        printf("\n");
    }

}

void ex_7 () {

    float cel = 0, fahr = 0;
    printf("Enter degrees C: ");
    scanf("%f", &cel);
    fahr = (cel * 1.8) + 32;
    printf("Fahr: %.2f \n", fahr);

}

float calc (float a, float b, char op) {

    switch (op) {
        case '+': return (int)(a + b);
        case '-': return (int)(a - b);
        case '*': return (int)(a * b);
        case '/':
            if (b != 0) {
                return a / b;
            } else {
                perror("Division by 0\n");
                return 0;
            }
    }

}

void ex_12 () {

    float a, b;
    char op;
    printf("Enter a = ");
    scanf("%g", &a);
    fflush(stdin);
    printf("Enter b = ");
    scanf("%g", &b);
    fflush(stdin);
    printf("Enter op = ");
    scanf("%c", &op);
    fflush(stdin);

    float res = calc(a, b, op);
    printf("%g\n", res);

}

void ex_16 () {

    int n, w, l;
    int m, o;
    float tms = 0.2;

    printf("Size of ploshtadka: ");
    scanf("%d", &n);
    fflush(stdin);
    printf("Wight of plochki: ");
    scanf("%d", &w);
    fflush(stdin);
    printf("Length of plochki: ");
    scanf("%d", &l);
    fflush(stdin);
    printf("Wight of bench: ");
    scanf("%d", &m);
    fflush(stdin);
    printf("Length of bench: ");
    scanf("%d", &o);
    fflush(stdin);

    int s_1 = n * n, s_2 = w * l, s_3 = m * o;
    printf("S plochadka: %d\nS plochki: %d\nS bench: %d\n", s_1, s_2, s_3);
    int s_fin = s_1 - s_3;
    printf("S after bench: %d\n", s_fin);
    float cnt_fin = s_fin / s_2, tms_fin = tms * cnt_fin;
    printf("Count plochki: %g\nTime for placement: %g\n", cnt_fin, tms_fin);

}


int main (int argc, char *argv[]) {

    ex_1();
    fflush(stdin);
    print_delim();

    ex_2();
    fflush(stdin);
    print_delim();

    ex_7();
    fflush(stdin);
    print_delim();

    ex_12();
    fflush(stdin);
    print_delim();

    ex_16();
    fflush(stdin);
    print_delim();

    return 0;
}
