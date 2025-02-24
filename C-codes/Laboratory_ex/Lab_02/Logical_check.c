#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n;
    scanf("%d",&n);

    if (n%2==0)
    {
        printf("Chisloto e chetno!\n ");

    }
    else
    {
            printf("Chisloto e nechetno!\n");
    }

    if (n % 3 == 0 && n % 5 == 0)
            {
            printf("Chisloto e kratno na 3 i 5\n");
        }
    else
        {
        printf("Chisloto ne e kratno na 3 i 5\n");
        }

        if ( n > 0){
            printf("Chisloto e polojitelno\n");
        }
        else if (n < 0){
            printf("Chisloto e otritsatelno\n");
        }
        else{printf("Chisloto e 0\n");}

    return 0;
}
