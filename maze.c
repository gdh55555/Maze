#include "maze.h"

int ROW, COL;  //maze row and col
int sx, sy, ex, ey; //the (sx, sy) is start point (ex, ey) is end point
int** maze;

void display_maze(int ROW, int COL, int** mptr){
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

bool read_maze(FILE* MazeFile, int** mptr ){
    if(fscanf(MazeFile, "%d %d", &ROW, &COL) != 2)
        return false;
    if(fscanf(MazeFile, "%d %d", &sx, &sy) != 2)
        return false;
    if(fscanf(MazeFile, "%d %d", &ex, &ey) != 2)
        return false;
    maze = alloc_maze(ROW, COL, 0, mptr);
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

int** alloc_maze(int ROW, int COL, int i, int** mptr){
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
