#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "../terrain/terrain.h"
#include "../dj/dj.h"

#define BOARD_X 401
#define BOARD_Y 401

int main()
{
    //creating board
    board bd;
    //setting board values at null and setting first square/coord
    initBoard(&bd);
    

    initCostMap(&bd);


    printSquare((bd.board[bd.curX][bd.curY]));
    
    int fx;
    int fy;
    char c;
    while(1){
        printf("Current location (%d,%d),\nenter option ([q]uit, [n]orth, [s]outh, [e]ast, [w]est, [f]ly): ",bd.curX-200,bd.curY-200);
        scanf(" %c", &c);
        switch (c)
        {
             case 'q':
                printf("See you later ... quitter\n");
                exit(0);
                break;
            case 'n':
                if(bd.curY+1 <= 400)
                {
                checkTile(&bd,bd.curX,bd.curY+1);
                printSquare(bd.board[bd.curX][bd.curY]);
                }
                else
                {
                    printf("You can't move farther in that direction\n");
                }
                break;
            case 's':
                if(bd.curY-1 >= 0)
                {
                    checkTile(&bd,bd.curX,bd.curY-1);
                    printSquare(bd.board[bd.curX][bd.curY]);
                } 
                else
                {
                    printf("You can't move farther in that direction\n");
                }
                break;
            case 'e':
                if(bd.curX+1 <= 400)
                {
                checkTile(&bd,bd.curX+1,bd.curY);
                printSquare(bd.board[bd.curX][bd.curY]);
                } 
                else
                {
                    printf("You can't move farther in that direction\n");
                }
                break;
            case 'w':
                if(bd.curX-1 >= 0) 
                {
                checkTile(&bd,bd.curX-1,bd.curY);
                printSquare(bd.board[bd.curX][bd.curY]);
                } 
                else
                {
                    printf("You can't move farther in that direction\n");
                }
                break;
            case 'f':
                printf("enter x: "); 
                scanf(" %d", &fx);
                printf("enter y: ");
                scanf(" %d", &fy);
                if(abs(fx) > 200 || abs(fy) > 200)
                {
                    printf("Slow your roll, thats out of bounds\n");
                    printf("Please enter x and y values under 200\n");
                }
                else 
                {
                    checkTile(&bd,fx+200,fy+200);
                    printSquare(bd.board[bd.curX][bd.curY]);
                }
                break;
            default:
                printf("Woah there pal, that not a valid option\n\n");
                break;



        }

    }

    return 0;
    
}



//what should this do?
//uhhhhhhhhhhhhhh
// create a board[400][400]
// then check for movement,
// if value of board = null
// then if not clreate a new square with beginning and ending paths
