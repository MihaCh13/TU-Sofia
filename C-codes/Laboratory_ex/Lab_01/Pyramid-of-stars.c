#include <stdio.h>
#include <stdlib.h>

int main()
{
    int rows = 8;
    for (int i = 1; i<=rows; i++){
            for(int j = 1; j <= i; j++){
                printf("* ");
            }
        printf("\n");
    }
    return 0;
}
