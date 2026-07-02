#include <stdio.h>
#include <stdlib.h>

int main()
{
    // The sizes should be 10 & 20, but they're not suitable for testing:
    float A[3][3]; // matrix declaration [floats, because of the range]
    printf("Copy the numbers from the matrix into another one & replace the negative ones within [K - L] with Q & count them.\n");
    printf("Solution BY: FirstName LastName\n\n");

    printf("Enter Elements:\n");
    int i, j;
    for (i = 0; i < 3; i++) // loop through rows
    {
        for (j = 0; j < 3; j++) // loop through columns
        {
            do
                {
                    printf("A[%d][%d] = ", i, j);
                    scanf("%f", &A[i][j]);
                }
            // Check if the entered value is outside the given interval:
            while (!(A[i][j] >= - 999.9 && A[i][j] <= 999.9));
        }
    }

    // Print the matrix elements:
    printf("\nMatrix A:\n");
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
            {
                printf("%.2f ", A[i][j]);
            }
        printf("\n"); // add a new line after each row
    }
    printf("\n");

    float B[3][3]; // create the new 2D array [with the same size]
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
            {
                B[i][j] = A[i][j]; // copy the elements
            }
    }
    // Print the matrix elements:
    printf("\nMatrix B:\n");
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
            {
                printf("%.2f ", B[i][j]);
            }
        printf("\n"); // add a new line after each row
    }
    printf("\n");

    int K, L;
    float Q;
    int count = 0;
    // Enter the interval's lower & upper limit:
    printf("Enter K & L: ");
    scanf("%d %d", &K, &L);

    // Enter the substitution number:
    printf("Enter Q: ");
    scanf("%f", &Q);

    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
            {
                if (B[i][j] < 0 && B[i][j] >= K && B[i][j] <= L)
                {
                    B[i][j] = Q;
                    count++;
                }
            }
    }

    printf("\nMatrix B [modified]:\n");
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
            {
                printf("%.2f ", B[i][j]);
            }
        printf("\n"); // add a new line after each row
    }
    printf("\nModified Element Count: %d\n", count);


    system("pause");
    return 0;
}