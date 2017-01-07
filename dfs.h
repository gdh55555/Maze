#ifndef _DFS_H_
#define _DFS_H_
#include "maze.h"

/**
 * DFS to get shortest path from the start position to the end position
 * it save the path from the start to the end, use '#' marks.
 * room The first room is the start room, and then alter.
 * depth The depth of the recursion
 * shortest The maze to store the shortest path maze info
 */
int getShortestMaze(Maze maze, Room room, int depth, Maze shortest);

/**
 * DFS to get shortest path from the start position to the end position
 * it save the move operations to shortestPath
 * room The first room is the start room, and then alter.
 * depth The depth of the recursion
 * path to update the recursion operations.
 * shortestPatht The Shortest path move ops to store into.
 */
bool getShortestPath(Maze maze, Room room, int depth, char* path, char* shortestPath);
#endif
