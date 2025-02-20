#include <stdio.h>
#include <stdlib.h>

int main()
{
    char symbol;
    scanf("%c", &symbol);

    int height;
    scanf("%d", &height);

    for (int i = 1; i <= height; i++){
        for (int j = 1; j <= height - i; j++){
                printf(" ");
        }

        for (int j = 1; j <= (2*i - 1); j++){
                if (j== 1 || j == (2*i-1) || i==height){
                    printf("%c", symbol);
                }
                else{
                    printf(" ");
                }
        }

         printf("\n");

    }
printf("Kuh e toi, kuh e!!!!!!!\n Ne plachi maiko, ne tuji, che stanah aze prazen...\n Ta tebe kleta ostavih za prazno chedo da jalish\n No kulni maiko proklinai,\n taz turska cherna kuhost\n Deto nas mladi propudi po tejka praznina, da hodim da se skitame\n nepulni, prazni, kuhi\n");
printf("\n");
printf("\tIZTURBUSHENI - ot Sami & Miha");
printf("\n");
    return 0;
}
