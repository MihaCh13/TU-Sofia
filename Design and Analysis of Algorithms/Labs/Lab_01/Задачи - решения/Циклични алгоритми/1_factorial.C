#include <stdio.h>

void calculate_factorial()
{
    // Declare variables:
    int number, factorial = 1; // starts with one (starting point)
    // Enter the number:
    printf("Enter a positive integer: ");
    scanf("%d", &number); // 5

    for (int i = 1; i <= number; i++) {factorial *= i;}
    // Iterations:
    // 1. factorial = 1*1 = 1
    // 2. factorial = 1*2 = 2
    // 3. factorial = 2*3 = 6
    // 4. factorial = 6*4 = 24
    // 5. factorial = 24*5 = 120
    printf("%d! = %d\n", number, factorial); // 5! = 120
}
