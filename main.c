#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "maze.h"

#define MAXLEN 1024
extern int ROW, COL;  //maze row and col
extern int sx, sy, ex, ey; //the (sx, sy) is start point (ex, ey) is end point
extern int** maze;


void usage(){
    printf("usage: maze [-d] MazeFileName SolutionFileName\n");
    printf("\t-d is optional to display the Maze\n");
    printf("\tMazeFileName is the name of maze file that should be read\n");
    printf("\tSolutionFileName is the name of the file in which should be stored\n");
}

int main(int argc, char* argv[]){
    //maze source filename, and output filename
    char MazeFileName[MAXLEN], SolutionFileName[MAXLEN];
    //display the maze or not; default false; use -d to open it
    bool isDisplay = false;
    //check argc
    if(argc == 3){
        strncpy(MazeFileName, argv[1], MAXLEN);
        strncpy(SolutionFileName, argv[2], MAXLEN);
    }
    else if(argc == 4){
        isDisplay = strcmp(argv[1], "-d") == 0;
        strncpy(MazeFileName, argv[2], MAXLEN);
        strncpy(SolutionFileName, argv[3], MAXLEN);
    }
    else{
        usage();
        exit(1);
    }
    FILE *MazeFile, *SolutionFile;
    if((MazeFile = fopen(MazeFileName, "r")) == NULL){
        printf("Maze File can't read");
        exit(1);
    }
    if(!read_maze(MazeFile, maze)){
        printf("read maze file error\n");
        exit(1);
    }
    //just for test
    /*
    for(int i =0;i < ROW; i++){
        for(int j = 0; j < COL; j++){
            printf("%d ", maze[i][j]);
        }
        printf("\n");
    }
    */
    display_maze(ROW, COL, maze);



    printf("OK\n");
    exit(0);


}
