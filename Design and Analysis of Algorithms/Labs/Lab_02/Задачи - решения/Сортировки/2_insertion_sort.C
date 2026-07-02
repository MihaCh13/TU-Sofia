#include <stdio.h>
#include <stdlib.h>

void print_array(int array[], int size);
int* create_array(int* size);
void insertion_sort(int array[], int size);

void call_insertion_sort()
{
    int size;
    int* array = create_array(&size);

    printf("Array: ");
    print_array(array, size);

    insertion_sort(array, size);

    printf("Sorted Array: ");
    print_array(array, size);

    free(array);
}

void insertion_sort(int array[], int size)
{
    for (int i = 1; i < size; i++)
    {
        int key = array[i];
        int j = i;
        while((j > 0) && (array[j - 1] > key))
        {
            array[j] = array[j - 1];
            j--;
        }
        array[j] = key;
    }
}

