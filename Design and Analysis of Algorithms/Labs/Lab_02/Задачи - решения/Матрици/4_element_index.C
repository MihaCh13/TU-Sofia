#include <stdio.h>

void element_by_index()
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

    // Declare a pointer to the first element of the matrix:
    int *pointer = &matrix[0][0];

    int index; // the index of the element we're looking for
    printf("Enter index: ");
    scanf("%d", &index);

    // If we type 5, we will be taken to the 5ᵗʰ element of the matrix.
    // This is accomplished via dereferencing:
    printf("Matrix Element №%d: %d.\n", index, *(pointer + index));
}
