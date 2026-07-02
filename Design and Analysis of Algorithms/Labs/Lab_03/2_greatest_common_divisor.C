#include <stdio.h>
#include <stdlib.h>

int MIN(int first, int second)
{
    if (first < second) {return first;}
    else {return second;}
}

int first_GCD(int first, int second) // won't work for 0
{
    if (first == second) {return first;}
    else {return first_GCD(abs(first - second), MIN(first, second));}
}

int second_GCD(int first, int second) // works for 0
{
    if (first == 0) {return abs(second);} // first base case
    if (second == 0) {return abs(first);} // second base case
    return second_GCD(second, first % second);
}

void find_GCD()
{
    int first, second;
    printf("Enter two numbers: ");
    scanf("%d %d", &first, &second);
    printf("GCD: %d\n", first_GCD(first, second)); // test first approach
    printf("GCD: %d\n", second_GCD(first, second)); // test second approach
}
