#include <stdio.h>
#include <stdlib.h>

void print_array(int array[], int size);
int* create_array(int* size);
void selection_sort(int array[], int size);

void call_selection_sort()
{
    int size;
    int* array = create_array(&size);

    printf("Array: ");
    print_array(array, size);

    selection_sort(array, size);

    printf("Sorted Array: ");
    print_array(array, size);

    free(array);
}

void selection_sort(int array[], int size)
{
    int MIN, MIN_index;

    for (int i = 0; i < size - 1; i++)
    {
        MIN = array[i];
        MIN_index = i;

        for (int j = i + 1; j < size; j++)
        {
            if (MIN > array[j])
            {
                MIN = array[j];
                MIN_index = j;
            }
        }

        array[MIN_index] = array[i];
        array[i] = MIN;
    }
}
