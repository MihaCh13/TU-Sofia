#include <stdio.h>
#include <stdlib.h>

void get_elements()
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
        for (int j = 0; j < columns; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    // Interval Variables:
    int x, y;
    printf("Enter X & Y: ");
    scanf("%d %d", &x, &y);

    int count = 0; // for the elements in the interval

    // Since we don't know how many elements we will add, the array is dynamic:
    int* array = (int*) malloc(count*sizeof(int));

    if (array == NULL)
    {
        fprintf(stderr, "Memory allocation failed!\n");
        return;
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            // If the current element is between X & Y:
            if (matrix[i][j] >= x && matrix[i][j] <= y)
            {
                count++;
                // Make space for the new element:
                array = (int*) realloc(array, count*sizeof(int));

                if (array == NULL)
                {
                    fprintf(stderr, "Memory allocation failed!\n");
                    return;
                }
                // Add the element:
                array[count - 1] = matrix[i][j];
            }
        }
    }

    printf("Elements between %d & %d: ", x, y);
    for (int i = 0; i < count; i++) {printf("%d ", array[i]);}
    free(array);
}
