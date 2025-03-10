#include <stdio.h>
#include <stdlib.h>


void calculate(int *a,int *b,int *sum,int *diff,int *prod,float*quot)
{
   *sum=*a+*b;
   *diff=*a-*b;
   *prod=(*a)*(*b);

   if (*b!=0)
   {
    *quot=(float)(*a)/(*b);
   }
   else
   {
    *quot=0;
   }
}


int main()
{
   int num1,num2,sum,diff,prod;
   float quot;
   scanf("%d %d",&num1,&num2);
   calculate(&num1,&num2,&sum,&diff,&prod,&quot);
   printf("sum: %d\n",sum);
   printf("diff: %d\n",diff);
   printf("prod: %d\n",prod);

   if(num2!=0)
   {
     printf("del: %.2f\n",quot);
   }
   else
   {
     printf("Error!!!!!");
   }
    return 0;
}
