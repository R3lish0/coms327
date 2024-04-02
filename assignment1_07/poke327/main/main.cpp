#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <cstdlib>
#include <ncurses.h>

#include "../terrain/terrain.h"
#include "../turn/turn.h"
#include "../data/data.h"

using namespace std;


#define BOARD_X 401
#define BOARD_Y 401
#define WIDTH 80
#define HEIGHT 24




int main(int argc, char *argv[])
{
    
//    initscr();
//    cbreak();
//    noecho();
//    refresh();
//    set_escdelay(0);
   
//    int npc_count = 10;
//    for(int i = 0; i < argc; i++)
//    {
//        if(strcmp(argv[i],"--numtrainers") == 0)
//            {
//                npc_count = atoi(argv[i+1]);
//            }
//    }

    

    //creating board
//    board bd;
//
//    int hiker_cost_map[X_MAG][Y_MAG];
//    int rival_cost_map[X_MAG][Y_MAG];
//    int pc_cost_map[X_MAG][Y_MAG]; 
//
//
//    int rival_dij_map[X_MAG][Y_MAG];
//    int hiker_dij_map[X_MAG][Y_MAG];
//
//
//    heap_t* queue_array[BOARD_X][BOARD_Y];
//    heapNode_t** npc_arr_board[BOARD_X][BOARD_Y];
    
    string env_home = "HOME";
    
    string value;

    value = std::getenv(env_home.c_str());

    cout << value << endl;

    //looks for files in ~/.poke327/ 
    if(check_file("/share/poke327/bingle.txt"))
    {
        get_data("/share/poke327/bingle.txt");

    }
   
    //Looks for files in ~/.poke327/
    if(check_file(value + "/.poke327/bingle.txt"))
    {
        get_data(value + "/.poke327/bingle.txt");
    }
    else
    {
        cout << "bingus" << endl;
    }


    //setting board values at null and setting first square/coord

//    initBoard(&bd);
//        
//    init_new_square(&bd, hiker_cost_map, hiker_dij_map,
//            rival_cost_map, rival_dij_map,
//            pc_cost_map, npc_arr_board,
//            queue_array, npc_count);
//
    
    
    
    //printSquare(bd.board[bd.curX][bd.curY]);

    //mvprintw(22,0,"%d, %d", bd.curX,bd.curY); 
//    const char *responses[6];
//    responses[0] = "Wrong input pal, looks like you lose a turn";
//    responses[1] = "You can't go there, thats water, you'll drown!";
//    responses[2] = "I don't see any climbing gear, so I don't think you can climb that mountain";
//    responses[3] = "That's the edge of the world you can't cross that";
//    responses[4] = "You need to be at a gate to travel";
//    responses[5] = "";
//    int response;

//    while(1)
//    {
//
//
//        if (queue_array[bd.curX][bd.curY]->arr[0]->h_npc->type == '@')
//        {
//            response = next_turn(queue_array[bd.curX][bd.curY], bd.board[bd.curX][bd.curY]->map,
//                    hiker_cost_map,
//                    rival_cost_map,
//                    pc_cost_map,
//                    rival_dij_map,
//                    hiker_dij_map,
//                    bd.board[bd.curX][bd.curY],
//                    npc_arr_board,
//                    npc_count,
//                    &bd,
//                    queue_array);
//            dijkstra(bd.board[bd.curX][bd.curY], hiker_cost_map, rival_cost_map,
//                    rival_dij_map, hiker_dij_map);
//
//            printSquare(bd.board[bd.curX][bd.curY]);
//            mvprintw(22,0,"%d, %d", bd.curX,bd.curY); 
//            if(response != -1)
//            {
//                    mvprintw(0,0,"%s", responses[response]); 
//                    refresh();
//            }
//            //turn over here
//           
//        }
//        else
//        {
//            next_turn(queue_array[bd.curX][bd.curY], bd.board[bd.curX][bd.curY]->map,
//                    hiker_cost_map,
//                    rival_cost_map,
//                    pc_cost_map,
//                    rival_dij_map,
//                    hiker_dij_map,
//                    bd.board[bd.curX][bd.curY],
//                    npc_arr_board, 
//                    npc_count,
//                    &bd,
//                    queue_array);
//        } 
////        switch (c)
////        {
////            case 'q':
////                printf("See you later ... quitter\n");
////                exit(0);
////                break;
////            case 'n':
////                if(bd.curY+1 <= 400)
////                {
////                    checkTile(&bd,bd.curX,bd.curY+1);
////                    printSquare(bd.board[bd.curX][bd.curY]);
////                    initCostMap(bd.board[bd.curX][bd.curY], hiker_cost_map, rival_cost_map);
////                    printf("\n\n");
////                    dijkstra(bd.board[bd.curX][bd.curY], hiker_cost_map, rival_cost_map);}
////                else
////                {
////                    printf("You can't move farther in that direction\n");
////                }
////                break;
////            case 's':
////                if(bd.curY-1 >= 0)
////                {
////                    checkTile(&bd,bd.curX,bd.curY-1);
////                    printSquare(bd.board[bd.curX][bd.curY]);
////                    initCostMap(bd.board[bd.curX][bd.curY], hiker_cost_map, rival_cost_map);
////                    printf("\n\n");
////                    dijkstra(bd.board[bd.curX][bd.curY], hiker_cost_map, rival_cost_map);} 
////                else
////                {
////                    printf("You can't move farther in that direction\n");
////                }
////                break;
////            case 'e':
////                if(bd.curX+1 <= 400)
////                {
////                    checkTile(&bd,bd.curX+1,bd.curY);
////                    printSquare(bd.board[bd.curX][bd.curY]);
////                    initCostMap(bd.board[bd.curX][bd.curY], hiker_cost_map, rival_cost_map);
////                    printf("\n\n");
////                    dijkstra(bd.board[bd.curX][bd.curY], hiker_cost_map, rival_cost_map);
////                } 
////                else
////                {
////                    printf("You can't move farther in that direction\n");
////                }
////                break;
////            case 'w':
////                if(bd.curX-1 >= 0) 
////                {
////                    checkTile(&bd,bd.curX-1,bd.curY);
////                    printSquare(bd.board[bd.curX][bd.curY]);
////                    initCostMap(bd.board[bd.curX][bd.curY], hiker_cost_map, rival_cost_map);
////                    printf("\n\n");
////                    dijkstra(bd.board[bd.curX][bd.curY], hiker_cost_map, rival_cost_map);} 
////                else
////                {
////                    printf("You can't move farther in that direction\n");
////                }
////                break;
////            case 'f':
////                printf("enter x: "); 
////                scanf(" %d", &fx);
////                printf("enter y: ");
////                scanf(" %d", &fy);
////                if(abs(fx) > 200 || abs(fy) > 200)
////                {
////                    printf("Slow your roll, thats out of bounds\n");
////                    printf("Please enter x and y values under 200\n");
////                }
////                else 
////                {
////                    checkTile(&bd,fx+200,fy+200);
////                    printSquare(bd.board[bd.curX][bd.curY]);
////                    initCostMap(bd.board[bd.curX][bd.curY], hiker_cost_map, rival_cost_map);
////                    printf("\n\n");
////                    dijkstra(bd.board[bd.curX][bd.curY], hiker_cost_map, rival_cost_map);
////                }
////                break;
////            default:
////                printf("Woah there pal, that not a valid option\n\n");
////                break;
////
//
//    }

    return 0;
    
}



// if value of board = null
// then if not clreate a new square with beginning and ending paths
