#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COLS 60
#define ROWS 60

char map[ROWS][COLS];
char *ptrs[ROWS*COLS];
int ptr9 = 0;

int part2Count(int x, int y, char current)
{
    if (x<0||y<0||x>=COLS||y>=ROWS) return 0;
    
    if (map[y][x] != current)
        return 0;

    if (map[y][x] == '9')
    {
        return 1;
    }

    return(
        part2Count(x+1,y,current + 1)
        +part2Count(x-1,y,current + 1)
        +part2Count(x,y+1,current + 1)
        +part2Count(x,y-1,current + 1)
    );

}

void part2()
{
    int total = 0;
    for(int x=0;x<COLS;x++)
    {
        for (int y=0;y<ROWS;y++)
        {
            total = total + part2Count(x,y,'0');
        }
    }
    printf("Part2: %d\n", total);
}

int part1Count(int x, int y, char current)
{
    if (x<0||y<0||x>=COLS||y>=ROWS) return 0;
    
    if (map[y][x] != current)
        return 0;

    if (map[y][x] == '9')
    {
        ptrs[ptr9++] = &(map[y][x]);
        map[y][x] = 'a';
        return 1;
    }

    return(
        part1Count(x+1,y,current + 1)
        +part1Count(x-1,y,current + 1)
        +part1Count(x,y+1,current + 1)
        +part1Count(x,y-1,current + 1)
    );

}

void part1()
{
    int total = 0;
    for(int x=0;x<COLS;x++)
    {
        for (int y=0;y<ROWS;y++)
        {
            total = total + part1Count(x,y,'0');
            for (int i=0;i<ptr9;i++)
            {
                char *p = ptrs[i];
                *p = '9';
            }
            ptr9 = 0;
        }
    }
    printf("Part1: %d\n", total);
}

int main(void)
{
  char *input_line = NULL;
  size_t lim = 0;

  int line_count = 0;

  while(getline(&input_line, &lim, stdin) > 1){
    strcpy(map[line_count], input_line);
    ++line_count;
  }

   part1();
   part2();
}
