#include "../board/board.h"
#include "../terrain/terrain.h"



#define BOARD_X 401
#define BOARD_Y 401

int initBoard(board *bd)
{
    square sq;
    
    genSquare(&sq,0,0,0,0);  
    bd->board[200][200] = &sq;

    return 0;
}
