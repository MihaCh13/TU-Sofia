#include <stdio.h>

int* create_array(int* size);

int check_array(int array[], int size)
{
    int is_monotonically_decreasing;
    if (size == 1) {return 1;}
    if (array[size - 2] >= array[size - 1]) {is_monotonically_decreasing = 1;}
    else {is_monotonically_decreasing = 0;}

    return is_monotonically_decreasing && check_array(array, size - 1);
}

void call_monotonical_check()
{
    int size;
    int* array = create_array(&size);

    printf("The sequence is ");
    if (!check_array(array, size)) {printf("not ");}
    printf("monotonically decreasing.\n");
}
