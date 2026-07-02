#include <stdio.h>

void process_array()
{
    // Declare the size & the number we're looking for:
    int size, negative_number;
    // Enter the array's size:
    printf("Enter array size: ");
    scanf("%d", &size);
    // Enter the number we're looking for:
    printf("Enter negative number: ");
    scanf("%d", &negative_number);

    // Declare array:
    int array[size];
    // Declare variables for different purposes:
    int MAX, odd_count = 0, present_negative = 0, sum = 0;
    float average;

    // Enter array elements:
    for (int i = 0; i < size; i++)
    {
        printf("array[%d] = ", i);
        scanf("%d", &array[i]);
    }

    // Print the array:
    printf("Array: ");
    for (int i = 0; i < size; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");

    // Initialize the biggest element as the first one:
    MAX = array[0];

    for (int i = 0; i < size; i++)
    {
        // If we find a bigger element, we take its value:
        if (array[i] > MAX) {MAX = array[i];}
        // Add the element to the sum:
        sum += array[i];
        // Count the odd elements:
        if (array[i]%2 != 0) {odd_count++;}
        // Check if this is the number we're looking for (set the flag):
        if (array[i] < 0) {if (array[i] == negative_number) {present_negative = 1;}}
    }

    // Print the biggest element:
    printf("MAX element: %d.\n", MAX);
    // Calculate the average value (since we know the total sum & size):
    average = (float)(sum/size);
    // Print the average value:
    printf("Average Value: %.2f.\n", average);
    // Print the odd number count:
    printf("Odd Number Count: %d.\n", odd_count);
    // Print if we have found the number:
    printf("Is %d present? ", negative_number);
    // An alternative to "if-else" (ternary operator):
    (present_negative) ? printf("Yes.") : printf("No.");
}
