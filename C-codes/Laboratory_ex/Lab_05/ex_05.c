#include <stdio.h>
#include <stdlib.h>

int main()
{

 int A[3][4]=
 {
     {1,2,3,4},
     {5,6,7,8},
     {9,0,1,2}
 };
 int B[2][2]=
 {
     {6,7},
     {0,1}
 };
 int m=3,n=4;
 int p=2,q=2;
 int found=0;

 for(int i=0; i<=m-p;i++)
 {
     for(int j=0; j<=n-q;j++)
     {
         int match=1;

         for(int x=0; x<p;x++)
         {
             for(int y=0; y<q;y++)
            {
                if(A[i+x][j+y]!= B[x][y])
                {
                    match=0;
                    break;
                }
            }
             if(!match)break;

         }
          if(match)
          {
             found=1;
             break;
          }
     }
     if(found) break;
 }
 if(found)
    printf("Matrix B is in Matrix A.\n");
 else
     printf("Matrix B is NOT in Matrix A.\n");

    return 0;
}
