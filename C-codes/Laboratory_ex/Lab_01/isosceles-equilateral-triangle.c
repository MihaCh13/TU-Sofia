#include <stdio.h>
#include <stdlib.h>

int main()
{
    char symbol;
    int height;
    scanf("%c", &symbol);
    scanf("%d", &height);

    for (int i = 1; i <= height; i++){
        for (int j = 1; j <= height - i; j++){
                printf(" ");
        }

        for (int j = 1; j <= (2*i - 1); j++){
                printf("%c", symbol);
        }

         printf("\n");
    }
    return 0;
}
