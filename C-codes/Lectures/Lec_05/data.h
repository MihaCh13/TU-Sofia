#ifndef DATA_H_INCLUDED
#define DATA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#define MIN 0
#define MAX 20
#define NL printf("\n")

void randomArray(int *arr,unsigned len);
void printArray(int *arr,unsigned len);
void randomMatrix(int **matrix,unsigned len);
void printMatrix(int **matrix,unsigned len);

#endif // DATA_H_INCLUDED
