#include "../terrain/terrain.h"

#ifndef BOARD_H
#define BOARD_H

#define BOARD_X 401
#define BOARD_Y 401

typedef struct board{
    square* board[BOARD_X][BOARD_Y];
    int curX;
    int curY;

} board;

int initBoard(board *bd);
int printCurSquare(board *bd);
int checkTile(board *bd, square *sq);






#endif
