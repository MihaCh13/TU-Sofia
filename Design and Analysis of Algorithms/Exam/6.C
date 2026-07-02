#include <stdio.h>
#include <stdlib.h>

int main()
{
    int matrix[3][3]; // the size should be 10, but it's 3 for testing purposes

    int row_size = sizeof(matrix)[0]/sizeof(float);
    int column_size = sizeof(matrix)/(row_size*sizeof(float));

    printf("Swap the rows with MIN & MAX element.\n");
    printf("Solution BY: Elena Antonova\n\n");

    printf("Enter Elements:\n");
    int i, j;
    for (i = 0; i < row_size; i++)
    {
        for (j = 0; j < column_size; j++)
        {
            do
                {
                    printf("matrix[%d][%d] = ", i, j);
                    scanf("%d", &matrix[i][j]);
                }
            while (!(matrix[i][j] >= 0 && matrix[i][j] <= 99));
        }
    }

    printf("\nMatrix:\n");
    for (i = 0; i < row_size; i++)
    {
        for (j = 0; j < column_size; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    int MIN, MAX;
    MIN = MAX = matrix[0][0];

    int MIN_row, MIN_column, MAX_row, MAX_column;
    MIN_row = MIN_column = MAX_row = MAX_column = 0;

    int temporary;

    for (i = 0; i < row_size; i++)
    {
        for (j = 1; j < column_size; j++)
        {
            if (MIN > matrix[i][j])
                {
                    MIN = matrix[i][j];
                    MIN_row = i;
                    MIN_column = j;
                }
            if (MAX < matrix[i][j])
                {
                    MAX = matrix[i][j];
                    MAX_row = i;
                    MAX_column = j;
                }
        }
    }

    printf("\nMIN element: matrix[%d][%d] = %d.\n", MIN_row, MIN_column, MIN);
    printf("MAX element: matrix[%d][%d] = %d.\n", MAX_row, MAX_column, MAX);

        for (j = 0; j < column_size; j++)
        {
            temporary = matrix[MIN_row][j];
            matrix[MIN_row][j] = matrix[MAX_row][j];
            matrix[MAX_row][j] = temporary;
        }

    printf("\nSwapped Matrix:\n");
    for (i = 0; i < row_size; i++)
    {
        for (j = 0; j < column_size; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    
    system("pause");
    return 0;
}
