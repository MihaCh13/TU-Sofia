#include <stdio.h>

void first_exam()
{
    float matrix[10][10];
    int row_size = sizeof(matrix)[0]/sizeof(float);
    int column_size = sizeof(matrix)/(row_size*sizeof(float));

    float positive_array[row_size*column_size], temporary;
    int position = 0;

    printf("Extract all positive numbers from the matrix & sort them.\n");
    printf("Solution BY: Elena Antonova\n\n");

    printf("Enter Elements:\n");
    for (int i = 0; i < row_size; i++)
    {
        for (int j = 0; j < column_size; j++)
        {
            do
                {
                    printf("matrix[%d][%d] = ", i, j);
                    scanf("%f", &matrix[i][j]);
                }
            while (!(matrix[i][j] >= - 999.99 && matrix[i][j] <= 999.99));
        }
    }

    printf("\nMatrix:\n");
    for (int i = 0; i < row_size; i++)
    {
        for (int j = 0; j < column_size; j++) {printf("%.2f ", matrix[i][j]);}
        printf("\n");
    }
    printf("\n");

    for (int i = 0; i < row_size; i++)
    {
        for (int j = 0; j < column_size; j++)
        {
            if (matrix[i][j] > 0)
            {
                positive_array[position] = matrix[i][j];
                position++;
            }
        }
    }

    printf("Array: ");
    for (int i = 0; i < position; i++) {printf("%.2f ", positive_array[i]);}
    printf("\n");

    for (int i = 0; i < position - 1; i++)
    {
        for (int j = i + 1; j < position; j++)
        {
            if (positive_array[i] > positive_array[j])
            {
                temporary = positive_array[i];
                positive_array[i] = positive_array[j];
                positive_array[j] = temporary;
            }
        }
    }

    printf("Sorted Array: ");
    for (int i = 0; i < position; i++) {printf("%.2f ", positive_array[i]);}
}
