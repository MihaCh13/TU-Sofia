#include "student.h"

int main()
{
    TStudent student;
    TStudent group[10];

 //   student = input();
    inputCSV("students.csv",&student,1);
    output(student);

    return 0;
}
