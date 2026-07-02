#include <stdio.h>

void check_leap_year()
{
    int year;
    printf("Enter Year: ");
    scanf("%d", &year);

    if ((year%4 == 0) && (year % 100 != 0) || (year % 400 == 0))
    {printf("Yes, leap year!\n");}
    else {printf("No leap year!\n");}
}
