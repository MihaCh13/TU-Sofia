#include <stdio.h>

void change_elements()
{
    int rows, columns;
    printf("Enter matrix dimensions: ");
    scanf("%d %d", &rows, &columns);

    int matrix[rows][columns];

    printf("Enter matrix elements:\n");
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            printf("matrix[%d][%d] = ", i, j);
            scanf("%d", &matrix[i][j]);
        }
    }
    printf("Matrix:\n");
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++) {printf("%d ", matrix[i][j]);}
        printf("\n");
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            // If the current element is above the main diagonal & odd:
            if ((i < j) && (matrix[i][j] % 2 != 0))
            {
                matrix[i][j]++; // increment the element to make it even
                matrix[i][i]++; // increment the element on the main diagonal on the same row
            }
            // If the current element is below the main diagonal & even:
            if ((i > j) && (matrix[i][j] % 2 == 0))
            {
                matrix[i][j]--; // decrement the element to make it odd
                matrix[i][i]++; // increment the element on the main diagonal on the same row
            }
        }
    }

    printf("Matrix after Modification:\n");
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++) {printf("%d ", matrix[i][j]);}
        printf("\n");
    }
}
