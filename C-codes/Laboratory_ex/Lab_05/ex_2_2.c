#include <stdio.h>
#include <stdlib.h>

int main()
{
    int arr[3][3] = {
        {1, 1, 3},
        {9, 3, 3},
        {3, 7, 3}
    };


    int sum1 = arr[0][0] + arr[0][1] + arr[0][2];
    int sum2 = arr[1][0] + arr[1][1] + arr[1][2];
    int sum3 = arr[2][0] + arr[2][1] + arr[2][2];

    int sum4 = arr[0][0] + arr[1][0] + arr[2][0];
    int sum5 = arr[0][1] + arr[1][1] + arr[2][1];
    int sum6 = arr[0][2] + arr[1][2] + arr[2][2];

    int sum7 = arr[0][0] + arr[1][1] + arr[2][2];
    int sum8 = arr[0][2] + arr[1][1] + arr[2][0];


    if (sum1 == sum2 && sum2 == sum3 && sum3 == sum4 && sum4 == sum5 && sum5 == sum6 && sum6 == sum7 && sum7 == sum8)
    {
        printf("The square is magical!\n");
    }
    else
    {
        printf("The square is NOT magical!\n");
    }

    return 0;
}
