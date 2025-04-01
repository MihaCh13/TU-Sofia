#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#define MAXLEN 10
#define NL printf("\n")

unsigned getIntFromTXT (char *fname, int *data,unsigned maxLen);
void printInts(int *data, unsigned len);
void putIntIntoTXT(char *fname,int *data, unsigned len);
#endif // MAIN_H_INCLUDED
