#include <stdio.h>
#include <stdlib.h>

int main()
{

    int arr[3][3]={
        {1,2,3},
        {4,5,6},
        {7,8,9}};
    printf("%d, %d, %d\n",arr[0][0],arr[1][1], arr[2][2]);
    printf("%d, %d, %d\n",arr[0][2],arr[1][1], arr[2][0]);
    printf("%d, %d, %d\n",arr[0][1],arr[0][2], arr[1][2]);
    printf("%d, %d, %d\n",arr[1][0],arr[2][0], arr[2][1]);


    return 0;
}
