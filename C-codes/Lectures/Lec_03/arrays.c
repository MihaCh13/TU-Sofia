#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BOOL int
#define FALSE 0
#define TRUE !FALSE

void inputArray(int data[], unsigned len)
{
    for (int i = 0; i < len; i++) {
        printf("A(%d) = ", i+1);
        scanf("%d", data + i); //data+i = &data[i]
    }
}

void inputRandomArray(int data[], unsigned len, BOOL isCustomSeed)
{
    const int MIN = -10, MAX = 10;

    if (isCustomSeed)
        srand(time(NULL));

    for (int i = 0; i < len; i++) {
        data[i] = rand() %(MAX-MIN+1) + MIN;
    }
}

void outputArray(int *data, unsigned len)
{
    for (int i = 0; i < len; i++) {
        printf("%d\t", data[i]); //data[i] = *(data + i)
    }
    printf("\n");
}

long sumarray(int data[], unsigned len)
{
    long sum = 0;

    for (int i = 0; i < len; i++)
    {
        sum += data[i];
    }
    return sum;
}
double averateNegatives(int data[], unsigned len) {
    long sum = 0;
    unsigned count = 0;

    for (int i = 0; i < len; i++) {
        if (data[i] < 0) {
            count++;
            sum += data[i];
        }
    }
    return (count > 0) ? (double)sum/count : 0;
}

int minEvenElement(int data[], unsigned len)
{
    int index = -1;

    for (int i = 0; i < len; i++) {
        if (data[i] % 2 == 0) {
            if (index == -1) {
                index = i;
            }
            else if (data[index] > data[i]) {
                index = i;
            }
        }
    }
    return index;
}

int maxArray(int data[], unsigned len) {
    int max =data[0];

    for (int i = 0; i < len; i++) {
        if (data[i] > max) {
            max = data[i];
        }
    }
    return max;
}

unsigned removeEvenElement(int data[], unsigned len) {
    int i,j;
    for (i = j = 0; i < len; i++) {
        if (data[i] % 2 == 0) {
            data[j++] = data[i];
        }
    }
    return j;
}

void moveArray(int data[], unsigned len) {
    for (int i = 0; i < len; i++) {
        data[i+len] = data[i];
    }
}

unsigned extendetArray(int data[], unsigned len) {
    unsigned index = 0;
    moveArray(data,len);
    // outputArray (data,2*len);
    for (int i = len; i < 2*len; i++) {
        data[index++] = data[i];
        if (data[i] > 0) {
            data[index++] = data[i]*-1;
        }
    }
    return index;

}

unsigned countElement(int data[], unsigned len, int element) {
    unsigned count = 0;

    for (int i = 0; i < len; i++) {
        if (data[i] == element) {
            count++;
        }
    }
    return count; // Трябва да се върне след приключване на цикъла
}

int main(void)
{
    const unsigned SIZE = 10;
    int array[SIZE*2];
    double result;
    int index, max;
    unsigned len;

    //inputArray(array, 3);
    //inputRandomArray(array, SIZE, TRUE);
    inputRandomArray(array, SIZE, FALSE);
    outputArray(array, SIZE);
    printf("The sum is %d\n", sumarray(array, SIZE));
    result = averateNegatives(array, SIZE);
    if (result == 0) {
        printf("No such data...\n");
    }
    else {
        printf("The average of Negatives: %g\n", result);
    }
    index = minEvenElement(array, SIZE);
    if (index==-1) {
        printf("No such data...\n");
    }
    else {
        printf("Min Even Element: %d\n", array[index]);
    }
    printf("Average of Negatives: %f\n", averateNegatives(array, SIZE));
    printf("Minimum Even Element: %d\n", minEvenElement(array, SIZE));

    max = maxArray(array, SIZE);
    printf("Max Element is %d.It\'s repeated %u times.\n", max, countElement(array, SIZE, max));
    len = extendetArray(array, SIZE);
    outputArray(array, len);
    len = removeEvenElement(array, len);
    if (len) {
        printf("Empty array\n");
    }
    else {
        outputArray(array, len);
    }
    outputArray(array, len);
    return 0;
}
