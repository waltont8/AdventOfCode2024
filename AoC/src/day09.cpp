#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMS 19999

char buf[NUMS];
int *disk;
int diskSize = 0;

#define EMPTY 999999

void buildDisk()
{
    disk = (int *)malloc(sizeof(int)*NUMS*9);
    int ptr = 0;
    int id = 0;
    int space = 0;
    for (int n=0;n<NUMS;n++)
    {
        int val = buf[n] - 48;

        for (int m=0;m<val;m++)
        {
            if (space == 1)
            {
                disk[ptr++] = EMPTY;
            }
            else
            {
                disk[ptr++] = id;
            }
        }
        if (space == 1)
        {
            space = 0;
        }
        else
        {
            space = 1;
            id++;
        }
    }
    diskSize = ptr;
}

void dump()
{
    for (int n = 0;n < diskSize; n++)
    {
        int val = disk[n];
        if (val == EMPTY) printf(".");
        else printf("%d", val);
    }
    printf("\n");
}
void swap(int a, int b)
{
    int c = disk[a];
    disk[a] = disk[b];
    disk[b] = c;
}

void part1()
{
    int startPtr = 0;
    int endPtr = diskSize-1;

    while (startPtr<endPtr)
    {
        if (disk[startPtr] == EMPTY)
        {
            if (disk[endPtr] != EMPTY)
            {
                swap(startPtr, endPtr);
                startPtr++;
            }
            endPtr--;
        }
        else
        {
            startPtr++;
        }
    }
    long long total = 0;
    for (int n=0;n<diskSize;n++)
    {
        if (disk[n]!=EMPTY)
        total = total + disk[n]*n;
    }
    printf("%lld\n",total);
}

int skipBackSpace(int ptr)
{
    while (ptr >= 0 && disk[ptr] == EMPTY)
        ptr--;
   
    return ptr;
}

void windback(int ptr, int *start, int *size)
{
    int cur = disk[ptr];
    int oldptr = ptr;

    while (ptr >= 0 && disk[ptr] == cur)
        ptr--;
   
    *start = ptr+1;
    *size = oldptr-ptr;

    return;
}

int getEmptySize(int n)
{
    int count = 0;

    while (disk[n] == EMPTY)
    {
        count++;
        n++;
    }

    return count;
}

int findGap(int size, int max)
{
    for (int n=0;n<max;n++)
    {
        if (disk[n] == EMPTY)
        {
            int emptySize = getEmptySize(n);
            if (emptySize >= size) return n;
            else n += emptySize;
        }
    }

    return -1;
}

void swapBlock(int a, int b, int size)
{
    for (int n=0;n<size;n++)
    {
      swap(a,b);
      a++;
      b++;
    }
}
void part2()
{
    int endPtr = diskSize-1;

    while (endPtr>0)
    {
        endPtr = skipBackSpace(endPtr);
        int start = 0;
        int size = 0;
        windback(endPtr, &start, &size);
        
        int startPtr = findGap(size, endPtr);
        if (startPtr >= 0)
        {
            swapBlock(startPtr, start, size);
        }
        endPtr -= size;
    }

    long long total = 0;
    for (int n=0;n<diskSize;n++)
    {
        if (disk[n]!=EMPTY)
        total = total + disk[n]*n;
    }
    printf("%lld\n",total);

}

int main(void)
{
  char *input_line = NULL;
  size_t lim = 0;

  getline(&input_line, &lim, stdin);
  strcpy(buf, input_line);

  buildDisk();
  part1();


  buildDisk();
  part2();
}
