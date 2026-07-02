#include <stdio.h>
#include <stdlib.h>

void print_array(int array[], int size);
int* create_array(int* size);
void quick_sort(int array[], int low, int high);

void call_quick_sort()
{
    int size;
    int* array = create_array(&size);

    printf("Array: ");
    print_array(array, size);

    quick_sort(array, 0, size - 1);

    printf("Sorted Array: ");
    print_array(array, size);

    free(array);
}

void quick_sort(int array[], int low, int high)
{
    int i = low, j = high, temporary;
    int x = array[(low + high)/2];

    do
    {
        while (array[i] < x) {i++;}
        while (array[j] > x) {j--;}

        if (i <= j)
        {
            temporary = array[i];
            array[i] = array[j];
            array[j] = temporary;
            i++; j--;
        }
    } while (i <= j);

    if (low < j) {quick_sort(array, low, j);} // left part
    if (i < high) {quick_sort(array, i, high);} // right part
}
