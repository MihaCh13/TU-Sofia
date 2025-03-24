#include <stdio.h>
#include <stdlib.h>

int main()
{

int m,n;
scanf("%d %d",&m,&n);
int matrix[m][n];
int value=1;

for(int i=0;i<m;i++)
{
  if(i%2==0)
  {
      for(int j=0;j<n;j++)
      {
          matrix[i][j]=value++;
      }
  }
  else
  {
    for(int j=n-1;j>=0;j--)
    {
        matrix[i][j]=value++;
    }
  }
}
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n; j++)
        {
            printf("%3d",matrix[i][j]);
        }
        printf("\n");
    }
    return 0;
}
