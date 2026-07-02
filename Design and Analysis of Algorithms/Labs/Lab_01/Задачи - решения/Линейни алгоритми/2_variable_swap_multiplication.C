#include <stdio.h>

void swap_variables()
{
    // Declare variables:
    int a, b;
    // Enter their values:
    printf("Enter a & b: ");
    scanf("%d %d", &a, &b); // 3 4
    // Print the values:
    printf("a = %d; b = %d\n", a, b);

    a = a*b; // a = 3*4 = 12
    b = a/b; // b = 12/4 = 3
    a = a/b; // a = 12/3 = 4

    // Print the swapped variables:
    printf("a = %d; b = %d\n", a, b); // 4 3
}
