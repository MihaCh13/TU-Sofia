#include <stdio.h>
#include <stdlib.h>


int main()
{
   int numbers[7];
   int sum=0;
   float average;
   int closest;
   int position;

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
   closest=numbers[0];
   position=0;
   float min_diff=fabs(numbers[0]-average);
   for (int i=1;i<7;i++)
   {
       float diff=fabs(numbers[i]-average);
       if (diff<min_diff)
       {
           min_diff=diff;
           closest=numbers[i];
           position=i;
       }
   }
    printf("average: %.2f\n",average);
      printf("Closest value: %d to %d place\n",closest,position+1);

   return 0;
}
