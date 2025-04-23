#include<stdio.h>
#include<stdlib.h> 
#include<fcntl.h> 
#include<unistd.h> 
#include<err.h> 
#include<time.h>

int isspace_t(char c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r';
}

int strlen_t (char *string) {
    int length = 0, i = 0; 
    while (string[i] != '\0') {
        length++; 
        i++; 
    }
    return length; 
}

char *strcpy_t(char *string, const char *new) {
    int i = 0;
    while (new[i] != '\0') {
        string[i] = new[i];
        i++;
    }
    string[i] = '\0';
    return string;
}

void ex_3() {

    int fd = open("input.txt", O_RDONLY); 
    if (fd == -1) errx(1, "Problem with open()"); 

    char last_letter; 

    int size = lseek(fd, 0, SEEK_END); 
    if (size == -1) {
        close(fd); 
        errx(2, "Problem with lseek()"); 
    }

    int lseek_flag = lseek(fd, 0, SEEK_SET); 
    if (lseek_flag == -1) {
        close(fd); 
        errx(3, "Problem with lseek()"); 
    }

    char *arr = (char *)malloc((size+1) * sizeof(char)); 
    if (arr == NULL) {
        close(fd); 
        errx(4, "Problem with malloc() for arr"); 
    }

    int read_flag = read(fd, arr, size); 
    if (read_flag == -1) {
        free(arr); 
        close(fd); 
        errx(5, "Problem with read()"); 
    }

    arr[size] = '\0'; 
    close(fd); 

    // printf("%s", arr); 

    char *matched = malloc(size + 1); 
    if (!matched) {
        free(arr);
        errx(6, "Problem with malloc() for matched");
    }

    int match_index = 0;
    int i = 0;
    last_letter = '\0';

    while (arr[i] != '\0') {
        while (isspace_t(arr[i])) i++;

        int start = i;
        while (arr[i] && !isspace_t(arr[i])) i++;
        int end = i;

        if (start == end) break;

        char first = arr[start];
        char last = arr[end - 1];

        if (last_letter == '\0' || first == last_letter) {
            for (int j = start; j < end; j++) {
                matched[match_index++] = arr[j];
            }
            matched[match_index++] = '\0'; 
            last_letter = last;
        }
    }

    fd = open("output.txt", O_WRONLY | O_TRUNC | O_CREAT, 0644); 
    if (fd == -1) {
        free(arr); 
        free(matched); 
        errx(7, "Problem with open()"); 
    }

    int written = 0;
    for (int j = 0; j < match_index; ) {
        int print_flag = dprintf(fd, "%s ", &matched[j]); 
        if (print_flag < 0) {
            free(arr); 
            free(matched); 
            close(fd); 
            errx(8, "Problem with dprintf()"); 
        }   
        while (matched[j] != '\0') j++; 
        j++; 
    }

    free(arr); 
    free(matched); 
    close(fd); 

}

void get_random_word(char *result, int max_len) {
    int fd = open("dict.txt", O_RDONLY);
    if (fd == -1) errx(1, "Problem with open()");

    int size = lseek(fd, 0, SEEK_END);
    if (size == -1) {
        close(fd);
        errx(2, "Problem with lseek()");
    }

    if (lseek(fd, 0, SEEK_SET) == -1) {
        close(fd);
        errx(3, "Problem with lseek()");
    }

    char *buffer = (char *)malloc(size + 1);
    if (buffer == NULL) {
        close(fd);
        errx(4, "Problem with malloc()");
    }

    int read_flag = read(fd, buffer, size); 
    if (read_flag == -1) {
        free(buffer);
        close(fd);
        errx(5, "Problem with read()");
    }

    buffer[size] = '\0';
    close(fd);

    int word_count = 0;
    for (int i = 0; i < size; i++) {
        if (buffer[i] == '\n') word_count++;
    }

    if (word_count == 0) {
        free(buffer);
        errx(6, "No words in given file");
    }

    srand(time(NULL));
    int target_line = rand() % word_count;

    int current_line = 0;
    int i = 0, j = 0;
    while (buffer[i] != '\0') {
        if (current_line == target_line) {
            while (buffer[i] != '\n' && buffer[i] != '\0' && j < max_len - 1) {
                result[j++] = buffer[i++];
            }
            break;
        }

        if (buffer[i] == '\n') current_line++;
        i++;
    }

    result[j] = '\0';
    free(buffer);
}

void choose_word(char *dest, int difficulty) {
    if (difficulty == 1) {
        strcpy_t(dest, "computer");
    } else {
        get_random_word(dest, 26);
    }
}

int already_guessed(char guess, char *guessed_letters, int count) {
    for (int i = 0; i < count; i++) {
        if (guessed_letters[i] == guess) return 1;
    }
    return 0;
}

int letter_in_word(char guess, char *word) {
    for (int i = 0; word[i]; i++) {
        if (word[i] == guess) return 1;
    }
    return 0;
}

int print_word_state(char *word, char *guessed_letters, int guessed_cnt) {
    int all_guessed = 1;
    printf("\nWord: ");
    for (int i = 0; word[i]; i++) {
        int found = 0;
        for (int j = 0; j < guessed_cnt; j++) {
            if (word[i] == guessed_letters[j]) {
                found = 1;
                break;
            }
        }
        if (found) {
            printf("%c", word[i]);
        } else {
            printf("_");
            all_guessed = 0;
        }
    }
    return all_guessed;
}

void ex_5(int difficulty) {

    char searched_word[26];
    choose_word(searched_word, difficulty); 

    char guessed_letters[26]; 

    int found_word = 0, guessed_cnt = 0, len = strlen_t(searched_word), attempts = len - 2, won = 0; 

    while(attempts > 0) {
        if (print_word_state(searched_word, guessed_letters, guessed_cnt)) {
            won = 1;
            break;
        }

        printf("\nAttempts left: %d", attempts);
        printf("\nGuess a letter: ");

        char guess;
        scanf(" %c", &guess); // space before %c skips newline

        if (already_guessed(guess, guessed_letters, guessed_cnt)) {
            printf("You already guessed '%c'. Try something else!\n", guess);
            continue;
        }

        guessed_letters[guessed_cnt++] = guess;

        if (letter_in_word(guess, searched_word)) {
            printf("Correct guess! Yay\n");
        } else {
            printf("Incorrect guess. Try again!\n");
            attempts--;
        }
    }

    if (won) {
        printf("\nCongratulations! You guessed the word: %s\n", searched_word);
    } else {
        printf("\nYou lost! The word was: %s\n", searched_word);
    }

}

void wrapper_ex_5() {

    int difficulty = 0;

    printf("1 - Easy (fixed word)\n");
    printf("2 - Hard (random word from file)\n");

    while (difficulty != 1 && difficulty != 2) {
        printf("Enter difficulty (1 or 2): ");
        scanf("%d", &difficulty); 
    }

    ex_5(difficulty);

}


void run_menu() {

    printf("Choose between ex_3 and ex_5 using 3 or 5: "); 
    int op; 
    scanf("%d", &op); 
    switch(op) {
        case 3: 
        ex_3(); 
        break; 
        case 5: 
        wrapper_ex_5(); 
        break; 
        default: 
        printf("Incorrect choice, terminating....."); 
    }

}

int main (int argc, char *argv[]) {

    run_menu(); 

    return 0; 
}
