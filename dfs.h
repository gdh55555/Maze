#ifndef _DFS_H_
#define _DFS_H_
#include "maze.h"

int getShortestMaze(Maze maze, Room room, int depth, Maze shortest);
bool getShortestPath(Maze maze, Room room, int depth, char* path, char* shortestPath);
#endif
