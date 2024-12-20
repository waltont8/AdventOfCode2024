#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// 141
#define COLS 141
#define ROWS 141
#define INFINITY 1000000

char map[ROWS][COLS];
int cost[ROWS][COLS];

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

int countPath()
{
    int total = 0;
    for (int y = 0; y < ROWS; y++)
    {
        for (int x = 0; x < COLS; x++)
        {
            if (map[y][x] == 'O')
                total++;
        }
    }
    return total;
}


void drawPaths(int x, int y)
{
    map[y][x] = 'O';

    if (cost[y][x + 1] == cost[y][x] - 1)
        drawPaths(x + 1, y);
    if (cost[y][x - 1] == cost[y][x] - 1)
        drawPaths(x - 1, y);
    if (cost[y + 1][x] == cost[y][x] - 1)
        drawPaths(x, y + 1);
    if (cost[y - 1][x] == cost[y][x] - 1)
        drawPaths(x, y - 1);
}

void annotate(int x, int y, int tot)
{
    if (map[y][x] != '.')
        return;

    if (tot > (cost[y][x]))
        return;

    cost[y][x] = tot;

    annotate(x, y - 1, tot + 1);
    annotate(x + 1, y, tot + 1);
    annotate(x, y + 1, tot + 1);
    annotate(x - 1, y, tot + 1);
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
            cost[y][x] = INFINITY;

            if (map[y][x] == 'S')
            {
                startX = x;
                startY = y;
                cost[y][x] = 0;
                map[y][x] = '.';
            }

            if (map[y][x] == 'E')
            {
                finishX = x;
                finishY = y;
                map[y][x] = '.';
            }

        }

    }
}

int cheats(int md)
{
    annotate(startX, startY, 0);
    drawPaths(finishX, finishY);
    int best = countPath();
    int total = 0;

    for (int sy = 1; sy < ROWS-1; sy++)for (int sx = 1; sx < COLS-1; sx++)
    {
        for (int ey = 1; ey < ROWS-1; ey++)for (int ex = 1; ex < COLS-1; ex++)
        {
            if (map[ey][ex] != 'O') continue;
            if (map[sy][sx] != 'O') continue;
            int dist = abs(ex-sx)+abs(ey-sy);
            if (dist > md) continue;

            int a = cost[ey][ex] - cost[sy][sx];
            if (a-dist >= 100) total++;
        }
    }
    return total;
}

int main(void)
{
    init();
    dump();
    printf("Part 1 %d\n", cheats(2));
    printf("Part 2 %d\n", cheats(20));
}
