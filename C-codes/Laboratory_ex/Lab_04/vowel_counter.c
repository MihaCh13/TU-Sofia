#include <stdio.h>
#include <ctype.h>  // За функцията tolower()


int count_vowels(const char *str) {
    int count = 0;
    char ch;

    while (*str != '\0') {
        ch = tolower(*str);  // Преобразуваме символа към малка буква, за да игнорираме големи/малки букви

        if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u') {
            count++;
        }

        str++;
    }

    return count;
}

int main() {
    const char *str = "Hello world!";

    int vowel_count = count_vowels(str);
    printf("The count of vowels in '%s': %d\n", str, vowel_count);

    return 0;
}
