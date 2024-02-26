#include "../queue/queue.h"

#ifndef TERRAIN_H
#define TERRAIN_H

#define X_MAG 80
#define Y_MAG 21

#define BOARD_X 401
#define BOARD_Y 401


typedef struct square{
    char map[X_MAG][Y_MAG];
    int n;
    int s;
    int e;
    int w;
    int px;
    int py;
} square;

typedef struct seeds{
    int seedLocations[6][2]; 
} seeds;


typedef struct board{
    square* board[BOARD_X][BOARD_Y];
    int curX;
    int curY;

} board;

int initBoard(board *bd);
int printCurSquare(board *bd);
int checkTile(board *bd, int x, int y);


void printSquare(square *sq);
void seedGen(seeds *sd, square *sq);
int checkSquare(queue *q, square *sq, int offsetX, int offsetY);
int grow(seeds *sd, square *sq);
int manMade(square *sq, int pk);
int genSquare(square *sq, int n, int s, int e, int w, int pk);




#endif
