#include <stdio.h>
#include <stdlib.h>

int main()
{

   int num =42;
   //dekralaciq na ukazatelq i priswoqwane na adresa na num
   int *ptr=&num;
   //stoinost na adresa chrez ukazatelq
   printf("%d\n",num);
   printf("%p\n",(void*)&num);
    return 0;
}
