#include <stdio.h>

void find_MAX_number()
{
    // Declare variables for the three numbers:
    int a, b, c;
    // Declare a variable to store the biggest value:
    int MAX;
    // Enter values:
    printf("Enter three integers: ");
    scanf("%d %d %d", &a, &b, &c); // 2 1 3

    // Comparison:
    if (a > b) {MAX = a;} // since 2 > 1, MAX = 2
    else {MAX = b;}
    if (c > MAX) {MAX = c;} // since 3 > 2, MAX = 3

    // Print the biggest value:
    printf("MAX: %d.\n", MAX); // 3
}
