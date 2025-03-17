#include <stdio.h>

int compare_strings(const char *str1, const char *str2) {
    while (*str1 != '\0' && *str2 != '\0') {
        if (*str1 != *str2) {
            return 0;
        }
        str1++;
        str2++;
    }

    // Ако двата низа са с различна дължина
    if (*str1 != *str2) {
        return 0;  // Връщаме 0 ако единият низ е по-кратък
    }

    return 1;  // Връщаме 1 ако низовете са идентични
}

int main() {
    const char *str1 = "Hello, World!";
    const char *str2 = "Hello, World!";
    const char *str3 = "Hello, C!";

    if (compare_strings(str1, str2)) {
        printf("Nizovete '%s' and '%s' are identical.\n", str1, str2);
    } else {
        printf("Nizovete '%s' and '%s' are not identical.\n", str1, str2);
    }

    if (compare_strings(str1, str3)) {
        printf("Nizovete '%s' and '%s' are identical.\n", str1, str3);
    } else {
        printf("Nizovete '%s' and '%s' are not identical.\n", str1, str3);
    }

    return 0;
}

