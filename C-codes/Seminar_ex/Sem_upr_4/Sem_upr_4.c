#include<stdio.h>
#include<stdlib.h>
#include<error.h>

int strlen_t (const char *str) {

    int len = 0, i = 0;
    while (str[i] != '\0') {
        len++;
        i++;
    }
    return len;

}

int strcmp_t (char *string1, char *string2) {

    int len_1 = strlen_t(string1);
    int len_2 = strlen_t(string2);

    if (len_1 < len_2) return -1;
    if (len_2 > len_1) return 1;
    for (int i = 0; i < len_1; i++) {
        if (string1[i] < string2[i]) return -1;
        if (string2[i] < string1[i]) return 1;
    }
    return 0;

}

void ex_8 () {

    int *arr = (int *)malloc(11*sizeof(int));
    if (arr == NULL) {
        perror("Allocation failed\n");
        return;
    }

    int cnt = 10, num = -1, index;
    char line[100];

    printf("Enter 10 numbers: \n");
    for (int i = 0; i < 10; i++) {
        scanf("%d", &arr[i]);
    }

    while (getchar() != '\n');

    while (1) {
        printf("Enter number and index /0 to quit/: \n");

        if (scanf("%d", &num) != 1) {
            printf("Invalid input! Please enter a valid number.\n");
            while (getchar() != '\n');
            continue;
        }

        if (num == 0) {
            break;
        }

        if (scanf("%d", &index) != 1) {
            printf("Invalid input! Please enter a valid index.\n");
            while (getchar() != '\n');
            continue;
        }

        if (index < 0 || index > cnt) {
            printf("Invalid index!\n");
            continue;
        }
        arr = realloc(arr, (cnt + 1)*sizeof(int));
        if (arr == NULL) {
            perror("Allocation failed\n");
            free(arr);
            return;
        }

        for (int i = cnt; i > index; i--) {
            arr[i] = arr[i - 1];
        }
        arr[index] = num;
        cnt++;
    }

    for (int i = 0; i < cnt; i++) printf("%d ", *(arr+i)); printf("\n");

    free(arr);

}

int compare (const void *a, const void *b) {

    return (*(int *)a - *(int *)b);

}

void ex_5 () {

    char *command = (char *)malloc(10*sizeof(char));
    if (command == NULL) {
        perror("Allocation failed\n");
        return;
    }

    int x, idx = 0, deleted = 0;
    int *arr = (int *)malloc(sizeof(int));
    if (arr == NULL) {
        perror("Allocation failed\n");
        return;
    }


    while (1) {
        printf("Command: \n");

        scanf("%s", command);

        if ((strcmp_t(command, "add") != 0) && (strcmp_t(command, "delete") != 0) && (strcmp_t(command, "smallest") != 0)) {
            printf("Wrong command, exitting.....");
            free(arr);
            free(command);
            return;
        }
        scanf("%d", &x);

        if ((strcmp_t(command, "add")) == 0) {
            arr = realloc(arr, (idx + 1)*sizeof(int));
            if (arr == NULL) {
                perror("Allocation failed\n");
                free(arr);
                free(command);
                return;
            }

            arr[idx] = x;
            idx++;
        }

        if ((strcmp_t(command, "delete")) == 0) {
            deleted = 0;
            for (int i = 0; i < idx; i++) {
                if (arr[i] == x) {
                    deleted++;
                    for (int j = i; j < idx - 1; j++) {
                        arr[j] = arr[j + 1];
                    }
                    idx--;
                }
            }

            if (deleted > 0) {
                arr = realloc(arr, idx * sizeof(int));
                if (arr == NULL) {
                    perror("Reallocation failed\n");
                    free(command);
                    return;
                }
            }
        }

        if ((strcmp_t(command, "smallest")) == 0) {
            qsort(arr, idx, sizeof(int), compare);
            printf("Smallest x-th currently is: %d", *(arr+x));
        }
    }

    free(command);
    free(arr);

}

int main () {

    ex_5();

    return 0;
}
