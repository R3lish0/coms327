#include <unistd.h>
#include <stdio.h>
#include "../terrain/terrain.h"

#define BOARD_X 401
#define BOARD_Y 401

int main()
{
    square sq;
    genSquare(&sq, 0, 0, 0, 0);

    //square board[BOARD_X][BOARD_Y];
    
    return 0;
}



//what should this do?
//uhhhhhhhhhhhhhh
// create a board[400][400]
// then check for movement,
// if value of board = null
// then if not clreate a new square with beginning and ending paths
