#include "../terrain/terrain.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define BOARD_X 401
#define BOARD_Y 401


int initBoard(board *bd)
{
    //init starting square 
    square sq;
    genSquare(&sq,0,0,0,0);
    //lets init a board
    for(int i = 0; i < BOARD_X; i++)
    {
        for(int j = 0; j < BOARD_Y; j++)
        {
            bd->board[i][j] = NULL;
        }
    }
    bd->curX = 200;
    bd->curY = 200;

    bd->board[200][200] = &sq;

    return 0;
}
