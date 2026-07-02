#include <stdio.h>
#include <stdlib.h>

void print_array(int array[], int size);
int* create_array(int* size);
void sift_down(int array[], int root, int bottom);
void heap_sort(int array[], int size);

void call_heap_sort()
{
    int size;
    int* array = create_array(&size);

    printf("Array: ");
    print_array(array, size);

    heap_sort(array, size);

    printf("Sorted Array: ");
    print_array(array, size);

    free(array);
}

void sift_down(int array[], int root, int bottom)
{
    int done = 0, MAX_child, temporary;

    while ((root*2 <= bottom) && !done)
    {
        if (root*2 == bottom) {MAX_child = root*2;}
        else if (array[root*2] > array[root*2 + 1]) {MAX_child = root*2;}
        else {MAX_child = root*2 + 1;}

        if (array[root] < array[MAX_child])
        {
            temporary = array[root];
            array[root] = array[MAX_child];
            array[MAX_child] = temporary;
            root = MAX_child;
        } else {done = 1;}
    }
}

void heap_sort(int array[], int size)
{
    int temporary;
    for (int i = size/2 - 1; i >= 0; i--) {sift_down(array, i, size);}

    for (int i = size - 1; i >= 1; i--)
    {
        temporary = array[0];
        array[0] = array[i];
        array[i] = temporary;
        sift_down(array, 0, i - 1);
    }
}
