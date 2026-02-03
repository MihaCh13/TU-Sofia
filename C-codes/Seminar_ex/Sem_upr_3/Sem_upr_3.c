#include<stdio.h>
#include<stdlib.h>
#include<error.h>

void ex_1 (int *arr, int n, int *start, int *length) {

    int max_len = 0, max_idx = 0, curr_len = 0, curr_start = 1;

    for (int i = 1; i < n; i++) {
        if (arr[i] == arr[i - 1]) {
            curr_len++;
        } else {
            if (curr_len > max_len) {
                max_len = curr_len;
                max_idx = curr_start;
            }
            curr_len = 1;
            curr_start = i;
        }
    }
    if (curr_len > max_len) {
        max_len = curr_len;
        max_idx = curr_start;
    }
    *start = max_idx;
    *length = max_idx;

}

void wrapper_ex_1 () {

    int n = 1;
    printf("Enter array size /0-50/: ");
    scanf("%d", &n);
    if (n < 1 || n > 50) {
        printf("Please follow size guidance: ");
        scanf("%d", &n);
    }
    int arr[n];
    for (int i = 0; i < n; i++) {
        printf("Enter a number: ");
        scanf("%d", &arr[i]);
    }
    int start, length;
    ex_1(arr, n, &start, &length);
    printf("The longest sequence of equivalent numbers start at [%d] and is [%d] numbers long\n", start, length);

}

int compare (const void *a, const void *b) {

    return (*(int *)b - *(int *)a);

}

int ex_5 (int *arr, int n, int k) {

    qsort (arr, n, sizeof(int), compare);
    return arr[k - 1];

}

void wrapper_ex_5 () {

    int n = 1;
    printf("Enter array size /0-50/: ");
    scanf("%d", &n);
    if (n < 1 || n > 50) {
        printf("Please follow size guidance: ");
        scanf("%d", &n);
    }
    int arr[n];
    for (int i = 0; i < n; i++) {
        printf("Enter a number: ");
        scanf("%d", &arr[i]);
    }

    int k;
    printf("Enter k: ");
    scanf("%d", &k);
    if (k > n) {
        perror("k is bigger than size\n");
        return;
    }

    printf("k-th biggest is %d\n", ex_5(arr, n, k));

}

void ex_8 () {

    int arr[20], cnt = 0, num, index;
    char line[100];

    printf("Enter count of numbers: ");
    scanf("%d", &cnt);
    if (cnt > 20) {
        printf("Size too big\n");
        return 0;
    }

    printf("Enter numbers: \n");
    for (int i = 0; i < cnt; i++) {
        scanf("%d", &arr[i]);
    }

    while (getchar() != '\n');

    while (cnt < 20) {
        printf("Enter number and index /0 to quit/: \n");
        //scanf("%[^?{2}]d", &num, &index);
        //scanf("%d %d", &num, &index);

        if (scanf("%d", &num) != 1) {
            printf("Invalid input! Please enter a valid number.\n");
            // Clear input buffer if invalid input is entered
            while (getchar() != '\n');
            continue;
        }

        // Exit the loop if num is 0
        if (num == 0) {
            break;
        }

        // Read the index only if num is not 0
        if (scanf("%d", &index) != 1) {
            printf("Invalid input! Please enter a valid index.\n");
            // Clear input buffer if index is invalid
            while (getchar() != '\n');
            continue;
        }

        // Ensure the index is valid
        if (index < 0 || index > cnt) {
            printf("Invalid index!\n");
            continue;
        }

        for (int i = cnt; i > index; i--) {
            arr[i] = arr[i - 1];
        }
        arr[index] = num;
        cnt++;
    }
    for (int i = 0; i < cnt; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

}

int main() {

    //wrapper_ex_1();
    //wrapper_ex_5();
    ex_8();

    return 0;
}
