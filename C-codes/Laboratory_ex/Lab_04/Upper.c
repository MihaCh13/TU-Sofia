#include <stdio.h>
#include <ctype.h>  // За функцията toupper()


void to_uppercase(char *str) {
    while (*str != '\0') {
        *str = toupper(*str);
        str++;
    }
}

int main() {
    char str[] = "Hello World!";

    to_uppercase(str);
    printf("Upper niz: %s\n", str);

    return 0;
}
