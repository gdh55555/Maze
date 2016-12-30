#include "dfs.h"
#include <limits.h>
#include <stdbool.h>

int getShortestMaze(Maze maze, Room room, int depth, Maze shortest){
    int nsize;
    static int shortDepth = INT_MAX;
    char mark;
    Room neighbor[4];

    mark = Maze_getMark(room);
    //check it whether visit or not.
    if(mark == Room_visit)
        return shortDepth;
    //reach the end.
    if(room == Maze_getEnd(maze)){
        //copy shortest Maze and update the value of shortDepth.
        if(depth < shortDepth){
            Maze_copy(shortest, maze);
            shortDepth = depth;
        }
        return shortDepth;
    }

    //set visit mark to the visiting room.
    Maze_setMark(room, Room_visit);
    //get accessible neighbor info
    nsize = Maze_getNeighbor(maze, room, neighbor, false);
    //traverse the neighbor to find path.
    for(int i = 0; i < nsize; i++){
        //recurse
        getShortestMaze(maze, neighbor[i], depth+1, shortest);
    }
    //reset the mark of the room.
    Maze_setMark(room, Room_empty);
    return shortDepth;
}

/**
 * copy path move operations from src to dst.
 */
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
    //check it whether visit or not.
    if(mark == Room_visit)
        return isFindPath;
    //reach the end.
    if(room == Maze_getEnd(maze)){
        isFindPath = true;
        //update shortestPath and shortDepth.
        if(depth < shortDepth){
            //update.
            pathCopy(shortestPath, path, depth);
            shortDepth = depth;
        }
        return isFindPath;
    }

    //set visit mark to the visiting room.
    Maze_setMark(room, Room_visit);
    //get accessible neighbor info
    nsize = Maze_getNeighbor(maze, room, neighbor, false);
    //traverse the neighbor to find path.
    for(int i = 0; i < nsize; i++){
        //record the move operation.
        path[depth] = Maze_getDirection(maze, room, neighbor[i]);
        //recurse
        getShortestPath(maze, neighbor[i], depth+1, path, shortestPath);
    }
    //reset the mark of the room.
    Maze_setMark(room, Room_empty);
    return isFindPath;
}
