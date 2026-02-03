#include<stdio.h>
#include<stdlib.h>
#include<error.h>
#include<unistd.h>

void print_delim() {

    printf("--------------------\n");

}

void high_or_low (int a, int b, char opt) {

    switch (opt) {
        case 'h': return (a > b) ? a : b; break;
        case 'l': return (a < b) ? a : b; break;
    }

}

void ex_1 () {

    int tmp = -1, num = -1, high = -1, low = 65766;
    while (num != 0) {
        printf("Enter a number: ");
        scanf("%d", &num);
        if (num > high) {
            high = num;
        } else if (num < low) {
            low = num;
        }
    }
    printf("Highest: %d \tLowest: %d\n", high, low);

}

void ex_5 () {

    int sec = -1, summ = 0, min = 0;
    while (sec != 0) {
        printf("Enter competitor speed: ");
        scanf("%d", &sec);
        fflush(stdin);
        if (sec == 0) break;
        summ += sec;
    }
    printf("0: Summ = %d", summ);
    min = summ / 60;
    int remaining = summ % 60;
    printf("Total: %d:%02d\n", min, remaining);

}

void ex_3 () {

    int a, b, c;
    printf("Enter a number: ");
    scanf("%d", &a);
    printf("Enter b number: ");
    scanf("%d", &b);
    printf("Enter c number: ");
    scanf("%d", &c);
    (a == b && b == c && a ==c) ? printf("Yes\n") : printf("No\n");

}

void ex_10 () {

    float p1, p2, p3, p4, p5;
    FILE *fd;
    fd = fopen("test.txt", "r");
    if (fd == NULL) {
        printf("Error opening file.\n");
        return;
    }

    int n = 0;
    fscanf(fd, "%d", &n);
    if (n <= 0) {
        printf("Invalid array size.\n");
        fclose(fd);
        return;
    }

    int *arr = (int*)malloc(n*sizeof(int));
    for (int i = 0; i < n; i++) {
        fscanf(fd, "%d", &arr[i]);
        //printf("[%d] %d\n", i, arr[i]);
    }

    int region_1 = 0, region_2 = 0, region_3 = 0, region_4 = 0, region_5 = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] >= 0 && arr[i] <= 199) {
            region_1++;
        } else if (arr[i] >= 200 && arr[i] <= 399) {
            region_2++;
        } else if (arr[i] >= 400 && arr[i] <= 599) {
            region_3++;
        } else if (arr[i] >= 600 && arr[i] <= 799) {
            region_4++;
        } else if (arr[i] >= 800 && arr[i] <= 1000) {
            region_5++;
        }
    }
    printf("%d\n%d\n%d\n%d\n%d\n", region_1, region_2, region_3, region_4, region_5);
    p1 = ((float)region_1 / n) * 100;
    p2 = ((float)region_2 / n) * 100;
    p3 = ((float)region_3 / n) * 100;
    p4 = ((float)region_4 / n) * 100;
    p5 = ((float)region_5 / n) * 100;
    printf("%g%%\n%g%%\n%g%%\n%g%%\n%g%%\n", p1, p2, p3, p4, p5);

    free(arr);

}

void ex_11 () {

    int n;
    printf ("Enter n = ");
    scanf("%d", &n);
    int width = 2*n, heigth = n, inside_width = n / 2;
    int mid = width - 4 - 2 * inside_width;

    // -----------------------------------------------------------------
    // Otgore
    // Kula 1
    printf("/");
    for (int i = 0; i < inside_width; i++) {
        printf("^");
    }
    printf("\\");

    // Mezhdu kulite
    for (int i = 0; i < mid; i++) {
        printf("_");
    }

    // Kula 2
    printf("/");
    for (int i = 0; i < inside_width; i++) {
        printf("^");
    }
    printf("\\\n");

    // -----------------------------------------------------------------
    // Prazno
    for (int i = 0; i < n - 3; i++) {
        printf("|");
        for (int j = 0; j < width - 2; j++) {
            printf(" ");
        }
        printf("|\n");
    }

    // -----------------------------------------------------------------
    // Predposledno
    if (n > 2) {
        printf("|");
        for (int i = 0; i < inside_width; i++) {
            printf(" ");
        }
        printf("_");
        for (int i = 0; i < mid; i++) {
            printf("_");
        }
        printf("_");
        for (int i = 0; i < inside_width; i++) {
            printf(" ");
        }
        printf("|\n");
    }

    // -----------------------------------------------------------------
    // Posledno
    printf("\\");
    for (int i = 0; i < inside_width; i++) {
        printf("_");
    }
    printf("/");
    for (int i = 0; i < mid; i++) {
        printf (" ");
    }
    printf("\\");
    for (int i = 0; i < inside_width; i++) {
        printf("_");
    }
    printf("/\n");


}

int main () {

    ex_1();
    print_delim();
    fflush(stdin);
    ex_5();
    print_delim();
    fflush(stdin);
    ex_3();
    print_delim();
    fflush(stdin);
    ex_10();
    print_delim();
    fflush(stdin);
    ex_11();
    print_delim();
    fflush(stdin);

    return 0;
}
