#include<stdio.h>
#include<stdlib.h> 
#include<fcntl.h> 
#include<unistd.h> 
#include<err.h> 

int compare(const void *a, const void *b) {

    return (*(int *)a - *(int *)b); 
}

void ex_1 () {

    int fd_in = open("numbers.bin", O_RDONLY); 
    printf("1\n"); 

    if (fd_in == -1) {
        errx(2, "Error with open()\n"); 
    }
    printf("2\n"); 

    int cnt = 0; 
    int read_flag = read(fd_in, &cnt, sizeof(int)); 
    if (read_flag == -1) {
        close(fd_in); 
        errx(3, "Error with read()\n"); 
    } 
    printf("%d", cnt); 

    int even = 0, odd = 0; 
    int *numbers = (int *)malloc(cnt * sizeof(int)); 

    for (size_t i = 0; i < cnt; i++) {
        read_flag = read(fd_in, &numbers[i], sizeof(int)); 
        if (read_flag == -1) { 
            free(numbers); 
            close(fd_in);
            errx(4, "Error with read()\n");
        } 
        (numbers[i] % 2 == 0) ? even++ : odd++; 
    }
    qsort(numbers, cnt, sizeof(int), compare); 

    close(fd_in); 

    int fd_out = open("numbers.txt", O_WRONLY | O_TRUNC | O_CREAT, 0644); 
    if (fd_out == -1) {
        free(numbers); 
        errx(5, "Error with open()\n"); 
    }

    int write_flag; 
    for (size_t i = 0; i < cnt; i++) {
        // write_flag = write(fd_out, &numbers[i], sizeof(int)); 
        // if (write_flag == -1) {
        //     close(fd_out); 
        //     errx(6, "Error with write()\n"); 
        // }
        if (dprintf(fd_out, "%d\n", numbers[i]) < 0) {
            close(fd_out);
            free(numbers);
            errx(6, "Error with dprintf()\n");
        }
    }
    free(numbers); 
    close(fd_out); 

    FILE *fptr = fopen("numbers2.txt", "w"); 
    if (fptr == NULL) {
        errx(7, "Error with fopen()\n");
    } 

    for (size_t i = 0; i < cnt; i++) {
        fprintf(fptr, "%d\n", numbers[i]);
    }

    fclose(fptr); 

}

int main (int argc, char *argv[]) {

    ex_1(); 

    return 0; 
}
