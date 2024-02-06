#include <unistd.h>
#include <stdio.h>
#include "../terrain/terrain.h"

#define BOARD_X 401
#define BOARD_y 401

int main()
{
    struct square sq;
    genMap(&sq, 0, 0, 0, 0);

    struct square board[BOARD_X][BOARD_Y]
    
    return 0;
}



//what should this do?
//uhhhhhhhhhhhhhh
// create a board[400][400]
// then check for movement,
// if value of board = null
// then if not create a new square with beginning and ending paths
