#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <map>
#include <tuple>

#define COLS 50
#define ROWS 50

char grid[ROWS][COLS];

using namespace std;

map<char, vector<tuple<int, int>>> nodeMap;

void dump()
{
  for (int y=0;y<ROWS;y++)
  {
    for (int x=0;x<COLS;x++)
    {
      printf("%c", grid[y][x]);
    }
    printf("\n");
  }
}

int inBounds(int x, int y)
{
  if (x<COLS && x>=0 && y >=0 && y<ROWS) return 1;
  return 0;
}

char getPoint(int x, int y)
{
  if (inBounds(x,y))
  {
    return grid[y][x];
  }
  return '.';
}

void findNodes()
{
  for (int y=0;y<ROWS;y++)
  {
    for (int x=0;x<COLS;x++)
    {
      if (grid[y][x] != '.')
      {
        if (nodeMap.count(grid[y][x]))
        {
          nodeMap[grid[y][x]].push_back({x,y});
        }
        else
        {
          nodeMap[grid[y][x]] = {{x,y}}; 
        }
        
      }
    }
  }
}

int setGrid(int x, int y, char c)
{
  if (x<0 || y<0 || x >=COLS || y >= ROWS) return 0;

  grid[y][x] = c;

  return 1;
}

void part1()
{
  map<char, vector<tuple<int, int>>>::iterator it;
  for (it = nodeMap.begin(); it != nodeMap.end(); it++)
  {
    printf("%c - %zu\n", it->first, it->second.size());
    for (int a=0; a<it->second.size(); a++)
    {
      for (int b=a+1; b<it->second.size(); b++)
      {
        int x1 = get<0>(it->second[a]);
        int y1 = get<1>(it->second[a]);
        int x2 = get<0>(it->second[b]);
        int y2 = get<1>(it->second[b]);
        int distx = (x1-x2);
        int disty = (y1-y2);
        setGrid(x1+distx, y1+disty, '#');
        setGrid(x2-distx, y2-disty, '#');
        
      }
    }
  }
  int count = 0;

  for (int y=0;y<ROWS;y++)
  {
    for (int x=0;x<COLS;x++)
    {
      if (grid[y][x] == '#')
      {
        count++;
      }
    }
  }
  printf("Part1: %d\n", count);
}

void part2()
{
  map<char, vector<tuple<int, int>>>::iterator it;
  for (it = nodeMap.begin(); it != nodeMap.end(); it++)
  {
    printf("%c - %zu\n", it->first, it->second.size());
    for (int a=0; a<it->second.size(); a++)
    {
      for (int b=a+1; b<it->second.size(); b++)
      {
        int x1 = get<0>(it->second[a]);
        int y1 = get<1>(it->second[a]);
        setGrid(x1,y1,'#');
        int x2 = get<0>(it->second[b]);
        int y2 = get<1>(it->second[b]);
        setGrid(x2,y2,'#');
        int distx = (x1-x2);
        int disty = (y1-y2);

        int targetX = x1+distx;
        int targetY = y1+disty;
        while(setGrid(targetX, targetY, '#'))
        {
          targetX += distx;
          targetY += disty;
        }

        targetX = x2-distx;
        targetY = y2-disty;
        while(setGrid(targetX, targetY, '#'))
        {
          targetX -= distx;
          targetY -= disty;
        }
        
      }
    }
  }
  int count = 0;

  for (int y=0;y<ROWS;y++)
  {
    for (int x=0;x<COLS;x++)
    {
      if (grid[y][x] == '#')
      {
        count++;
      }
    }
  }
  printf("Part2: %d\n", count);
}

int main(void)
{
  char *input_line = NULL;
  size_t lim = 0;

  int line_count = 0;

  while(getline(&input_line, &lim, stdin) > 1){
    strcpy(grid[line_count], input_line);
    ++line_count;
  }

  findNodes();

  part1();
  dump();

  part2();
  dump();
}
