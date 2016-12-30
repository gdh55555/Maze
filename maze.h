#ifndef _MAZE_H_
#define _MAZE_H_
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

enum {R = 1, D = 2, L = 4, U = 8};

/**
 * Three characters can be used to mark a room.
 *can have perceptual intuition to check the result
 */
#define Room_empty ' '
#define Room_visit '#'
#define Room_canot 'X'

/**
 * Two data structures:room and maze.
 * To store the maze infomation and  wall
 */
struct room_struct;
struct maze_struct;
typedef struct room_struct *Room;
typedef struct maze_struct *Maze;

/* first version
extern int ROW, COL;  //maze row and col
extern int sx, sy, ex, ey; //the (sx, sy) is start point (ex, ey) is end point
extern int **maze;  //store maze
*/


/**
 * construct a maze variable.
 */
Maze Maze_new(void);

/*
void Maze_display(int ROW, int COL, int** mptr);
bool Maze_read(int** mptr, char* MazeFileName );
int** Maze_alloc(int ROW, int COL, int i, int** mptr);
*/

/**
 * read maze from file
 */
bool Maze_read(Maze maze, char* MazeFileName);
bool Maze_write(char* shortest, char* SolutionFileName);

/**
 * display maze
 */
void Maze_display(Maze maze);

bool Maze_copy(Maze dst, Maze src);

void Maze_free(Maze *maze);

/**
 * check (x,y) is a room or not
 */
bool isRoom(Maze maze, int x, int y);

/**
 * get room address from Maze
 */
Room getRoom(Maze maze, int x, int y);

/**
 * mark the room with characters
 */
void Maze_setMark(Room room, char m);
char Maze_getMark(Room room);

Room Maze_getStart(Maze maze);
Room Maze_getEnd(Maze maze);

int Maze_getNeighbor(Maze maze, Room room, Room* neighbor, bool walls);
char Maze_getDirection(Maze maze, Room room, Room neighbor);

void Maze_print_test(Maze maze);

#endif
