#include <stdio.h>

void matrix_IO()
{
    // Variables for matrix dimensions:
    int rows, columns;
    printf("Enter matrix dimensions: ");
    scanf("%d %d", &rows, &columns);

    int matrix[rows][columns]; // declare a matrix with these dimensions

    printf("Enter matrix elements:\n");
    for (int i = 0; i < rows; i++) // outer loop for rows
    {
        for (int j = 0; j < columns; j++) // inner loop for each row's columns
        {
            printf("matrix[%d][%d] = ", i, j);
            scanf("%d", &matrix[i][j]);
        }
    }
    printf("Matrix:\n");
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}
