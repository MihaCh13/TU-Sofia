#include "data.h"

int main()
{
    unsigned size,cnt=0;
    int *array,**matrix;

    printf("Input Size:");
    scanf("%u",&size);

    array = (int*)malloc(size*sizeof(int));
    if (array==NULL){
        perror(NULL);
        exit(errno);
    }

    randomArray(array,size);
    printArray(array,size);

    free(array);

    puts("===========================");

    matrix = (int**)malloc(size*sizeof(int*));
    if (matrix == NULL){
        perror("Memory error for matrix: ");
        exit(EXIT_FAILURE);
    }

    for (int i=0;i<size;++i,++cnt){
        if ((matrix[i] = (int*)malloc(size*sizeof(int)))==NULL){
            printf("%d\n",errno);
            break;
        }
    }

    randomMatrix(matrix,cnt);
    printMatrix(matrix,cnt);

    for (int i=0;i<cnt;++i){
        free(matrix[i]);
    }
    free(matrix);
    puts("=======================");

    return 0;
}
