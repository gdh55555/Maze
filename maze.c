#include "maze.h"
#include <stdlib.h>
#include <string.h>

struct room_struct{
    int wall;  //save wall info
    char mark; //set visit info
};

struct maze_struct{
    int row, col;  //the size of maze
    Room start, end;  //store the start and the end position.
    Room matrix;   //The maze full info
};

Maze Maze_new(void){
    Maze maze;
    maze = malloc(sizeof(*maze));
    maze->row = maze->col = 0;
    maze->start = maze->end = maze->matrix = NULL;
    return maze;
}


bool Maze_read(Maze maze, char* MazeFileName){
    FILE *MazeFile ;
    int sx, sy, ex, ey;
    bool isSucess;

    isSucess = false;
    if((MazeFile = fopen(MazeFileName, "r")) == NULL){
        printf("Maze File can't read\n");
        goto ERROR;
    }
    if(fscanf(MazeFile, "%d %d", &maze->row, &maze->col) != 2)
        goto ERROR;
    maze->matrix = malloc(sizeof(*maze->matrix) * maze->row * maze->col );
    if(maze->matrix == NULL){
        printf("Alloc maze matrix fail\n");
        goto ERROR;
    }
    if(fscanf(MazeFile, "%d %d", &sx, &sy) != 2)
        goto ERROR;
    //set the start position.
    maze->start = getRoom(maze, sx, sy);
    if(fscanf(MazeFile, "%d %d", &ex, &ey) != 2)
        goto ERROR;
    //set the end position.
    maze->end = getRoom(maze, ex, ey);
    //check the values of start and end
    if(!maze->start || !maze->end){
        printf("start or end point not in the right room!\n");
        goto ERROR;
    }
    Room room;
    //store maze info in matrix.
    for(int i = 0; i < maze->row; i++){
        for(int j = 0; j < maze->col; j++){
            room = getRoom(maze, i, j);
            if(fscanf(MazeFile, "%d", &room->wall) != EOF){
                Maze_setMark(room, Room_empty);
            }
            else
                goto ERROR;
        }
    }
    isSucess = true;
ERROR:
    if(MazeFile)
        fclose(MazeFile);
    return isSucess;

}

bool Maze_write(char* shortest, char* SolutionFileName){
    int len;
    bool isSucess;
    FILE* SolutionFile;

    isSucess = false;
    if((SolutionFile = fopen(SolutionFileName, "w")) == NULL){
        printf("Solution File can't write\n");
        goto ERROR;
    }

    len = strlen(shortest);
    //the sums of the move operations.
    fprintf(SolutionFile, "%d\n", len);
    //save move operations.
    for(int i = 0; i < len; i++)
        fprintf(SolutionFile, "%c",  shortest[i]);
    fprintf(SolutionFile, "\n");
    isSucess = true;
ERROR:
    if(SolutionFile)
        fclose(SolutionFile);
    return isSucess;
}

void printBorder(Maze maze, int x, int direction){
    printf("+");
    for(int i = 0; i < maze->col; i++){
        if(getRoom(maze, x, i)->wall & direction)
            printf("---");
        else
            printf("   ");
        printf("+");
    }
    printf("\n");
}

void printRoom(Maze maze, int x){
    if(!maze)
        return;
    //left border
    if(getRoom(maze, x, 0)->wall & L)
        printf("|");
    else
        printf(" ");
    Room room;
    for(int i = 0; i < maze->col; i++){
        room = getRoom(maze, x, i);
        if(!room)
            return;
        //print space , S or E, or other visiting char.
        if(room == maze->start)
            printf(" S ");
        else if(room == maze->end)
            printf(" E ");
        else
            printf(" %c ", room->mark);
        if(room->wall & R)
            printf("|");
        else
            printf(" ");
    }
    printf("\n");
}

void Maze_display(Maze maze){
    if(!maze)
        return;
    //first top line
    printBorder(maze, 0, U);
    for(int i = 0; i < maze->row; i++){
        printRoom(maze, i);
        printBorder(maze, i, D);
    }

}

//return the X -coordinate
int getX(Maze maze, Room room){
    return (room-maze->matrix) / (maze->col);
}

//return the Y -coordinate
int getY(Maze maze, Room room){
    return (room-maze->matrix) % (maze->col);
}

bool Maze_copy(Maze dst, Maze src){
    int x, y;
    bool isSucess;

    isSucess = false;

    if(!dst || !src)
        goto ERROR;
    memcpy(dst, src, sizeof(*src));
    //allocate new matrix for dst.
    dst->matrix = malloc(sizeof(*src->matrix) * src->row * src->col);
    if(!dst->matrix)
        goto ERROR;
    //copy the maze info.
    memcpy(dst->matrix, src->matrix, sizeof(*src->matrix) * src->row * src->col );
    x = getX(src, src->start);
    y = getY(src, src->start);
    //assign start position
    dst->start = getRoom(dst, x, y);
    x = getX(src, src->end);
    y = getY(src, src->end);
    //assign end position
    dst->end = getRoom(dst, x, y);
    isSucess = true;
ERROR:
    return isSucess;

}


void Maze_free(Maze *maze){
    if(*maze){
        free((*maze)->matrix);
    }
    free(*maze);
    *maze = NULL;
}

//check (x,y) is valid
bool isRoom(Maze maze, int x, int y){
    return x >=0 && x < maze->row && y >= 0 && y < maze->col;
}

Room getRoom(Maze maze, int x, int y){
    if(isRoom(maze, x, y))
        //return the real address of the room
        return &maze->matrix[maze->col * x + y];
    else
        return NULL;
}


bool hasWall(Room room, int wall){
    return (room->wall & wall) != 0;
}

void Maze_setMark(Room room, char m){
    if(room)
        room->mark = m;
}

char Maze_getMark(Room room){
    return room->mark;
}

Room Maze_getStart(Maze maze){
    return maze->start;
}
Room Maze_getEnd(Maze maze){
    return maze->end;
}

int Maze_getNeighbor(Maze maze, Room room, Room* neighbor, bool walls){
    int x,y, count;

    count = 0;
    for(int i = 0; i < 4; i++)
        neighbor[i] = NULL;
    if(!maze || !room)
        goto ERROR;
    //get X,Y coordinate
    x = getX(maze, room);
    y = getY(maze, room);
    if(hasWall(room, U) == walls)
        //assign the top neighbor
        if((neighbor[count] = getRoom(maze, x-1, y)))
            count++;
    if(hasWall(room, D) == walls)
        //assign the below neighbor
        if((neighbor[count] = getRoom(maze, x+1, y)))
            count++;
    if(hasWall(room, L) == walls)
        //assign the left neighbor
        if((neighbor[count] = getRoom(maze, x, y-1)))
            count++;
    if(hasWall(room, R) == walls)
        //assign the right neighbor
        if((neighbor[count] = getRoom(maze, x, y+1)))
            count++;

ERROR:
    return count;

}

char Maze_getDirection(Maze maze, Room room, Room neighbor){
    int rx, ry, nx, ny;
    //get X,Y coordinate of the room
    rx = getX(maze, room);
    ry = getY(maze, room);

    //get X,Y coordinate of the neighbor
    nx = getX(maze, neighbor);
    ny = getY(maze, neighbor);

    //judge the direction between room and its neighbor.
    if(rx == nx && ry == ny - 1)
        return 'R';
    else if(rx == nx && ry == ny + 1)
        return 'L';
    else if(rx == nx - 1 && ry == ny)
        return 'D';
    else if(rx == nx + 1 && ry == ny)
        return 'U';
}

void Maze_print_test(Maze maze){
    //just for test
    for(int i =0; i < maze->row; i++){
        for(int j = 0; j < maze->col; j++){
            printf("%4d ", getRoom(maze, i, j)->wall);
        }
        printf("\n");
    }
}

/* version 1
void Maze_display(int ROW, int COL, int** mptr){
    int x, y;
    printf(" ");
    for(x = 0; x < COL; x++)
        if(mptr[0][x] & U)
            printf("_ ");
        else
            printf(" ");
    printf("\n");
    for(x = 0; x < ROW; x++){
        if(mptr[x][0] & L)
            printf("|");
        else
            printf(" ");
        for(y = 0; y < COL; y++){
            printf((mptr[x][y] & D) ? "_" : " ");
            if(mptr[x][y] & R){
                printf("|");
            }
            else{
                printf(" ");
            }
        }
        printf("\n");
    }
}
*/

/* version 1
bool Maze_read(int** mptr, char* MazeFileName){
    FILE *MazeFile ;
    if((MazeFile = fopen(MazeFileName, "r")) == NULL){
        printf("Maze File can't read");
        return false;
    }
    if(fscanf(MazeFile, "%d %d", &ROW, &COL) != 2)
        return false;

    if(fscanf(MazeFile, "%d %d", &sx, &sy) != 2)
        return false;
    if(fscanf(MazeFile, "%d %d", &ex, &ey) != 2)
        return false;
    maze = Maze_alloc(ROW, COL, 0, mptr);
    if(maze == NULL){
        printf("alloc maze fail");
        return false;
    }
    for(int i = 0; i < ROW; i++){
        for(int j = 0; j < COL; j++){
            if(fscanf(MazeFile, "%d", &maze[i][j]) != EOF)
                continue;
            else
                return false;
        }
    }
    return true;

}
*/

/* version 1
int** Maze_alloc(int ROW, int COL, int i, int** mptr){
    if(i == 0){
        mptr = (int**)malloc(ROW*sizeof(int*));
    }
    if(i < ROW){
        mptr[i] = (int*)malloc(COL*sizeof(int));
        alloc_maze(ROW, COL, i+1, mptr);
    }
    else{
        return mptr;
    }
}
*/
