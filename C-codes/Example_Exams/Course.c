/* 
   This code successfully compiles under the following command:
   $ gcc -g --pedantic --std=c11 Course.c -o out
*/

#include<stdio.h> 
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>

#define INPUT_FILE "courses.bin" 
#define OUTPUT_FILE "offers.txt"

struct Course {
    char name[50]; 
    char start_date[11]; // YYYY:MM:DD 
    int total_lectures; 
    float price; 
};

int strlen_t (const char *string) {
    int length = 0, i = 0; 
    while (string[i] != '\0') {
        length++; 
        i++; 
    }
    return length; 
}

void strcpy_t (char *dest, const char *src) {
    int len = strlen_t(src);
    for (int i = 0; i < len; i++) {
        dest[i] = src[i]; 
    }
    dest[len] = '\0'; 
}


int strcmp_t (char *string1, char *string2) {

    int len_1 = strlen_t(string1); 
    int len_2 = strlen_t(string2); 

    if (len_1 < len_2) return -1; 
    if (len_1 > len_2) return 1; 
    for (int i = 0; i < len_1; i++) {
        if (string1[i] < string2[i]) return -1; 
        if (string1[i] > string2[i]) return 1; 
    }
    return 0; 

}

void *memset_t(void *ptr, int value, size_t num) {

    unsigned char *p = (unsigned char *)ptr;  
    for (size_t i = 0; i < num; i++) {
        p[i] = (unsigned char)value;  
    }
    return ptr;  

}


void discount (struct Course *courses, int n, int index) {

    if (index > n - 1) {
        printf("Index out of bounds\n"); 
        return; 
    }

    for (size_t i = 0; i < n; i++) {
        if (i == index) {
            courses[i].price -= 0.1 * courses[i].price; 

            printf("%.2f lv. - %s - %s\n", courses[i].price, courses[i].name, courses[i].start_date);
        } 
    }

    printf("Couldn't find such a course!\n"); 
    return; 
}

void courses_in_diapason (struct Course *courses, int n, float start_price, float end_price) {
    
    int fd = open(OUTPUT_FILE, O_WRONLY | O_CREAT | O_TRUNC); 
    if (fd == -1) {
        printf("Error opening file\n");
        return;
    } 

    char buffer[100]; 

    for (size_t i = 0; i < n; i++) {
        if (courses[i].price >= start_price && courses[i].price <= end_price) {
            write(fd, courses[i].name, strlen_t(courses[i].name)); 
            write(fd, "\n", 1); 

            write(fd, courses[i].start_date, 12); 
            write(fd, "\n", 1);

            memset_t(buffer, 0, sizeof(buffer));  // Clear buffer before use
            int len = snprintf(buffer, sizeof(buffer), "%d lectures\n", courses[i].total_lectures);
            write(fd, buffer, len);

            memset_t(buffer, 0, sizeof(buffer));  // Clear buffer again
            len = snprintf(buffer, sizeof(buffer), "%.2f\n", courses[i].price);
            write(fd, buffer, len);
        }
    }

}

struct Course *delete_course (struct Course *courses, int *n, char *name, char *start_date) {

    for (size_t i = 0; i < *n; i++) {
        if (strcmp_t(courses[i].name, name) == 0 && strcmp_t(courses[i].start_date, start_date)) {
            for (size_t j = i; j < *n - 1; j++) {
                courses[j] = courses[j + 1];
            }
            
            (*n)--;
            courses = realloc(courses, (*n) * sizeof(struct Course));

            if (*n > 0 && courses == NULL) {
                printf("Memory reallocation failed!\n");
                return NULL; 
            }

            return courses;
        }
    }
    return NULL; 

}

int main () {

    struct Course *courses = (struct Course *)malloc(100 * sizeof(struct Course)); 

    int fd = open(INPUT_FILE, O_RDONLY); 
    if (fd == -1) {
        printf("Error opening file\n");
        return 1;
    }

    int i = 0; 

    struct Course course; 

    while (read(fd, &course, sizeof(struct Course)) == sizeof(struct Course)) {  
        if (i >= 100) break; 
        
        strcpy_t(courses[i].name, course.name); 
        strcpy_t(courses[i].start_date, course.start_date); 
        courses[i].total_lectures = course.total_lectures; 
        courses[i].price = course.price; 

        i++;
    }

    close(fd); 
    free(courses); 

    return 0; 
}
