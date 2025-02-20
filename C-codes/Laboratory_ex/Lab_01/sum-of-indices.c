#include <stdio.h>
#include <stdlib.h>

int main()
{
    int x;
    scanf("%d", &x);
    int y = x%10;
    x = x/10;
    int z = x%10;
    x = x/10;
    int t = x%10;
    x = x/10;
    int suma = x + y + z + t;
    printf("%d", suma);

    return 0;
}
