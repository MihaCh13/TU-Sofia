/*
    Compiled under $gcc -g --pedantic --std=c11 files.c -o files 
    Works with both .txt and .bin files 
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h> 

void copy_file(char *in, char *out) {

    int fd_input = open(in, O_RDONLY); 
    if (fd_input == -1) {
        perror("Can't access file\n"); 
        return; 
    } 
    int fd_output = open(out, O_WRONLY | O_TRUNC); 
    if (fd_output == -1) {
        perror("Can't access file\n"); 
        close(fd_input); 
        return; 
    } 
    int size = lseek(fd_input, 0, SEEK_END); 
    if (size == -1) {
        perror("Error with lseek\n");
        close(fd_input); 
        close(fd_output); 
        return; 
    }
    char buff[size];
    int size2 = lseek(fd_input, 0, SEEK_SET); 
    if (size2 == -1) {
        perror("Error with lseek\n");
        close(fd_input); 
        close(fd_output); 
        return; 
    }

    int res = read(fd_input, buff, size); 
    if (res == -1) {
        perror("Error with read\n"); 
        close(fd_input); 
        close(fd_output); 
        return; 
    }

    res = write(fd_output, buff, size); 
    if (res == -1) {
        perror("Error with write\n"); 
        close(fd_input); 
        close(fd_output); 
        return; 
    }

}

void copy_file_withot (char *in, char *out, char ch) {

    int fd_input = open(in, O_RDONLY); 
    if (fd_input == -1) {
        perror("Can't access file\n"); 
        return; 
    } 
    int fd_output = open(out, O_WRONLY | O_TRUNC); 
    if (fd_output == -1) {
        close(fd_input); 
        perror("Can't access file\n"); 
        return; 
    } 
    int size = lseek(fd_input, 0, SEEK_END); 
    if (size == -1) {
        perror("Error with lseek\n");
        close(fd_input); 
        close(fd_output); 
        return; 
    }
    char buff[size+1];
    int size2 = lseek(fd_input, 0, SEEK_SET); 
    if (size2 == -1) {
        perror("Error with lseek\n");
        close(fd_input); 
        close(fd_output); 
        return; 
    }

    int res = read(fd_input, buff, size); 
    if (res == -1) {
        perror("Error with read\n"); 
        close(fd_input); 
        close(fd_output); 
        return; 
    }
    size2 = size; 

    for (size_t i = 0; i < size; i++) {
        if (*(buff+i) == ch) {
            size2--; 
            for (size_t j = i; j < size; j++) {
                *(buff+j) = *(buff+j+1); 
            }
        }
    }

    res = write(fd_output, buff, size2); 
    if (res == -1) {
        perror("Error with write\n"); 
        close(fd_input); 
        close(fd_output); 
        return; 
    }
    close(fd_input); 
    close(fd_output); 

}

void change_file (char *file, char ch) {

    int fd = open(file, O_RDONLY); 
    if (fd == -1) {
        perror("Can't access file\n"); 
        return; 
    } 

    int size = lseek(fd, 0, SEEK_END); 
    if (size == -1) {
        perror("Error with lseek\n"); 
        return; 
    }
    char buff[size+1];
    int size2 = lseek(fd, 0, SEEK_SET); 
    if (size2 == -1) {
        perror("Error with lseek\n"); 
        return; 
    }

    int res = read(fd, buff, size); 
    if (res == -1) {
        perror("Error with read\n"); 
        return; 
    }
    for (size_t i = 0; i < size; i++) {
        if (*(buff+i) == ch && (ch >= 97 && ch <= 122)) *(buff + i) -= 32; 
    }
    close(fd); 
    fd = open(file, O_WRONLY | O_TRUNC); 
    if (fd == -1) {
        perror("Can't access file\n"); 
        return; 
    } 

    res = write(fd, buff, size); 
    if (res == -1) {
        perror("Error with write\n"); 
        return; 
    }

}

int main () {

    copy_file("input.bin", "output.bin"); 
    change_file("output.bin", 't'); 

    return 0; 
}
