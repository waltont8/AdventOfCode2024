#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COLS 140
#define ROWS 140

char map[ROWS][COLS];

void dump()
{

        for (int y=0;y<ROWS;y++)
    {
    for(int x=0;x<COLS;x++)
        {
            printf("%c", map[y][x]);
        }
            printf("\n");
    }
    printf("\n");
}

char get(int x, int y)
{
    if (x<0 || y<0 || x>=COLS || y >= ROWS) return '.';
    return map[y][x];
}

int no(int x, int y, char target)
{
    if (get(x,y) != target && get(x,y) != (target - 32) && get(x,y) !='*')
        return 1;

    return 0;
}

void count2(char target, int x, int y, int *area, int *corner)
{
    if (get(x,y) != target) return;
    map[y][x] = target - 32;

    (*area)++;
    if (no(x+1,y,target))
    {
        if (no(x,y+1,target)&&no(x+1,y+1,target))
        {
            (*corner)++;
        }
        if (!no(x,y+1,target)&&!no(x+1,y+1,target))
        {
            (*corner)++;
        }
    }
    if (no(x-1,y,target))
    {
        if (no(x,y-1,target)&&no(x-1,y-1,target))
        {
            (*corner)++;

        }
        if (!no(x,y-1,target)&&!no(x-1,y-1,target))
        {
            (*corner)++;         
        }
    }
    if (no(x,y+1,target))
    {
        if (no(x-1,y,target)&&no(x-1,y+1,target))
        {
            (*corner)++;      

        }
        if (!no(x-1,y,target)&&!no(x-1,y+1,target))
        {
            (*corner)++;       

        }        
    }
    if (no(x,y-1,target))
    {
        if (no(x+1,y,target)&&no(x+1,y-1,target))
        {
            (*corner)++;map[y][x]='*';
        }
        if (!no(x+1,y,target)&&!no(x+1,y-1,target))
        {
            (*corner)++;map[y][x]='*';
        }    
    }

    count2(target, x+1, y, area, corner);
    count2(target, x-1, y, area, corner);
    count2(target, x, y+1, area, corner);
    count2(target, x, y-1, area, corner);
}

void part2()
{
    int total = 0;
    for(int x=0;x<COLS;x++)
    {
        for (int y=0;y<ROWS;y++)
        {
            if (map[y][x] >= 'a' && map[y][x] <= 'z')
            {
                int area = 0;
                int corner = 0;
                char target = map[y][x];
                count2(map[y][x],x,y,&area,&corner);
                total += area*corner;
            }
        }
    }
    printf("Part2: %d\n", total);
}

void count(char target, int x, int y, int *area, int *perim)
{
    if (get(x,y) != target) return;
    map[y][x] = target + 32;

    (*area)++;
    if (get(x+1,y) != target && get(x+1,y) != (target + 32)) (*perim)++;
    if (get(x-1,y) != target && get(x-1,y) != (target + 32)) (*perim)++;
    if (get(x,y+1) != target && get(x,y+1) != (target + 32)) (*perim)++;
    if (get(x,y-1) != target && get(x,y-1) != (target + 32)) (*perim)++;

    count(target, x+1, y, area, perim);
    count(target, x-1, y, area, perim);
    count(target, x, y+1, area, perim);
    count(target, x, y-1, area, perim);
}

void part1()
{
    int total = 0;
    for(int x=0;x<COLS;x++)
    {
        for (int y=0;y<ROWS;y++)
        {
            if (map[y][x] >= 'A' && map[y][x] <= 'Z')
            {
                int area = 0;
                int perim = 0;
                char target = map[y][x];
                count(map[y][x],x,y,&area,&perim);
                total += area*perim;
            }
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
