#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "maze.h"
#include "dfs.h"

#define MAXLEN 256
#define MAXDEPTH 5000

char path[MAXDEPTH];
char shortespath[MAXDEPTH];


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
    Maze maze, shortMaze;

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
    if((maze = Maze_new()) ==NULL)
        ;
    if(!Maze_read(maze, MazeFileName)){
        printf("read maze file error\n");
        exit(1);
    }
    //Maze_print_test(maze);
    shortMaze = Maze_new();
    if(isDisplay){
        Maze_display(maze);
        getShortestMaze(maze, Maze_getStart(maze), 0, shortMaze);
        Maze_display(shortMaze);
    }
    if(!getShortestPath(maze, Maze_getStart(maze), 0, path, shortespath)){
        printf("Can't find path from start to end\n");
        exit(1);
    }
    if(!Maze_write(shortespath, SolutionFileName)){
        printf("write maze file error\n");
        exit(1);
    }
    else{
        printf("Write SolutionFile Success\n");
    }




    exit(0);


}
