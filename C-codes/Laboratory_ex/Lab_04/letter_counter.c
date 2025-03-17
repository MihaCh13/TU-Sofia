#include <stdio.h>
#include <ctype.h>  // За функцията tolower()

#define ALPHABET_SIZE 26  // Броят на буквите в английската азбука

void count_letters(const char *str) {
    int count[ALPHABET_SIZE] = {0};  // Масив за броене на всяка буква (A-Z или a-z)

    while (*str != '\0') {
        // Преобразуваме символа към малка буква, ако е необходимо (за да игнорираме големи и малки букви)
        char ch = tolower(*str);

        // Проверяваме дали символът е буква (a-z)
        if (ch >= 'a' && ch <= 'z') {
            count[ch - 'a']++;  // Увеличаваме броя на съответната буква
        }

        str++;  // Преминаваме към следващия символ в низа
    }

    printf("letter count:\n");
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (count[i] > 0) {
            printf("We can see the letter '%c', times: %d \n", i + 'a', count[i]);
        }
    }
}

int main() {
    const char *str = "Hello world!";

    count_letters(str);  // Извикваме функцията за броене на буквите

    return 0;
}
