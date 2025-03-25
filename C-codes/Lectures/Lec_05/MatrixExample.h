#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#define MIN -10
#define MAX 10
#define NO_COLS 3

void inputRandom(int a[][NO_COLS],unsigned rows,unsigned cols);
void print(int a[][NO_COLS],unsigned rows,unsigned cols);
int sumMD(int a[][NO_COLS],unsigned cols);
int minBelowMD(int a[][NO_COLS],unsigned cols);
int maxAboveMD(int a[][NO_COLS],unsigned cols);
float averageSD(int a[][NO_COLS],unsigned cols);
int sumNegAboveSD(int a[][NO_COLS],unsigned cols);
int sumPosBelowSD(int a[][NO_COLS],unsigned cols);
void averageCols(int a[][NO_COLS],unsigned cols,float avrs[]);
void printResult(float result[],unsigned cols);

#endif // MAIN_H_INCLUDED
