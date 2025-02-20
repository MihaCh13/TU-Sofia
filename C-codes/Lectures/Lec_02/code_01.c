#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define LEN 3000
#define IN 1
#define OUT 0
void strupper(char *name)
{
    for (unsigned i=0; i<strlen(name);++i)
    {
        if (islower(name[i]))
            name[i] = toupper(name[i]);
    }
}
unsigned cntupper(char name[])
{
    unsigned count=0;
    for (unsigned i=0;i<strlen(name);++i){
        if (isupper(name[i]))
        {
            count++;
        }
    }return count;
    }
    unsigned cntwords(char name[])
    {
        unsigned words=0;
        int state=OUT;
        for (unsigned i=0; i<strlen(name);++i)
        {
            if (name[i]==' ' || name[i]=='\t' || name[i]=='\n')
                state=OUT;
            else if (state==OUT){state = IN;
            words++;}
        }
        return words;
    }
 
void changecase(char name[])
{
    for (int i=0;i<strlen(name);++i)
    {
        name[i]= (islower(name[i]))? toupper(name[i]):tolower(name[i]);
    }
}
/*void increment()
{
    int x=3,y=3;
    int z;
    z=x++ + ++y;
    printf("x=%d,y=%d,z=%d\n",x,y,z);
 
}*/
int main()
{
    char name[LEN];
 
    fgets(name,LEN,stdin);
    if (name[strlen(name)-1]=='\n')
        name[strlen(name)-1]='\0';
    //gets_s(name,LEN);
    printf("Hello world, %s!\n",name);
    printf("Upper letters: %u\n",cntupper(name));
    printf("Words: %u\n", cntwords(name));
    changecase(name);
    puts(name);
    strupper(name);
    puts(name);
 
    //increment();
    return 0;
 
}
