#include <unistd.h>
#include <cstdlib>
#include <ncurses.h>
#include <vector>
#include <string.h>
#include <algorithm>
#include <iostream>

#include "../terrain/terrain.h"
#include "../turn/turn.h"
#include "../data/data.h"
#include "../dj/dj.h"
#include "../main/main.h"

using namespace std;


#define BOARD_X 401
#define BOARD_Y 401
#define WIDTH 80
#define HEIGHT 24


int player_bag[3] = {10,10,10};
int player_team[6] = {-1,-1,-1,-1,-1,-1};
 

int gen_pokemon(std::vector<saved_poke*>& poke_list,
        vector<moves*>& moves_vec, vector<pokemon_moves*>& pokemon_moves_vec,
        vector<pokemon*>& pokemon_vec, vector<pokemon_stats*>& pokemon_stats_vec,
        int level, vector<pokemon_types*>& pokemon_types_vec)
{
    saved_poke* new_poke = new saved_poke();

    new_poke->index = poke_list.size();
    new_poke->level = level;
    new_poke->iv_hp = rand() % 15 + 1;
    new_poke->iv_attack = rand() % 15 + 1;
    new_poke->iv_defense = rand() % 15 + 1;
    new_poke->iv_speed = rand() % 15 + 1;
    new_poke->iv_special_attack = rand() % 15 + 1;
    new_poke->iv_special_defense = rand() % 15 + 1;
    new_poke->is_shiny = (rand() % 8192 == 0) ? 0 : 1;
    new_poke->gender = (rand()%2 == 1 ? 'M' : 'F');
    
    //gen the pokemon
    new_poke->poke = pokemon_vec.at(rand() % pokemon_vec.size());

    for(long unsigned int i = 0; i < pokemon_stats_vec.size(); i++)
    {
        if(pokemon_stats_vec.at(i)->pokemon_id == new_poke->poke->id)
        {
            new_poke->hp = pokemon_stats_vec.at(i)->base_stat + new_poke->iv_hp;
            new_poke->attack = pokemon_stats_vec.at(i+1)->base_stat + new_poke->iv_attack;
            new_poke->defense = pokemon_stats_vec.at(i+2)->base_stat + new_poke->iv_defense;
            new_poke->special_attack = pokemon_stats_vec.at(i+3)->base_stat + new_poke->iv_special_attack;
            new_poke->special_defense = pokemon_stats_vec.at(i+4)->base_stat + new_poke->iv_special_defense;
            new_poke->speed = pokemon_stats_vec.at(i+5)->base_stat + new_poke->iv_speed;

            new_poke->curr_hp = new_poke->hp;
            new_poke->curr_attack = new_poke->attack;
            new_poke->curr_defense = new_poke->defense;
            new_poke->curr_special_attack = new_poke->special_attack;
            new_poke->curr_special_defense = new_poke->special_defense;
            new_poke->curr_speed = new_poke->speed;

            

            i = pokemon_stats_vec.size();
        }
    }
    for(long unsigned int j = 0; j < pokemon_types_vec.size(); j++)
    {
        if(new_poke->poke->id == pokemon_types_vec.at(j)->pokemon_id)
        {
            new_poke->type_id.push_back(pokemon_types_vec.at(j)->type_id);
        }
    }

    
    
    //gen the movelist
    vector<int> viable_moves;
    long unsigned int i;
    for(i = 0; i < pokemon_moves_vec.size(); i++)
    {
        pokemon_moves* curr_move = pokemon_moves_vec.at(i);  

      if(curr_move->pokemon_id == new_poke->poke->species_id)
      {
          if(curr_move->pokemon_move_method_id == 1)
          {
              if(curr_move->level <= new_poke->level)
              {
                  int cnt = count(viable_moves.begin(),viable_moves.end(), pokemon_moves_vec.at(i)->move_id);
                  if (cnt == 0)
                  {
                      viable_moves.push_back(pokemon_moves_vec.at(i)->move_id);
                  }
              }
          }
      }

    }
    
    if(viable_moves.size() == 0)
    {
        //little rat gets struggle
        new_poke->move_list.push_back(moves_vec.at(165));
    }
    else if(viable_moves.size() == 1)
    {
        new_poke->move_list.push_back(moves_vec.at(viable_moves.at(0) + 1));
    }
    else
    {
        int moves = 0;
        int taken[2];
        while(moves != 2)
        {
            int viable_index = rand() % viable_moves.size();
            if(moves != 0)
            {
                if(viable_moves.at(viable_index) != taken[0])
                {
                    new_poke->move_list.push_back(moves_vec.at(viable_moves.at(viable_index)+ 1));
                    moves++;
                }
                
            }
            else
                {
                    
                    taken[0] = viable_moves.at(viable_index);
                    new_poke->move_list.push_back(moves_vec.at(viable_moves.at(viable_index)+ 1));
                    moves++;
                }
        }
    }
    poke_list.push_back(new_poke);
    return  new_poke->index;
}


    




int main(int argc, char *argv[])
{
    
    initscr();
    cbreak();
    noecho();
    //    nodelay(stdscr, TRUE);
    refresh();
    start_color();
    set_escdelay(0);
   
    

    

    //creating board
    board bd;

    int hiker_cost_map[X_MAG][Y_MAG];
    int rival_cost_map[X_MAG][Y_MAG];
    int pc_cost_map[X_MAG][Y_MAG]; 


    int rival_dij_map[X_MAG][Y_MAG];
    int hiker_dij_map[X_MAG][Y_MAG];


    heap_t* queue_array[BOARD_X][BOARD_Y];
    heapNode_t** npc_arr_board[BOARD_X][BOARD_Y];

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
    vector<saved_poke*> saved_poke_list;


   
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


    int npc_count = 10;
    for(int i = 0; i < argc; i++)
    {
        if(strcmp(argv[i],"--numtrainers") == 0)
        {
            npc_count = atoi(argv[i+1]);
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

    initBoard(&bd);
        
    init_new_square(&bd, hiker_cost_map, hiker_dij_map,
            rival_cost_map, rival_dij_map,
            pc_cost_map, npc_arr_board,
            queue_array, npc_count);

    add_npc(queue_array[bd.curX][bd.curY],npc_arr_board[bd.curX][bd.curY][0]);
    
    
    printSquare(bd.board[bd.curX][bd.curY]);

    for(int i = 0; i < 3; i++)
    {
        gen_pokemon(saved_poke_list,
                moves_vec, pokemon_moves_vec,
                pokemon_vec, pokemon_stat_vec,
                5, pokemon_types_vec);
    
    }
       

    








    mvprintw(22,0,"%d, %d", bd.curX-200,bd.curY-200); 
    const char *responses[6];
    responses[0] = "Wrong input pal, looks like you lose a turn";
    responses[1] = "You can't go there, thats water, you'll drown!";
    responses[2] = "I don't see any climbing gear, so I don't think you can climb that mountain";
    responses[3] = "That's the edge of the world you can't cross that";
    responses[4] = "You need to be at a gate to travel";
    responses[5] = "";
    int response;


    refresh();

    int pokemon_choice = '1';
    int cur_pokemon = 1;

    WINDOW * pick = newwin(15,52,5,15);
    int in_menu = 1;
    while(in_menu)
    {
        if(pokemon_choice - '0' <= 3 && pokemon_choice - '0' > 0) 
        {
            cur_pokemon = pokemon_choice - '0';
            werase(pick);
            wprintw(pick, "Choose Your Pokemon!! "); 
            wprintw(pick, "Press Y to accept \nAnd 1,2,3 to view possible Pokemon");     
            pokemon_choice = pokemon_choice - '0';
            mvwprintw(pick, 3,0,"%s", saved_poke_list.at(pokemon_choice - 1)->poke->identifier.c_str());     
            mvwprintw(pick, 3,20,"Level: %d", saved_poke_list.at(pokemon_choice - 1)->level);     
            mvwprintw(pick, 4,20,"Gender: %c", saved_poke_list.at(pokemon_choice - 1)->gender);     
            mvwprintw(pick, 4,0,"Shiny: %s", saved_poke_list.at(pokemon_choice - 1)->is_shiny != 0 ? "no" : "yes");     
            mvwprintw(pick, 5,20,"Hp: %d", saved_poke_list.at(pokemon_choice - 1)->hp);     
            mvwprintw(pick, 5,0,"Attack: %d", saved_poke_list.at(pokemon_choice - 1)->attack);     
            mvwprintw(pick, 6,20,"Defense: %d", saved_poke_list.at(pokemon_choice - 1)->defense);     
            mvwprintw(pick, 6,0,"Speed: %d", saved_poke_list.at(pokemon_choice - 1)->speed);     
            mvwprintw(pick, 7,20,"Special Attack: %d", saved_poke_list.at(pokemon_choice - 1)->special_attack);     
            mvwprintw(pick, 7,0,"Special Defense: %d", saved_poke_list.at(pokemon_choice - 1)->special_defense);     

            wprintw(pick, "\n\nMoves:");     
            for(long unsigned int i = 0; i < saved_poke_list.at(pokemon_choice -1)->
                    move_list.size(); i++)
            {
                wprintw(pick, "\n%s", saved_poke_list.at(pokemon_choice - 1)->move_list.at(i)->identifier.c_str());     
            }
            pokemon_choice = wgetch(pick);

        }
        else if(pokemon_choice == 'y' || pokemon_choice == 'Y')
        {

            npc_arr_board[bd.curX][bd.curY][0]->h_npc->team[0] = cur_pokemon-1;

            in_menu = 0;
            endwin();
        }
        else
        {
            pokemon_choice = wgetch(pick);
        }


    }




    printSquare(bd.board[bd.curX][bd.curY]);
    mvprintw(22,0,"%d, %d", bd.curX-200,bd.curY-200); 
    refresh();


    while(1)
    {


        if (queue_array[bd.curX][bd.curY]->arr[0]->h_npc->type == '@')
        {
            for(int i = 0; i < 6; i++)
            {
                player_team[i] = queue_array[bd.curX][bd.curY]->arr[0]->h_npc->team[i];
            }
            for(int i = 0; i < 3; i++)
            {
                player_bag[i] = queue_array[bd.curX][bd.curY]->arr[0]->h_npc->bag[i];

            }
            printSquare(bd.board[bd.curX][bd.curY]);

            mvprintw(22,0,"%d, %d", bd.curX-200,bd.curY-200);

            response = next_turn(queue_array[bd.curX][bd.curY], bd.board[bd.curX][bd.curY]->map,
                    hiker_cost_map,
                    rival_cost_map,
                    pc_cost_map,
                    rival_dij_map,
                    hiker_dij_map,
                    bd.board[bd.curX][bd.curY],
                    npc_arr_board,
                    npc_count,
                    &bd,
                    queue_array,saved_poke_list,
                    moves_vec, pokemon_moves_vec,
                    pokemon_vec, pokemon_stat_vec,
                    pokemon_types_vec);


            dijkstra(bd.board[bd.curX][bd.curY], hiker_cost_map, rival_cost_map,
                    rival_dij_map, hiker_dij_map);
             
           
            add_npc(queue_array[bd.curX][bd.curY],npc_arr_board[bd.curX][bd.curY][0]);

           //turn over here
            if(response != -1)
            {
                    mvprintw(0,0,"%s", responses[response]); 
                    refresh();
            } 
        }
        else
        {
            next_turn(queue_array[bd.curX][bd.curY], bd.board[bd.curX][bd.curY]->map,
                    hiker_cost_map,
                    rival_cost_map,
                    pc_cost_map,
                    rival_dij_map,
                    hiker_dij_map,
                    bd.board[bd.curX][bd.curY],
                    npc_arr_board, 
                    npc_count,
                    &bd,
                    queue_array ,saved_poke_list,
                    moves_vec, pokemon_moves_vec,
                    pokemon_vec, pokemon_stat_vec,
                    pokemon_types_vec);
        } 
    }

    return 0;
    
}



// if value of board = null
// then if not clreate a new square with beginning and ending paths
