#include <stdio.h>
#include <stdlib.h>

int main()
{
    int x;
    int y;
    scanf("%d%d", &x,&y);
    int suma = x +y;
    int raz = x - y;
    int pro = x * y;
    float chast = (float) x / y;
    printf("suma = %d\nrazlika = %d\nproizvedenie = %d\nchastno = %.2f", suma, raz, pro, chast);

    return 0;
}
