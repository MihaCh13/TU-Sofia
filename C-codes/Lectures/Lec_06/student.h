#ifndef STUDENT_H_INCLUDED
#define STUDENT_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN 50

struct TTStudent {
    unsigned fNo;
    char name[LEN];
    float avMark;
};

typedef struct TTStudent TStudent;

TStudent  input();
void output(TStudent st);
void inputCSV(char *fname,TStudent *group,unsigned size);
TStudent readStudent(FILE *fin);

#endif // STUDENT_H_INCLUDED
