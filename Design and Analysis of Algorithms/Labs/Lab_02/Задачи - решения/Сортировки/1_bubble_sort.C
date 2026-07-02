#include <stdio.h>
#include <stdlib.h>

void print_array(int array[], int size);
int* create_array(int* size);
void first_bubble_sort(int array[], int size);
void second_bubble_sort(int array[], int size);

void call_bubble_sort()
{
    int size;
    int* array = create_array(&size);

    printf("Array: ");
    print_array(array, size);


    //first_bubble_sort(array, size);
    //second_bubble_sort(array, size);

    printf("Sorted Array: ");
    print_array(array, size);

    free(array);
}

void print_array(int array[], int size)
{
    for (int i = 0; i < size; i++) {printf("%d ", array[i]);}
    printf("\n");
}

int* create_array(int* size)
{
    printf("Enter array size: ");
    scanf("%d", size);

    int* array = (int*) malloc(*size*sizeof(int));
    if (array == NULL)
    {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(1);
    }

    printf("Enter array elements:\n");
    for (int i = 0; i < *size; i++)
    {
        printf("array[%d] = ", i);
        scanf("%d", &array[i]);
    }

    return array;
}

void first_bubble_sort(int array[], int size)
{
    int temporary;

    for (int i = size - 1; i >= 0; i--)
    {
        for (int j = 1; j <= i; j++)
        {
            if (array[j - 1] > array[j])
            {
                temporary = array[j - 1];
                array[j - 1] = array[j];
                array[j] = temporary;
            }
        }
    }
}

void second_bubble_sort(int array[], int size)
{
    int temporary;

    for (int i = 0; i < size - 1; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            if (array[i] > array[j])
            {
                temporary = array[i];
                array[i] = array[j];
                array[j] = temporary;
            }
        }
    }
}
