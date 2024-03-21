#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "../terrain/terrain.h"
#include "../dj/dj.h"
#include "../turn/turn.h"

#include <ncurses.h>
#define BOARD_X 401
#define BOARD_Y 401
#define WIDTH 80
#define HEIGHT 24




int main(int argc, char *argv[])
{
    initscr();
    cbreak();
    noecho();
    refresh();
    set_escdelay(0);
   
    int npc_count = 10;
    for(int i = 0; i < argc; i++)
    {
        if(strcmp(argv[i],"--numtrainers") == 0)
            {
                npc_count = atoi(argv[i+1]);
            }
    }

    heapNode_t* npc_arr[npc_count+1];

    //creating board
    board bd;

    int hiker_cost_map[X_MAG][Y_MAG];
    int rival_cost_map[X_MAG][Y_MAG];
    int pc_cost_map[X_MAG][Y_MAG]; 


    int rival_dij_map[X_MAG][Y_MAG];
    int hiker_dij_map[X_MAG][Y_MAG];

    int char_map[X_MAG][Y_MAG];

    for(int i = 0; i < X_MAG; i++)
    {
        for(int j = 0; j < Y_MAG; j++)
        {
            char_map[i][j] = -1;
        }
    }



    //setting board values at null and setting first square/coord
    initBoard(&bd);
    
    initCostMap(bd.board[bd.curX][bd.curY], 
            hiker_cost_map, 
            rival_cost_map,
            pc_cost_map);


    dijkstra(bd.board[bd.curX][bd.curY], hiker_cost_map, rival_cost_map,
            rival_dij_map, hiker_dij_map);

    

    heap_t* heap_t = init_turn_heap(npc_count+1);
    heapNode_t* playerNode = create_npc(0,bd.board[bd.curX][bd.curY]->px,
            bd.board[bd.curX][bd.curY]->py, '@', pc_cost_map, char_map,
            bd.board[bd.curX][bd.curY]->map);

    bd.board[bd.curX][bd.curY]->
        map[bd.board[bd.curX][bd.curY]->px][bd.board[bd.curX][bd.curY]->py] = '@';

    npc_arr[0] = playerNode;
    
    add_npc(heap_t,playerNode);

    for(int i = 1; i <= npc_count; i++)
    {
       bool valid = 0;
       char type; 

       if(i % 2 == 0 || i % 2 == 1)
       {
           type = 'h';
       }
       if(i % 3 == 0)
       {
           if((rand() % 2) + 1 == 1)
           {
               type = 'e';
           }
           else
           {
               type = 'p';
           }
       }
       if(i % 4 == 0)
       {
           type = 'r';
       }
       if(i % 5 == 0)
       {
           if((rand() % 2) + 1 == 1)
           {
               type = 'w';
           }
           else
           {
               type = 's';
           }
       }
       int x;
       int y;
       while(!valid)
       {
           x = (rand() % (75)) + 2;
           y = (rand() % (16)) + 2;


           if(type == 'h')
           {
               if(hiker_cost_map[x][y] != INT16_MAX && char_map[x][y] == -1)
               {
                   valid = 1;
               }
           }
           else
           {
               if(rival_cost_map[x][y] != INT16_MAX && char_map[x][y] == -1)
               {
                   valid = 1;
               }
           }
        }
        heapNode_t* npc;
        if(type == 'h')
        {
            npc = create_npc(i,x,y,type,hiker_cost_map,char_map,bd.board[bd.curX][bd.curY]->map);
        }
        else
        {
            npc = create_npc(i,x,y,type,rival_cost_map,char_map,bd.board[bd.curX][bd.curY]->map);
            
        }
        bd.board[bd.curX][bd.curY]->map[x][y] = type;
        if(type != 's')
        {
        add_npc(heap_t, npc); 
        }
        npc_arr[i] = npc;

    }
    
    
    printSquare(bd.board[bd.curX][bd.curY]);

    const char *responses[5];
    responses[0] = "Wrong input pal, looks like you lose a turn";
    responses[1] = "You can't go there, thats water, you'll drown!";
    responses[2] = "I don't see any climbing gear, so I don't think you can climb that mountain";
    responses[3] = "That's the edge of the world you can't cross that";
    printf("%d", npc_arr[0]->npc->index); 
    int response;
    while(1)
    {
        if (heap_t->arr[0]->npc->type == '@')
        {
            dijkstra(bd.board[bd.curX][bd.curY], hiker_cost_map, rival_cost_map,
                    rival_dij_map, hiker_dij_map);
            response = next_turn(heap_t, bd.board[bd.curX][bd.curY]->map,
                    hiker_cost_map,
                    rival_cost_map,
                    pc_cost_map,
                    char_map, 
                    rival_dij_map,
                    hiker_dij_map,
                    bd.board[bd.curX][bd.curY],
                    npc_arr,
                    npc_count);
            
            

            printSquare(bd.board[bd.curX][bd.curY]);
            if(response != -1)
            {
                mvprintw(0,0,"%s", responses[response]); 
                refresh();
            }
        }
        else
        {
        next_turn(heap_t, bd.board[bd.curX][bd.curY]->map,
                hiker_cost_map,
                rival_cost_map,
                pc_cost_map,
                char_map, 
                rival_dij_map,
                hiker_dij_map,
                bd.board[bd.curX][bd.curY],
                npc_arr,
                npc_count);
        } 

        //huge case switch here

        
       
        //this is for when UH we in a window

        //when displaying trainer list, scroll up if overflow
        //else if(c == KEY_UP)
        //{
        //}
        //when displaying trainer  list, scroll down if overflow
        //else if(c == KEY_DOWN)
        //{}
        //else if(c == 27)
        //{
        //    endwin();
        //    exit(1);
        //}

    }

    

//    int fx;
//    int fy;
//    char c; 
//
    //while(1){
    //    printf("Current location (%d,%d),\nenter option ([q]uit, [n]orth, [s]outh, [e]ast, [w]est, [f]ly): ",bd.curX-200,bd.curY-200);
    //    scanf(" %c", &c);
    //    switch (c)
    //    {
    //         case 'q':
    //            printf("See you later ... quitter\n");
    //            exit(0);
    //            break;
    //         case 'n':
    //            if(bd.curY+1 <= 400)
    //            {
    //                checkTile(&bd,bd.curX,bd.curY+1);
    //                printSquare(bd.board[bd.curX][bd.curY]);
    //                initCostMap(bd.board[bd.curX][bd.curY], hiker_cost_map, rival_cost_map);
    //                printf("\n\n");
    //                dijkstra(bd.board[bd.curX][bd.curY], hiker_cost_map, rival_cost_map);}
    //            else
    //            {
    //                printf("You can't move farther in that direction\n");
    //            }
    //            break;
    //         case 's':
    //            if(bd.curY-1 >= 0)
    //            {
    //                checkTile(&bd,bd.curX,bd.curY-1);
    //                printSquare(bd.board[bd.curX][bd.curY]);
    //                initCostMap(bd.board[bd.curX][bd.curY], hiker_cost_map, rival_cost_map);
    //                printf("\n\n");
    //                dijkstra(bd.board[bd.curX][bd.curY], hiker_cost_map, rival_cost_map);} 
    //            else
    //            {
    //                printf("You can't move farther in that direction\n");
    //            }
    //            break;
    //         case 'e':
    //            if(bd.curX+1 <= 400)
    //            {
    //                checkTile(&bd,bd.curX+1,bd.curY);
    //                printSquare(bd.board[bd.curX][bd.curY]);
    //                initCostMap(bd.board[bd.curX][bd.curY], hiker_cost_map, rival_cost_map);
    //                printf("\n\n");
    //                dijkstra(bd.board[bd.curX][bd.curY], hiker_cost_map, rival_cost_map);
    //            } 
    //            else
    //            {
    //                printf("You can't move farther in that direction\n");
    //            }
    //            break;
    //         case 'w':
    //            if(bd.curX-1 >= 0) 
    //            {
    //                checkTile(&bd,bd.curX-1,bd.curY);
    //                printSquare(bd.board[bd.curX][bd.curY]);
    //            initCostMap(bd.board[bd.curX][bd.curY], hiker_cost_map, rival_cost_map);
    //                printf("\n\n");
    //                dijkstra(bd.board[bd.curX][bd.curY], hiker_cost_map, rival_cost_map);} 
    //            else
    //            {
    //                printf("You can't move farther in that direction\n");
    //            }
    //            break;
    //         case 'f':
    //            printf("enter x: "); 
    //            scanf(" %d", &fx);
    //            printf("enter y: ");
    //            scanf(" %d", &fy);
    //            if(abs(fx) > 200 || abs(fy) > 200)
    //            {
    //                printf("Slow your roll, thats out of bounds\n");
    //                printf("Please enter x and y values under 200\n");
    //            }
    //            else 
    //            {
    //                checkTile(&bd,fx+200,fy+200);
    //                printSquare(bd.board[bd.curX][bd.curY]);
    //                initCostMap(bd.board[bd.curX][bd.curY], hiker_cost_map, rival_cost_map);
    //                printf("\n\n");
    //                dijkstra(bd.board[bd.curX][bd.curY], hiker_cost_map, rival_cost_map);
    //            }
    //            break;
    //        default:
    //            printf("Woah there pal, that not a valid option\n\n");
    //            break;



   //     }

    //}
    return 0;
    
}



//what should this do?
//uhhhhhhhhhhhhhh
// create a board[400][400]
// then check for movement,
// if value of board = null
// then if not clreate a new square with beginning and ending paths
