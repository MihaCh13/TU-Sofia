#include <stdio.h>
#include <stdlib.h>

enum boolean {false,true};

int findMin(int a[],unsigned size, int start)
{
    int index=start;
    for (int i=index+1;i<size;++i)
    {
        if (a[index]>a[i])
            index=i;
    }return index;
}

/*void swap(int a, int b)
{
    int temp;
    temp=a;
    a=b;
    b=temp;
}*/
void swap(int *a, int *b)
{
    int temp;
    temp =*a;
    *a=*b;
    *b=temp;
}

//gipsy folk dance

void selectionSort(int a[], unsigned size)
{
    int minIndex;
    for (int i=0;i<size-1;++i)
    {
      minIndex=findMin(a,size,i);
      swap(a+minIndex,a+i);
    }
}
// Hungarian folk dance
void bubbleSort(int a[],unsigned size)
{
    enum boolean isChanged=true;
    //for (int i=0;i<size-1;i++)
    for (int i=0;i<size-1 && isChanged;i++)
    {
        isChanged=false;
        for (int j=i+1;j<size;++j)
        {
            if (a[j-1]>a[j])
                swap(&a[j-1],&a[j]);
                isChanged=true;
        }
    }
}

void printArray(int a[],unsigned size)

{
    for (int i=0;i<size;++i)
    {
        printf("%d\t",a[i]);
    }
    printf("\n");
}

int myCompare(const void *a, const void *b)
{
    int *ai = (int*)a;
    int *bi = (int*)b;

    return *bi - *ai;
}

int findNext(int a[],unsigned size,int start,int value)
{
    for (int i=start;i<size;++i)
    {
        if (a[i]==value)
            return i;
    }
    return -1;
}
int findFirst(int a[],unsigned size,int value)
{
    return findNext(a,size,0,value);
}

int binarySearch(int a[], unsigned size, int value)
{
    int low=0,high=size-1,mid;

    do
    {
        mid=low+(high-low)/2;
        if(a[mid]==value)
            return mid;
        else if (a[mid]>value)
            high=mid-1;
        else
            low =mid+1;
    }
    while (high>=low);
    return -1;
}

int main()

{

    int a[]={3,0,1,6,7,2,5,4,9,8};
    const unsigned SIZE = sizeof(a)/sizeof(int);
    int index;

    printArray(a,SIZE);

    //swap(a[0],a[1]);
   //swap(&a[0],&a[1]);
   //selectionSort(a,SIZE);
    bubbleSort(a,SIZE);
    //qsort(a,SIZE,sizeof(int),myCompare);
    printArray(a,SIZE);

    //index=findFirst(a,SIZE,-1);
    index=findFirst(a,SIZE,1);
    index=findNext(a,SIZE,index+1,1);
    index=binarySearch(a,SIZE,1);
    if (index==-1)
    {
        puts("No such value..\n");
    }
    else
    {
        printf("Index: %d\n",index);
    }

    return 0;
}
