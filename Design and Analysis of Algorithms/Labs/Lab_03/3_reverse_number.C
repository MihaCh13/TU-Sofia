#include <stdio.h>

void reverse(int number)
{
    if (number < 10) {printf("%d", number);}
    else
    {
        printf("%d", number%10);
        reverse(number/10);
    }
}

void call_reverse()
{
    int number;
    printf("Enter number: ");
    scanf("%d", &number);
    reverse(number);
}
