#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gifenc.h"
//141
#define COLS 141
#define ROWS 141
#define INFINITY 1000000

#define N 0
#define E 1
#define S 2
#define W 3


char map[ROWS][COLS];
int cost[ROWS][COLS][4] = {INFINITY};

int startX = 0;
int startY = 0;
int finishX = 0;
int finishY = 0;

void dump()
{
    for (int y = 0; y < ROWS; y++)
    {
        for (int x = 0; x < COLS; x++)
        {
            printf("%c", map[y][x]);
        }
        printf("\n");
    }
    printf("\n");
}

void part2()
{
    int total = 0;

    for (int y = 0; y < ROWS; y++)
    {
        for (int x = 0; x < COLS; x++)
        {
            if (map[y][x] == 'O') total++;
        }
    }
    printf("%d\n", total);
}

void drawPaths(int x, int y)
{
    map[y][x] = 'O';

    if (cost[y][x+1] == cost[y][x] - 1 || cost[y][x+1] == cost[y][x] - 1001) drawPaths(x+1,y);
    if (cost[y][x-1] == cost[y][x] - 1||cost[y][x-1] == cost[y][x] - 1001) drawPaths(x-1,y);
    if (cost[y+1][x] == cost[y][x] - 1||cost[y+1][x] == cost[y][x] - 1001) drawPaths(x,y+1);
    if (cost[y-1][x] == cost[y][x] - 1||cost[y-1][x] == cost[y][x] - 1001) drawPaths(x,y-1);
}

void annotate(int x, int y, int dir, int tot)
{
    if (map[y][x] != '.') return;
    if (tot > (cost[y][x][dir])) return;

    cost[y][x][dir] = tot;

    switch (dir)
    {
        case N:
            annotate(x,y-1,N,tot+1);
            annotate(x+1,y,E,tot+1000+1);
            annotate(x-1,y,W,tot+1000+1);

        break;
        case E:
            annotate(x+1,y,E,tot+1);
            annotate(x,y-1,N,tot+1000+1);
            annotate(x,y+1,S,tot+1000+1);


        break;
        case S:
            annotate(x,y+1,S,tot+1);
            annotate(x+1,y,E,tot+1000+1);
            annotate(x-1,y,W,tot+1000+1);
        break;
        case W:
            annotate(x-1,y,W,tot+1);
            annotate(x,y-1,N,tot+1000+1);
            annotate(x,y+1,S,tot+1000+1);

        break;
    }
}

void init()
{
    char *input_line = NULL;
    size_t lim = 0;

    int line_count = 0;

    while (getline(&input_line, &lim, stdin) > 5)
    {
        strcpy(map[line_count], input_line);
        ++line_count;
    }
    
    for (int y = 0; y < ROWS; y++)
    {
        for (int x = 0; x < COLS; x++)
        {
            if (map[y][x] == 'S')
            {
                startX = x;
                startY = y;
                cost[y][x][0] = 0;
                cost[y][x][1] = 0;
                cost[y][x][2] = 0;
                cost[y][x][3] = 0;
                map[y][x] = '.';
            }
            
            if (map[y][x] == 'E')
            {
                finishX = x;
                finishY = y;
                map[y][x] = '.';

            }
        }
        printf("\n");
    }

}

int main(void)
{
    init();
    dump();
    annotate(startX, startY,E,0);
    printf("%d\n", cost[finishY][finishX]);
    drawPaths(finishX, finishY);
    dump();
    part2();

}
