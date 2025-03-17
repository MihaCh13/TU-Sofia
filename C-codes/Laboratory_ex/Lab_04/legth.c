#include <stdio.h>

int string_length(const char *str)
    {
    int length = 0;

    while (str[length] != '\0')
        {
        length++;
    }

    return length;
}

int main()
 {
    const char *str = "Hello, World!";
    int len = string_length(str);
    printf("The length: %d\n", len);
    return 0;
}
