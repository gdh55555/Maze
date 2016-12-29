#include "maze.h"

struct room_struct{
    int wall;
    char mark;
};

struct maze_struct{
    int row, col;
    Room start, end;
    Room matrix;
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
    bool isSucess = false;
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
    maze->start = getRoom(maze, sx, sy);
    if(fscanf(MazeFile, "%d %d", &ex, &ey) != 2)
        goto ERROR;
    maze->end = getRoom(maze, ex, ey);
    if(!maze->start || !maze->end){
        printf("start or end point not in the right room!\n");
        goto ERROR;
    }
    Room room;
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
    if(getRoom(maze, x, 0)->wall & L)
        printf("|");
    else
        printf(" ");
    Room room;
    for(int i = 0; i < maze->col; i++){
        room = getRoom(maze, x, i);
        if(!room)
            return;
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
    printBorder(maze, 0, U);
    for(int i = 0; i < maze->row; i++){
        printRoom(maze, i);
        printBorder(maze, i, D);
    }

}

bool isRoom(Maze maze, int x, int y){
    return x >=0 && x < maze->row && y >= 0 && y < maze->col;
}

Room getRoom(Maze maze, int x, int y){
    if(isRoom(maze, x, y))
        return &maze->matrix[maze->col * x + y];
    else
        return NULL;
}

void Maze_setMark(Room room, char m){
    if(room)
        room->mark = m;
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
