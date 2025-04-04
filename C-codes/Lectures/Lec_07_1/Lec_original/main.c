#include <stdio.h>
#include <stdlib.h>

void copyFile(char *in,char *out)
{
    //FILE *in = fopen(in,"r");
    FILE *fin, *fout;
    char ch;

    if ((fin=fopen(in,"r"))==NULL)
    {
        perror("IN file");
        exit(2);
    }

    if ((fout=fopen(out,"a"))==NULL)
    {
        perror("OUT file");
        exit(2);
    }
    while ((ch=fgetc(fin))!=-1)
    {
        fputc(ch,fout);
    }
    fclose(fin);
    fclose(fout);
}


void copyFileWithout(char *in,char *out)
{
    //FILE *in = fopen(in,"r");
    FILE *fin, *fout;
    char ch;

    if ((fin=fopen(in,"r"))==NULL)
    {
        perror("IN file");
        exit(2);
    }

    if ((fout=fopen(out,"a"))==NULL)
    {
        perror("OUT file");
        exit(2);
    }
    while ((ch=fgetc(fin))!=-1)
    {
        if (ch !='a')
        fputc(ch,fout);
    }
    fclose(fin);
    fclose(fout);
}
void changeFile(char *fname)
{
    //FILE *in = fopen(in,"r");
    FILE *f;
    char ch;

    if ((f=fopen(fname,"r+"))==NULL)
    {
        perror("File");
        exit(2);
    }

    while ((ch=fgetc(f))!=-1)
    {
        if (ch =='t')
        {
         fseek(f,0L,SEEK_CUR);
         ch ='T';
         fputc(ch,f);
         fseek(f,0L,SEEK_CUR);
        }

    }
    fclose(f);
}

int main()
{
   // copyFile("lipsum.txt","lipsum-copy.txt");
    //copyFileWithout("lipsum-copy.txt","lipsum-without.txt");
    changeFile("lipsum-without.txt");
    printf("Done.\n");
    return 0;
}
