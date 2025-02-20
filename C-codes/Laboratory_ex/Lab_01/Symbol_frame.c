#include <stdio.h>
#include <stdlib.h>

int main()
{
    char znak;
    scanf("%c",&znak);

    for (int i = 1; i <= 10; i++){
        printf("%c", znak);
    }
    printf("\n");
    for (int j = 1; j<=5; j++){
        printf("%c", znak);
        printf("\t%c\n", znak);
    }

    for (int i = 1; i <= 10; i++){
        printf("%c", znak);
    }
    return 0;
}
