#ifndef _MAZE_H
#define _MAZE_H
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

enum {R = 1, D = 2, L = 4, U = 8};

extern int ROW, COL;  //maze row and col
extern int sx, sy, ex, ey; //the (sx, sy) is start point (ex, ey) is end point
extern int **maze;  //store maze

void display_maze(int ROW, int COL, int** mptr);
bool read_maze(FILE* MazeFile, int** mptr );
int** alloc_maze(int ROW, int COL, int i, int** mptr);
#endif
