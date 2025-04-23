#include<stdio.h>
#include<stdlib.h> 
#include<fcntl.h> 
#include<unistd.h> 
#include<err.h> 

int main() {

    int fd = open("numbers.bin", O_WRONLY | O_CREAT | O_TRUNC, 0644); 

    int cnt = 10; 
    int numbers[] = {5, 6, 12, 3, 21, 36, 46, 1213, 312, 13}; 

    if (write(fd, &cnt, sizeof(int)) == -1) {
        close(fd); 
        errx(1, "Error writing to file");
    } 

    for (size_t i = 0; i < cnt; i++) {
        if (write(fd, &numbers[i], sizeof(int)) == -1) {
            close(fd); 
            errx(1, "Error writing to file");
        } 
    }

    close(fd); 

    return 0; 
}
