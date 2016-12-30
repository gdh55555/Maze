#ifndef _MAZE_H_
#define _MAZE_H_
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * If the location has a wall above it the variable has 8 added to it.
 * If the location has a wall to the left of it the variable has 4 added to it
 * If the location has a wall below it the variable has 2 added to it.
 * If the location has a wall to the right of it the variable has 1 added to it.
 * It also mean moves direction from start position to the end position.
 */
enum {R = 1, D = 2, L = 4, U = 8};

/**
 * Three characters can be used to mark a room.
 * can have perceptual intuition to check the result
 * '#' is maze visit marks
 * 'X' stands for the path can't reach the end.
 */
#define Room_empty ' '
#define Room_visit '#'
#define Room_canot 'X'

/**
 * Two data structures:room and maze.
 * To store the maze infomation and  wall
 * Maze has member: the maze's size  and maze matrix info
 * Room has the wall and marks
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
 * maze The maze info to strore in.
 * MazeFileName The file to read into the maze.
 */
bool Maze_read(Maze maze, char* MazeFileName);

/**
 * write move operations to file
 * maze The maze info to strore in.
 * SolutionFileName The file to write to the maze.
 */
bool Maze_write(char* shortest, char* SolutionFileName);

/**
 * display maze
 * maze The maze info in it.
 * example:
 *   +---+---+---+---+
 *   |       |       |
 *   +---+   +   +   +
 *   |           |   |
 *   +---+---+---+   +
 *   |   |     S     |
 *   +   +   +   +---+
 *   |   |   |       |
 *   +   +   +---+   +
 *   | E         |   |
 *   +---+---+---+---+
 */
void Maze_display(Maze maze);

/**
 * Copy dst maze from src. This is deep copy operation.
 * Will assign src value to dst, and allocate memory for dst.
 */
bool Maze_copy(Maze dst, Maze src);

/**
 * Free the Maze and set the variable to NULL
 */
void Maze_free(Maze *maze);

/**
 * check (x,y) is a room or not
 * maze The maze to check whether have (x,y) room or not.
 */
bool isRoom(Maze maze, int x, int y);

/**
 * get room address from Maze
 * maze The maze to get (x,y) room.
 */
Room getRoom(Maze maze, int x, int y);

/**
 * mark the room with characters
 * room Set m characters to room mark.
*/
void Maze_setMark(Room room, char m);

/**
 * get the mark of room , return the result
 * room get characters of room mark.
*/
char Maze_getMark(Room room);

/**
 * Get the start room of the maze.
 */
Room Maze_getStart(Maze maze);

/**
 * Get the end room of the maze.
 */
Room Maze_getEnd(Maze maze);

/**
 * Get the neighbor rooms of the specified room.
 * romm The assigned room
 * neighbor To store the room's neighbor info
 * walls To check the room has the wall between them.
 */
int Maze_getNeighbor(Maze maze, Room room, Room* neighbor, bool walls);

/**
 * Get direction between room and its neighbor.
 * return char to show its move operations.
 * if from room to neighbor should move up, it retrun 'U'.
 */
char Maze_getDirection(Maze maze, Room room, Room neighbor);

/**
 * just for test the read maze info.
 */
void Maze_print_test(Maze maze);

#endif
