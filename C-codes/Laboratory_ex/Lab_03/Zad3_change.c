#include <stdio.h>
#include <stdlib.h>


int main()
{
   int a,b;
   int *ptrA=&a,*ptrB=&b;
   scanf("%d %d",&a,&b);
   *ptrA=*ptrA+*ptrB;
   *ptrB=*ptrA-*ptrB;
   *ptrA=*ptrA-*ptrB;


   printf("After change: a=%d, b=%d\n",a,b);



   return 0;
}
