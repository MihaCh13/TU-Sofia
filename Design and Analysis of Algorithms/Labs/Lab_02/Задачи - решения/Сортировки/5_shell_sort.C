#include <stdio.h>
#include <stdlib.h>

void print_array(int array[], int size);
int* create_array(int* size);
void first_shell_sort(int array[], int size);
void second_shell_sort(int array[], int size);

void call_shell_sort()
{
    int size;
    int* array = create_array(&size);

    printf("Array: ");
    print_array(array, size);

 // first_shell_sort(array, size);
 // second_shell_sort(array, size);

    printf("Sorted Array: ");
    print_array(array, size);

    free(array);
}

void first_shell_sort(int array[], int size)
{
    int interval = size - 1, temporary;

    while (interval > 0)
    {
        for (int i = 0; i < size; i++)
        {
            int j = i;
            temporary = array[i];
            while ((j >= interval) && (array[j - interval] > temporary))
            {
                array[j] = array[j - interval];
                j -= interval;
            }
            array[j] = temporary;
        }

        if (interval/2 != 0) {interval /= 2;}
        else if (interval == 1) {interval = 0;}
        else {interval = 1;}
    }
}

void second_shell_sort(int array[], int size)
{
    int temporary;
    for (int interval = size/2; interval > 0; interval /= 2)
    {
        for (int i = interval; i < size; i ++)
        {
            temporary = array[i];
            int j;
            for (j = i; j >= interval && array[j - interval] > temporary; j -= interval)
            {array[j] = array[j - interval];}

            array[j] = temporary;
        }
    }
}
