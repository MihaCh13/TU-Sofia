#include <stdio.h>
#include <stdlib.h>

int main()
{
    
    int arr[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

 
    int rotated[3][3];

  
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            rotated[j][2 - i] = arr[i][j]; 
        }
    }

    
    printf("The rotated matrix is:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", rotated[i][j]); 
        }
        printf("\n");
    }

    return 0;
}
