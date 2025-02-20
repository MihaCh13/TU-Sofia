#include<stdio.h> 
#include<stdlib.h>

int strlen_t (char *string) {
    int length = 0, i = 0; 
    while (string[i] != '\0') {
        length++; 
        i++; 
    }
    return length; 
}

char *strcpy_t (char *string, char *new) {
    free(string);  

    string = malloc(strlen(new) + 1); 
    for (int i = 0; i < strlen_t(new); i++) {
        string[i] = new[i]; 
    }
    string[strlen_t(new)] = '\0';

    return string; 
}

char *to_upper (char *string) {
    char *new_str = malloc(strlen_t(string) + 1);
    int len = strlen_t(string); 

    for (int i = 0; i < len; i++) {
        if (string[i] >= 97 && string[i] <= 122) {
            new_str[i] = string[i] - 32;
        } else {
            new_str[i] = string[i];
        }
    }
    new_str[strlen_t(string)] = '\0'; 

    return new_str; 
} 

char *change_case (char *string) {
    char *new_str = malloc(strlen_t(string) + 1); 

    for (int i = 0; i < strlen_t(string); i++) {
        if (string[i] >= 97 && string[i] <= 122) {
            new_str[i] = string[i] - 32; 
        } else if (string[i] >= 65 && string[i] <= 90) {
            new_str[i] = string[i] + 32;
        } else {
            new_str[i] = string[i]; 
        }
    }
    new_str[strlen_t(string)] = '\0'; 

    return new_str; 
}

int cnt_upper (char *string) {
    int cnt = 0; 

    for (int i = 0; i < strlen_t(string); i++) {
        if (string[i] >= 65 && string[i] <= 90) {
            cnt++; 
        } else {
            continue; 
        }
    }

    return cnt; 
}

// AI corrected: 
int cnt_words(const char *string) {
    int cnt = 0;
    int in_word = 0;

    for (int i = 0; i < strlen_t(string); i++) {
        if (string[i] != ' ' && string[i] != '\t' && string[i] != '\n') {
            if (!in_word) {
                cnt++;
                in_word = 1;
            }
        } else {
            in_word = 0;
        }
    }
    return cnt;
}

int main (int argc, char *argv[]) {

    char *input = (char*)malloc(20*sizeof(char*)); 
    input = strcpy_t(input, "This is a test"); 

    char *upper_str = to_upper(input); 
    char *changed_case_str = change_case(input);
    printf("Length: %d\nWords count: %d\nUpper before: %d\nTo upper: %s\nUpper after: %d\nCase change: %s\n", 
    strlen_t(input), cnt_words(input), cnt_upper(input), upper_str, cnt_upper(input), changed_case_str);

    return 0; 
}
