#include <stdio.h>
#include <stdlib.h>

int main()
{
    int size;
    printf("Enter Matrix Size: ");
    scanf("%d", &size);

    float matrix[size][size];

    printf("Double all elements outside [A-B] & transpose the matrix.\n");
    printf("Solution BY: Elena Antonova\n\n");

    printf("Enter Elements:\n");
    int i, j;
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            do
                {
                    printf("matrix[%d][%d] = ", i, j);
                    scanf("%f", &matrix[i][j]);
                }
            while (!(matrix[i][j] >= -999.99 && matrix[i][j] <= 999.99));
        }
    }

    printf("\nMatrix:\n");
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            printf("%.2f ", matrix[i][j]);
        }
        printf("\n");
    }

    int A, B;
    printf("Enter A & B: ");
    scanf("%d %d", &A, &B);

    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            if (!(matrix[i][j] >= A && matrix[i][j] <= B))
            {
                matrix[i][j] *= 2;
            }
        }
    }

    float temporary;

    for (i = 0; i < size; i++)
    {
        for (j = 0; j < i; j++)
        {
                temporary = matrix[i][j];
                matrix[i][j] = matrix[j][i];
                matrix[j][i] = temporary;
        }
    }

    printf("\nDoubled & Transposed Matrix:\n");
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            printf("%.2f ", matrix[i][j]);
        }
        printf("\n");
    }
    
    system("pause");
    return 0;
}
