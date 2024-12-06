#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COLS 130
#define ROWS 130

typedef enum {UP, DOWN, LEFT, RIGHT} direction;
char lab[ROWS][COLS];
int *labCount;
int gx,gy;
int loopCount = 0;

void dump()
{
  for (int y=0;y<ROWS;y++)
  {
    for (int x=0;x<COLS;x++)
    {
      printf("%c", lab[y][x]);
    }
    printf("\n");
  }
}

int inBounds(int x, int y)
{
  if (x<COLS && x>=0 && y >=0 && y<ROWS) return 1;
  return 0;
}

char getTile(int x, int y)
{
  if (inBounds(x,y))
  {
    return lab[y][x];
  }
  return '.';
}

void walkForward(int sx, int sy, direction sd, int loopMode)
{
  direction d = sd;
  int x=sx;
  int y=sy;
  bzero(labCount, ROWS*COLS*sizeof(int));

  while (inBounds(x,y))
  {
    if (loopMode == 1)
    {
      if (lab[y][x] != 'X')
      {
        lab[y][x] = '#';
        walkForward(gx,gy,UP,2);
        lab[y][x] = 'X';
      }
    }

    if (loopMode ==  2)
    {
      if (labCount[y*ROWS+x] >= 4)
      {
        loopCount++;
        return;
      }
      labCount[y*ROWS+x]++;
    }

    if (loopMode == 0)
    {
      lab[y][x] = '*';
    }

oh_my_god_wot:;

    switch (d)
    {
      case UP:
        if (getTile(x,y-1) != '#')
        {
          y = y - 1;
        }
        else
        {
          d = RIGHT;
          goto oh_my_god_wot;
        }
      break;
      case RIGHT:
        if (getTile(x+1,y) != '#')
        {
          x = x + 1;
        }
        else
        {
          d = DOWN;
          goto oh_my_god_wot;
        }
      break;
      case DOWN:
        if (getTile(x,y+1) != '#')
        {
          y = y + 1;
        }
        else
        {
          d = LEFT;
          goto oh_my_god_wot;
        }
      break;
      case LEFT:
        if (getTile(x-1,y) != '#')
        {
          x = x - 1;
        }
        else
        {
          d = UP;
          goto oh_my_god_wot;
        }
      break;
    }
  }
}

void findStartPosition()
{
  for (int x=0;x<COLS;x++)
  {
    for (int y=0;y<ROWS;y++)
    {
      if (lab[y][x] == '^')
      {
        gx=x;
        gy=y;
        lab[y][x] = '.';
        return;
      }
    }
  }
  gx=-1;
  gy=-1;
}

void part1()
{
  int stepCount = 0;
  for (int y=0;y<ROWS;y++)
  {
    for (int x=0;x<COLS;x++)
    {
      if (lab[y][x] != '.' && lab[y][x] != '#')
        stepCount++;
    }
  }
  printf("%d\n", stepCount);
}

int main(void)
{
  char *input_line = NULL;
  size_t lim = 0;

  int line_count = 0;

  while(getline(&input_line, &lim, stdin) > 1){
    strcpy(lab[line_count], input_line);
    ++line_count;
  }

  labCount = (char *)malloc(ROWS*COLS*sizeof(int));

  findStartPosition();

  walkForward(gx,gy,UP,0);
  //dump();
  part1();

  walkForward(gx,gy,UP,1);
  printf("%d\n", loopCount);

  free(labCount);
}
