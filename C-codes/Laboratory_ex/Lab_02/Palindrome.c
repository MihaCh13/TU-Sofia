#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n;
    scanf("%d", &n);

    int pol = 0; // Инициализация на pol с 0

    int original_n = n; // Запазваме оригиналното число, за да го сравним по-късно

    while (n > 0) {
        int ostatuk = n % 10;  // Вземаме последната цифра
        n /= 10;                // Премахваме последната цифра от числото
        pol = pol * 10 + ostatuk; // Добавяме цифрата в новото число (полиндром)
    }

    if (original_n == pol) {
        printf("Chisloto e palindrom");
    } else {
        printf("Chisloto ne e palindrom");
    }

    return 0;
}
