#include <stdio.h>

int iterative_factorial(int number)
{
    if (number == 0) {return 1;}

    int factorial = 1; // starting point
    for (int i = 1; i <= number; i++) {factorial = factorial*i;} // 1*2*3*4*5
    return factorial; // 120
}

int recursive_factorial(int number)
{
    if (number <= 1) {return 1;}
    else {return number*recursive_factorial(number - 1);} // 5*4*3*2*1 = 120
}

void call_factorial()
{
    int number;
    printf("Enter an integer: ");
    scanf("%d", &number);
    // We call the two factorial methods:
    printf("number! = %d = %d\n", iterative_factorial(number), recursive_factorial(number));
}
