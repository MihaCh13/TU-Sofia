#include <stdio.h>
#include <stdlib.h>
#include "main.h"

int main()
{
 //   int a[][3] = {{1,2,3},{4,5,6}};
 //   print(a,2,3);
    int a[3][3];
    float res[3];

    inputRandom(a,3,3);
    print(a,3,3);
    puts("=======================");
    printf("%d\n",sumMD(a,3));
    printf("%d\n",minBelowMD(a,3));
    printf("%d\n",maxAboveMD(a,3));
    puts("=======================");
    printf("%g\n",averageSD(a,3));
    printf("%d\n",sumNegAboveSD(a,3));
    printf("%d\n",sumPosBelowSD(a,3));
    puts("=======================");
    averageCols(a,3,res);
    printResult(res,3);

    return 0;
}

void inputRandom(int a[][NO_COLS],unsigned rows,unsigned cols)
{
    for (int i=0;i<rows;++i){
        for (int j=0;j<cols;++j){
            a[i][j] = rand()%(MAX-MIN+1)+MIN;
        }
    }
}

void print(int a[][NO_COLS],unsigned rows,unsigned cols)
{
    for (int i=0;i<rows;++i){
        for (int j=0;j<cols;++j){
            printf("%d\t",a[i][j]);
        }
        printf("\n");
    }
}

int sumMD(int a[][NO_COLS],unsigned cols)
{
    int sum = 0;

    for (int i=0;i<cols;++i){
        sum += a[i][i];
    }
    return sum;
}

int minBelowMD(int a[][NO_COLS],unsigned cols)
{
    int min = a[1][0];

    for (int i=1;i<cols;++i){   // i=0;
        for (int j=0;j<i;++j){    //j<=i;
            if (a[i][j]<min)
                min = a[i][j];
        }
    }
    return min;
}

int maxAboveMD(int a[][NO_COLS],unsigned cols)
{
    int max = a[0][1];

    for (int i=0;i<cols-1;++i){       // i<cols;
        for (int j=i+1;j<cols;++j){   // j=i;
            if (a[i][j]>max)
                max = a[i][j];
        }
    }
    return max;
}

float averageSD(int a[][NO_COLS],unsigned cols)
{
    int sum=0,cnt=0;

    for (int i=0;i<cols;++i){
        sum += a[i][cols-1-i];
        cnt++;
    }
    return (float)sum/cnt;
}

int sumNegAboveSD(int a[][NO_COLS],unsigned cols)
{
    int sum=0;

    for (int i=0;i<cols-1;++i){    // i<cols
        for (int j=0;j<cols-1-i;j++)   // j<cols-i
            if (a[i][j]<0)
                sum += a[i][j];
    }
    return sum;
}

int sumPosBelowSD(int a[][NO_COLS],unsigned cols)
{
    int sum=0;

    for (int i=1;i<cols;++i){    // i=0
        for (int j=cols-i;j<cols;j++)   // j=cols-1-i
            if (a[i][j]>0)
                sum += a[i][j];
    }
    return sum;
}

void averageCols(int a[][NO_COLS],unsigned cols,float avrs[])
{
    for (int j=0;j<cols;++j){
        avrs[j]=0;
        for (int i=0;i<cols;++i){
            avrs[j] += a[i][j];
        }
        avrs[j] /= cols;
    }
}

void printResult(float result[],unsigned cols)
{
    for (int i=0;i<cols;++i)
        printf("%g\t",result[i]);
    printf("\n");
}
