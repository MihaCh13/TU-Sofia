#include <stdio.h>
#include <stdlib.h>

void print_array(int array[], int size);
int* create_array(int* size);
void merge(int array[], int temporay[], int left, int middle, int right);
void sort(int array[], int temporary[], int left, int right);
void merge_sort(int array[], int size);

void call_merge_sort()
{
    int size;
    int* array = create_array(&size);

    printf("Array: ");
    print_array(array, size);

    merge_sort(array, size);

    printf("Sorted Array: ");
    print_array(array, size);

    free(array);
}

void merge(int array[], int temporary[], int left, int middle, int right)
{
    int left_end = middle - 1;
    int element_count = right - left + 1;
    int temporary_position = left;

    while ((left <= left_end) && (middle <= right))
    {
        if (array[left] <= array[middle])
        {
            temporary[temporary_position] = array[left];
            temporary_position++;
            left++;
        }
        else
        {
            temporary[temporary_position] = array[middle];
            temporary_position++;
            middle++;
        }
    }
    while (left <= left_end)
    {
        temporary[temporary_position] = array[left];
        temporary_position++;
        left++;
    }
    while(middle <= right)
    {
        temporary[temporary_position] = array[middle];
        temporary_position++;
        middle++;
    }
    for (int i = 0; i <= element_count; i++)
    {
        array[right] = temporary[right];
        right--;
    }
}

void sort(int array[], int temporary[], int left, int right)
{
    int middle;
    if (right > left)
    {
        middle = (right + left)/2;
        sort(array, temporary, left, middle);
        sort(array, temporary, middle + 1, right);
        merge(array, temporary, left, middle + 1, right);
    }
}

void merge_sort(int array[], int size)
{
    int temporary[size];
    sort(array, temporary, 0, size - 1);
}
