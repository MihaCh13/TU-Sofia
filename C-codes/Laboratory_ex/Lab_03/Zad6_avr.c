#include <stdio.h>
#include <stdlib.h>


int main()
{
   int numbers[7];
   int sum=0;
   float average;
   for (int i=0;i<7;i++)
    {
        scanf("%d",&numbers[i]);
   if (numbers[i]<-5000 || numbers[i]>5000)
   {
       printf("Error!!");
       i--;
       continue;
   }

   sum+=numbers[i];}
   average=(float)sum/7;

    printf("average: %.3f\n",average);

   return 0;
}
