#include <stdio.h>
#include <ctype.h>  // isspace()

int word_count(const char *str) {
    int count = 0;
    int in_word = 0;

    while (*str != '\0') {
        if (!isspace(*str)) {
            if (!in_word) {
                count++;
                in_word = 1;
            }
        } else {
            in_word = 0;
        }
        str++;
    }

    return count;
}

int main() {
    const char *str = "Hello world!";
    int count = word_count(str);
    printf("Word count: %d\n", count);
    return 0;
}
