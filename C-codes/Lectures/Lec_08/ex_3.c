#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 50
#define MAX_CLASSES 5


typedef struct {
    char first_name[50];
    char last_name[50];
    float grade;
} Student;


typedef struct {
    Student students[MAX_STUDENTS];
    int num_students;
} Class;


typedef struct {
    Class classes[MAX_CLASSES];
    int num_classes;
} GraduationYear;


float calculateClassAverage(Class* class) {
    float total = 0;
    for (int i = 0; i < class->num_students; i++) {
        total += class->students[i].grade;
    }
    return total / class->num_students;
}


float calculateGraduationAverage(GraduationYear* graduationYear) {
    float total = 0;
    int totalStudents = 0;

    for (int i = 0; i < graduationYear->num_classes; i++) {
        total += calculateClassAverage(&graduationYear->classes[i]) * graduationYear->classes[i].num_students;
        totalStudents += graduationYear->classes[i].num_students;
    }

    return total / totalStudents;
}

int main() {
    GraduationYear graduationYear;
    graduationYear.num_classes = 1;

    for (int i = 0; i < graduationYear.num_classes; i++) {
        printf("Enter the number of students in class %d: ", i + 1);
        scanf("%d", &graduationYear.classes[i].num_students);


        for (int j = 0; j < graduationYear.classes[i].num_students; j++) {
            printf("Enter first name of student %d: ", j + 1);
            scanf("%s", graduationYear.classes[i].students[j].first_name);
            printf("Enter last name of student %d: ", j + 1);
            scanf("%s", graduationYear.classes[i].students[j].last_name);
            printf("Enter grade of student %d: ", j + 1);
            scanf("%f", &graduationYear.classes[i].students[j].grade);
        }
    }


    for (int i = 0; i < graduationYear.num_classes; i++) {
        float classAverage = calculateClassAverage(&graduationYear.classes[i]);
        printf("\nThe average grade of class %d is: %.2f\n", i + 1, classAverage);
    }


    float graduationAverage = calculateGraduationAverage(&graduationYear);
    printf("\nThe average grade of the graduation year is: %.2f\n", graduationAverage);

    return 0;
}
