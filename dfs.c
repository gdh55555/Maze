#include "dfs.h"
#include <limits.h>
#include <stdbool.h>

int getShortestMaze(Maze maze, Room room, int depth, Maze shortest){
    int nsize;
    static int shortDepth = INT_MAX;
    char mark;
    Room neighbor[4];

    mark = Maze_getMark(room);
    if(mark == Room_visit)
        return shortDepth;
    if(room == Maze_getEnd(maze)){
        if(depth < shortDepth){
            Maze_copy(shortest, maze);
            shortDepth = depth;
        }
        return shortDepth;
    }

    Maze_setMark(room, Room_visit);
    nsize = Maze_getNeighbor(maze, room, neighbor, false);
    for(int i = 0; i < nsize; i++){
        getShortestMaze(maze, neighbor[i], depth+1, shortest);
    }
    Maze_setMark(room, Room_empty);
    return shortDepth;
}

void pathCopy(char* dst, char* src, int len){
    if(!src || !dst)
        return;
    int i;
    for(i = 0; i < len; i++)
        dst[i] = src[i];
    dst[i] = '\0';
}

bool getShortestPath(Maze maze, Room room, int depth, char* path, char* shortestPath){
    int nsize;
    static int shortDepth = INT_MAX;
    static bool isFindPath = false;
    char mark;
    Room neighbor[4];

    mark = Maze_getMark(room);
    if(mark == Room_visit)
        return isFindPath;
    if(room == Maze_getEnd(maze)){
        isFindPath = true;
        if(depth < shortDepth){
            pathCopy(shortestPath, path, depth);
            shortDepth = depth;
        }
        return isFindPath;
    }

    Maze_setMark(room, Room_visit);
    nsize = Maze_getNeighbor(maze, room, neighbor, false);
    for(int i = 0; i < nsize; i++){
        path[depth] = Maze_getDirection(maze, room, neighbor[i]);
        getShortestPath(maze, neighbor[i], depth+1, path, shortestPath);
    }
    Maze_setMark(room, Room_empty);
    return isFindPath;
}
