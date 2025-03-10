#include <stdio.h>
#include <stdlib.h>


int main()
{
   int numbers[7];
   int max;
   for (int i=0;i<7;i++)
    {
        scanf("%d",&numbers[i]);
   if (numbers[i]<-5000 || numbers[i]>5000)
   {
       printf("Error!!");
       i--;
       continue;
   }
   max=numbers[0];
 for(int i=1;i<7;i++)
 {
     if (numbers[i]>max)
     {
         max=numbers[i];

     }
 }
    }
    printf("max: %d\n",max);

   return 0;
}
