#include <stdio.h>

int* create_array(int* size);

int search_element(int array[], int number, int index)
{
    if (index < 1) {return number == array[0];}

    return number == array[index - 1] || search_element(array, number, index - 1);
}

void call_search()
{
    int size;
    int* array = create_array(&size);

    int number;
    printf("Enter value to search for: ");
    scanf("%d", &number);

    printf("%d is ", number);

    if (search_element(array, number, size)) {printf("present in the array.\n");}
    else {printf("not present in the array.\n");}
}
