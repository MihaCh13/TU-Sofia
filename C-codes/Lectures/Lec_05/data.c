#include "data.h"

void randomArray(int *arr,unsigned len)
{
    for (int i=0;i<len;++i){
        arr[i] = rand()%(MAX-MIN+1)+MIN;
    }
}

void printArray(int *arr,unsigned len)
{
    for (int i=0;i<len;++i){
        printf("%d\t",arr[i]);
    }
    NL;
}

void randomMatrix(int **matrix,unsigned len)
{
    for (int i=0;i<len;++i){
        for (int j=0;j<len;++j){
            matrix[i][j] = rand()%(MAX-MIN+1)+MIN;
        }
    }
}

void printMatrix(int **matrix,unsigned len)
{
    for (int i=0;i<len;++i){
        for(int j=0;j<len;++j){
            printf("%d\t",matrix[i][j]);
        }
        NL;
    }
}
