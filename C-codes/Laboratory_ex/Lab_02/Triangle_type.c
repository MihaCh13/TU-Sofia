#include <stdio.h>
#include <stdlib.h>

int main()
{
    float a,b,c;
    scanf("%f %f %f",&a,&b,&c);
    if ((a+b)>c && (a+c) > b && (b+c)>a){
        printf ("Triangle real\n");

        if (a==b && a==c && b==c)
        {
            printf("Triangle is rawnostranen");
        }
        else if (a==b || a==c || c==b){
            printf("Triangle is rawnobedren");
        }
        else {printf("TriaNGLE IS RAZNOSTRANEN");}
    }
    else {printf("Triangle NOT real");}

    return 0;
}
