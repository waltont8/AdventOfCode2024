#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COLS 71
#define ROWS 71
#define INFINITY 1000000

#define N 0
#define E 1
#define W 2
#define S 3

bool goal = false;

char map[ROWS][COLS] = {'.'};
int cost[ROWS][COLS] = {INFINITY};

bool oob(int x, int y)
{
    if (x < 0 || y < 0 || x >= COLS || y >= ROWS)
        return true;
    return false;
}

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

void part1()
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
    printf("%d\n", total);
}

void drawPaths(int x, int y)
{
    map[y][x] = 'O';

    int lowest = cost[y][x];
    int dir = -1;

    if (!oob(x - 1, y) && cost[y][x - 1] < lowest)
    {
        lowest = cost[y][x - 1];
        dir = W;
    }
    if (!oob(x + 1, y) && cost[y][x + 1] < lowest)
    {
        lowest = cost[y][x + 1];
        dir = E;
    }
    if (!oob(x, y - 1) && cost[y - 1][x] < lowest)
    {
        lowest = cost[y - 1][x];
        dir = N;
    }
    if (!oob(x, y + 1) && cost[y + 1][x] < lowest)
    {
        lowest = cost[y + 1][x];
        dir = S;
    }

    switch (dir)
    {
    case N:
        drawPaths(x, y - 1);
        break;
    case S:
        drawPaths(x, y + 1);
        break;
    case E:
        drawPaths(x + 1, y);
        break;
    case W:
        drawPaths(x - 1, y);
        break;
    }
    return;
}

void annotate(int x, int y, int tot)
{

    if (oob(x, y))
        return;
    if (map[y][x] != '.')
        return;
    if (tot >= (cost[y][x]))
        return;

    cost[y][x] = tot;
     if (x == 70 && y == 70)
    {
        goal = true;
        return;
    }

    annotate(x, y - 1, tot + 1);
    annotate(x, y + 1, tot + 1);
    annotate(x + 1, y, tot + 1);
    annotate(x - 1, y, tot + 1);
}

void init()
{
    char *input_line = NULL;
    size_t lim = 0;

    int line_count = 0;
    for (int y = 0; y < ROWS; y++)
    {
        for (int x = 0; x < COLS; x++)
        {
            map[y][x] = '.';
            cost[y][x] = INFINITY;
        }
    }

    int count = 0;
    while (getline(&input_line, &lim, stdin) > 2 && count < 1024)
    {
        int x, y;
        sscanf(input_line, "%d,%d", &x, &y);
        // printf("%d,%d\n",x,y);
        map[y][x] = '*';
        /*
        // for part 2
        for (int y = 0; y < ROWS; y++)
        {
            for (int x = 0; x < COLS; x++)
            {
                cost[y][x] = INFINITY;
            }
        }

        annotate(0, 0, 0);
        printf("%d - %d count %d,%d\n", goal, count, x, y);
        goal = false;

        */
        count++;
    }
}

int main(void)
{
    init();
    printf("Done init...\n");
    dump();
    annotate(0, 0, 0);
    printf("Annotated\n");
    drawPaths(70, 70);
    dump();
    part1();
    printf("Goal %d\n", goal - 1);
}
