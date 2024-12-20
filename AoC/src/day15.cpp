#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COLS_1 50
#define ROWS_1 50

char map[ROWS_1][COLS_1];

#define COLS_2 100
#define ROWS_2 50

char map2[ROWS_2][COLS_2];

#define LINES 70
#define LENGTH 1000
char code[LINES][LENGTH];

int startX = 0;
int startY = 0;

int startX2 = 0;
int startY2 = 0;

void dump()
{
    for (int y = 0; y < ROWS_1; y++)
    {
        for (int x = 0; x < COLS_1; x++)
        {
            printf("%c", map[y][x]);
        }
        printf("\n");
    }
    printf("\n");
}
void dump2()
{
    for (int y = 0; y < ROWS_2; y++)
    {
        for (int x = 0; x < COLS_2; x++)
        {
            printf("%c", map2[y][x]);
        }
        printf("\n");
    }
    printf("\n");
}

bool pushBox(int x, int y, int dx, int dy, bool dryrun)
{
    if (map[y][x] == '.')
    {
        return true;
    }
    if (map[y][x] == '#')
    {
        return false;
    }
    if (map[y][x] == 'O')
    {
        if (pushBox(x + dx, y + dy, dx, dy, dryrun))
        {
            if (!dryrun)
            {
                map[y][x] = '.';
                map[y + dy][x + dx] = 'O';
            }
            return true;
        }
        else
        {
            return false;
        }
    }
    printf("error %d %d\n", x, y);
    exit(-1);
    return false;
}

bool pushBox2(int x, int y, int dx, int dy, bool dryrun)
{
    if (map2[y][x] == '.')
    {
        return true;
    }
    if (map2[y][x] == '#')
    {
        return false;
    }
    if (dy)
    {
        if (map2[y][x] == '[')
        {
            if (pushBox2(x + dx, y + dy, dx, dy, dryrun) && pushBox2(x + dx + 1, y + dy, dx, dy, dryrun))
            {
                if (!dryrun)
                {
                    map2[y][x] = '.';
                    map2[y + dy][x + dx] = '[';
                    map2[y][x + 1] = '.';
                    map2[y + dy][x + dx + 1] = ']';
                }
                return true;
            }
            else
            {
                return false;
            }
        }
        else if (map2[y][x] == ']')
        {
            if (pushBox2(x + dx, y + dy, dx, dy, dryrun) && pushBox2(x + dx - 1, y + dy, dx, dy, dryrun))
            {
                if (!dryrun)
                {
                    map2[y][x] = '.';
                    map2[y + dy][x + dx] = ']';
                    map2[y][x - 1] = '.';
                    map2[y + dy][x + dx - 1] = '[';
                }
                return true;
            }
            else
            {
                return false;
            }
        }
    }
    if (dx)
    {
        if (map2[y][x] == '[')
        {
            if (pushBox2(x + dx, y + dy, dx, dy, dryrun))
            {
                if (!dryrun)
                {
                    map2[y][x] = '.';
                    map2[y + dy][x + dx] = '[';
                }
                return true;
            }
            else
            {
                return false;
            }
        }
        else if (map2[y][x] == ']')
        {
            if (pushBox2(x + dx, y + dy, dx, dy, dryrun))
            {
                if (!dryrun)
                {
                    map2[y][x] = '.';
                    map2[y + dy][x + dx] = ']';
                }
                return true;
            }
            else
            {
                return false;
            }
        }
    }
    printf("error %d %d %c\n", x, y, map2[y][x]);
    exit(-1);
    return false;
}

void execute(int x, int y, bool (*f)(int, int, int, int, bool))
{
    for (int i = 0; i < LINES; i++)
    {
        for (int j = 0; j < LENGTH; j++)
        {
            char inst = code[i][j];
            switch (inst)
            {
            case '>':
                if (f(x + 1, y, 1, 0, true))
                {
                    f(x + 1, y, 1, 0, false);
                        x = x + 1;
                }
                break;
            case '<':
                if (f(x - 1, y, -1, 0, true))
                {
                    f(x - 1, y, -1, 0, false);
                    x = x - 1;
                }
                break;
            case '^':
                if (f(x, y - 1, 0, -1, true))
                {
                    f(x, y - 1, 0, -1, false);
                        y = y - 1;
                }
                break;
            case 'v':
                if (f(x, y + 1, 0, 1, true))
                {
                    f(x, y + 1, 0, 1, false);
                        y = y + 1;
                }
                break;
            }
        }
    }
}

int score2()
{
    int total = 0;
    for (int x = 0; x < COLS_2; x++)
    {
        for (int y = 0; y < ROWS_2; y++)
        {
            if (map2[y][x] == '[')
            {
                total = total + (y * 100) + x;
            }
        }
    }
    return total;
}

int score()
{
    int total = 0;
    for (int x = 0; x < COLS_1; x++)
    {
        for (int y = 0; y < ROWS_1; y++)
        {
            if (map[y][x] == 'O')
            {
                total = total + (y * 100) + x;
            }
        }
    }
    return total;
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

    line_count = 0;

    while (getline(&input_line, &lim, stdin) > 5)
    {
        strcpy(code[line_count], input_line);
        ++line_count;
    }

    // Build map 2
    for (int x = 0; x < COLS_1; x++)
    {
        for (int y = 0; y < ROWS_1; y++)
        {
            switch (map[y][x])
            {
            case '.':
                map2[y][x * 2] = '.';
                map2[y][x * 2 + 1] = '.';
                break;
            case '#':
                map2[y][x * 2] = '#';
                map2[y][x * 2 + 1] = '#';
                break;
            case 'O':
                map2[y][x * 2] = '[';
                map2[y][x * 2 + 1] = ']';
                break;
            case '@':
                map2[y][x * 2] = '@';
                map2[y][x * 2 + 1] = '.';
                break;
            }
        }
    }

    for (int x = 0; x < COLS_1; x++)
    {
        for (int y = 0; y < ROWS_1; y++)
        {
            if (map[y][x] == '@')
            {
                startX = x;
                startY = y;
                map[y][x] = '.';
                break;
            }
        }
    }

    for (int x = 0; x < COLS_2; x++)
    {
        for (int y = 0; y < ROWS_2; y++)
        {
            if (map2[y][x] == '@')
            {
                startX2 = x;
                startY2 = y;
                map2[y][x] = '.';
                break;
            }
        }
    }
}

int main(void)
{
    init();
    dump();
    //execute(startX, startY, pushBox);
    dump();
    printf("%d\n", score());
    dump2();
    execute(startX2, startY2, pushBox2);
    dump2();
    printf("%d\n", score2());
}
