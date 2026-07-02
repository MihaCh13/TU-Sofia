#include <stdio.h>
#include <stdlib.h>

int main()
{
    int N; // declare a variable for the size
    printf("Enter Matrix Size: ");
    scanf("%d", &N);

    int A[N][N]; // declare the matrix [integers, because of the range]
    printf("Calculate the average value of all elements above the main diagonal in the range [K - L], divisible by R.\n");
    printf("Solution BY: FirstName LastName\n\n");

    printf("Enter Elements:\n");
    int i, j; // loop iterators
    for (i = 0; i < N; i++) // loop through rows
    {
        for (j = 0; j < N; j++) // loop through columns
        {
            do
            {
                printf("A[%d][%d] = ", i, j);
                scanf("%d", &A[i][j]); // enter value
            } while (!(A[i][j] >= -999 && A[i][j] <= 999)); // if the value is outside the range, enter another

        }
    }

    printf("\nMatrix:\n"); // print the input values
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            {
                printf("%d ", A[i][j]);
            }
        printf("\n"); // add a new line after each row
    }
    printf("\n");

    int K, L, R; // the [K-L] range & the divisor R
    printf("Enter K, L & R: ");
    scanf("%d %d %d", &K, &L, &R);

    int sum = 0, count = 0; // since we're going to calculate an average value
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            {
               if (i < j && A[i][j] >= K && A[i][j] <= L && A[i][j] % R == 0) // if all of these are true
               {
                   sum += A[i][j]; // add the value to the sum
                   count++; // increase the count by one
               }
            }
    }
    float average = (float)sum/count; // calculate the average value
    printf("Average Value: %.2f\n", average); // print the result

   system("pause");
   return 0;
}