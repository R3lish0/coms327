#include <unistd.h>
#include <cstdlib>
#include <ncurses.h>
#include <vector>
#include <string.h>

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


    //create a for loop for finding files
    //
    //for(dataType in dataArr)
    //check
    //get
    //
    //
    string filenames[] = {"pokemon", "moves", "pokemon_moves", 
        "pokemon_species","experience", "type_names", 
        "pokemon_stats", "stats", "pokemon_types"};

    vector<pokemon*> pokemon_vec;
    vector<moves*> moves_vec;
    vector<pokemon_moves*>  pokemon_moves_vec;
    vector<pokemon_species*> species_vec;
    vector<experience*> exp_vec;
    vector<type_names*> type_name_vec;
    vector<pokemon_stats*> pokemon_stat_vec;
    vector<stats*>  stats_vec;
    vector<pokemon_types*> pokemon_types_vec;


    int i;
    string path;
    for(i = 0; i < 9; i++)
    {
        if(check_file(value + "/.poke327/pokedex/pokedex/data/csv/" + filenames[i] + ".csv"))
        {
            path = value + "/.poke327/pokedex/pokedex/data/csv/"+ filenames[i] + ".csv";
            switch (i)
            {

                case 0:
                    get_pokemon_data(path, pokemon_vec);
                    break;
                case 1:
                    get_moves_data(path, moves_vec);
                    break;
                case 2:
                    get_pokemon_moves_data(path, pokemon_moves_vec);
                    break;
                case 3:
                    get_pokemon_species_data(path, species_vec);
                    break;
                case 4:
                    get_exp_data(path,exp_vec);
                    break;
                case 5:
                    get_type_name_data(path, type_name_vec);
                    break;
                case 6:
                    get_pokemon_stats_data(path, pokemon_stat_vec);
                    break;
                case 7:
                    get_stats_data(path, stats_vec);
                    break;
                case 8:
                    get_pokemon_types_data(path, pokemon_types_vec);
            }
        }
        else if(check_file("/share/cs327/pokedex/pokedex/data/csv/"+ filenames[i] + ".csv"))
        {
            path = "/share/cs327/pokedex/pokedex/data/csv/"+ filenames[i] + ".csv";
            switch (i)
            {

                case 0:
                    get_pokemon_data(path, pokemon_vec);
                    break;
                case 1:
                    get_moves_data(path, moves_vec);
                    break;
                case 2:
                    get_pokemon_moves_data(path, pokemon_moves_vec);
                    break;
                case 3:
                    get_pokemon_species_data(path, species_vec);
                    break;
                case 4:
                    get_exp_data(path,exp_vec);
                    break;
                case 5:
                    get_type_name_data(path, type_name_vec);
                    break;
                case 6:
                    get_pokemon_stats_data(path, pokemon_stat_vec);
                    break;
                case 7:
                    get_stats_data(path, stats_vec);
                    break;
                case 8:
                    get_pokemon_types_data(path, pokemon_types_vec);
            }
            
        }  
        else
            {
                cerr << filenames[i] << ".csv not found in either of the expected places"
                    << "\n/share/cs327/pokedex/pokedex/data/csv/"<< 
                    "\nor\n$HOME/.poke327/pokedex/pokedex/data/csv/ \n\n";
                exit(1);
            }
    }


   // int npc_count = 10;
    for(int i = 0; i < argc; i++)
    {
        if(strcmp(argv[i],"--numtrainers") == 0)
        {
    //        npc_count = atoi(argv[i+1]);
        }
        else if(strcmp(argv[i],"--pokemon") == 0)
        {
            print_pokemon_data(pokemon_vec);
        }
        else if(strcmp(argv[i],"--moves") == 0)
        { 
            print_moves_data(moves_vec);
        }
        else if(strcmp(argv[i],"--pokemon_moves") == 0)
        {
            print_pokemon_moves_data(pokemon_moves_vec);
        }
        else if(strcmp(argv[i],"--pokemon_species") == 0)
        {
            print_pokemon_species_data(species_vec);
        }
        else if(strcmp(argv[i],"--experience") == 0)
        {
            print_exp_data(exp_vec);
        }
        else if(strcmp(argv[i],"--type_names") == 0)
        {
            print_type_name_data(type_name_vec);
        }
        else if(strcmp(argv[i],"--pokemon_stats") == 0)
        {
            print_pokemon_stats_data(pokemon_stat_vec);
        }
        else if(strcmp(argv[i],"--stats") == 0)
        {
            print_stats_data(stats_vec);
        }
        else if(strcmp(argv[i],"--pokemon_types") == 0)
        {
            print_pokemon_types_data(pokemon_types_vec);
        }
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
