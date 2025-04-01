#include "main.h"

int main()
{
    int data[MAXLEN];
    unsigned size =getIntFromTXT("numbers.txt",data,MAXLEN);
    printInts(data,size);
    putIntIntoTXT("numbers.out",data,size);

    return 0;
}

unsigned getIntFromTXT (char *fname, int *data,unsigned maxLen)
{
    FILE *fin = fopen(fname,"r");
    int tmp,i=0;

    if (fin == NULL)
    {
        perror(NULL);
        exit(1);
    }

    while (fscanf(fin,"%d",&tmp)!=EOF && i<maxLen)
    {
        data[i++]=tmp;
    }
    fclose(fin);

    return i;
}

void printInts(int *data, unsigned len)
{
    for (int i=0;i<len;++i)
    {
        printf("%d\t", data[i]);
    }
    NL;
}
void putIntIntoTXT(char *fname,int *data, unsigned len)
{
    FILE *fout = fopen(fname,"w");

    if (fout == NULL)
    {
        perror(NULL);
        exit(1);
    }
    for (int i=0;i<len;++i)
    {
        fprintf(fout,"%d\n",data[i]);
    }
    fclose(fout);
}
