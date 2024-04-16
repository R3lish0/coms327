//check out this super cool C file
//
//ok here's what I have to do
//
//First create a heap 
//then get next move all characters and add them to heap
//then go through the heap and select next move for each character
//
//Things to consider
//
//characters cannot collide
//
//we need to check depending on character
//  If we need to do something like uhh turn around (we need turn function)
//
//  sentries might be a little hard to be honest
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ncurses.h>
#include <unistd.h>
#include <string>

#include "../turn/turn.h"
#include "../terrain/terrain.h"
#include "../dj/dj.h"
#include "../data/data.h"

using namespace std;

// Define a createHeap function
heap_t* createHeap_t(int capacity)
{
    // Allocating memory to heap h
    heap_t* h = (heap_t*)malloc(sizeof(heap_t));
 
    // Checking if memory is allocated to h or not
    if (h == NULL) {
        printf("Memory error");
        return NULL;
    }
    // set the values to size and capacity
    h->size = 0;
    h->capacity = capacity;
 
    // Allocating memory to array
    h->arr = (heapNode_t**)malloc(capacity * sizeof(heapNode_t*));
 
    // Checking if memory is allocated to h or not
    if (h->arr == NULL) {
        printf("Memory error");
        return NULL;
    }
    int i = 0; 
    h->size = i;
    i = (h->size - 2) / 2;
    while (i >= 0) {
        heapify_t(h, i);
        i--;
    }
    return h;
}
 
// Defining insertHelper function
void insertHelper_t(heap_t* h, int index)
{
 
    // Store parent of element at index
    // in parent variable
    int parent = (index - 1) / 2;
 
    if (h->arr[parent]->h_npc->cost > h->arr[index]->h_npc->cost) {
        // Swapping when child is smaller
        // than parent element
        heapNode_t* temp = h->arr[parent];
        h->arr[parent] = h->arr[index];
        h->arr[index] = temp;
 
        // Recursively calling insertHelper
        insertHelper_t(h, parent);
    }
}
 
void heapify_t(heap_t* h, int index)
{
    int left = index * 2 + 1;
    int right = index * 2 + 2;
    int min = index;
 
    // Checking whether our left or child element
    // is at right index or not to avoid index error
    if (left >= h->size || left < 0)
        left = -1;
    if (right >= h->size || right < 0)
        right = -1;
 
    // store left or right element in min if
    // any of these is smaller that its parent
    if (left != -1 && h->arr[left]->h_npc->cost < h->arr[index]->h_npc->cost)
        min = left;
    if (right != -1 && h->arr[right]->h_npc->cost < h->arr[min]->h_npc->cost)
        min = right;
 
    // Swapping the nodes
    if (min != index) {
        heapNode_t* temp = h->arr[min];
        h->arr[min] = h->arr[index];
        h->arr[index] = temp;
 
        // recursively calling for their child elements
        // to maintain min heap
        heapify_t(h, min);
    }
}
 
heapNode_t* extractMin_t(heap_t* h)
{
    heapNode_t* deleteItem;
 
    // Checking if the heap is empty or not
    if (h->size == 0) {
        printf("\nHeap id empty.");
        return NULL;
    }
 
    // Store the node in deleteItem that
    // is to be deleted.
    deleteItem = h->arr[0];
 
    // Replace the deleted node with the last node
    h->arr[0] = h->arr[h->size - 1];
    // Decrement the size of heap
    h->size--;
 
    // Call minheapify_top_down for 0th index
    // to maintain the heap property
    heapify_t(h, 0);
    return deleteItem;
}
 
// Define a insert function
void insert_t(heap_t* h, heapNode_t* hn)
{
 
    // Checking if heap is full or not
    if (h->size < h->capacity) {
        // Inserting data into an array
        h->arr[h->size] = hn;
        // Calling insertHelper function
        insertHelper_t(h, h->size);
        // Incrementing size of array
        h->size++;
    }
}



void battle(npc* p, npc* n, int character_map[X_MAG][Y_MAG],
        vector<saved_poke*>& saved_poke_list,
        std::vector<moves*>& moves_vec, std::vector<pokemon_moves*>& pokemon_moves_vec,
        std::vector<pokemon*>& pokemon_vec, std::vector<pokemon_stats*>& pokemon_stats_vec,
        vector<int>& levels)
{
    WINDOW * menu = newwin(15,52,5,15);
    
    for(long unsigned int i = 0; i < levels.size(); i++)
    {
        n->team[i] = gen_pokemon(saved_poke_list, moves_vec, pokemon_moves_vec, pokemon_vec,
            pokemon_stats_vec, levels.at(i));
    }

    int in_menu = 1;
    long unsigned int pokemon_choice = '1';

    pokemon_choice = pokemon_choice - '0';
    werase(menu);
    wprintw(menu, "You have been challenged to a battle!!\n"); 
    wprintw(menu, "Trainer has %lu pokemon\nCycle through with number keys 1-n", levels.size());     
    mvwprintw(menu, 4,0,"%s", saved_poke_list.at(n->team[pokemon_choice-1])->poke->identifier.c_str());     
    mvwprintw(menu, 4,30,"Level: %d", saved_poke_list.at(n->team[pokemon_choice-1])->level);     
    mvwprintw(menu, 5,30,"Gender: %c", saved_poke_list.at(n->team[pokemon_choice-1])->gender);     
    mvwprintw(menu, 5,0,"Shiny: %s", saved_poke_list.at(n->team[pokemon_choice-1])->is_shiny != 0 ? "no" : "yes");     
    mvwprintw(menu, 6,30,"Hp: %d", saved_poke_list.at(n->team[pokemon_choice-1])->hp);     
    mvwprintw(menu, 6,0,"Attack: %d", saved_poke_list.at(n->team[pokemon_choice-1])->attack);     
    mvwprintw(menu, 7,30,"Defense: %d", saved_poke_list.at(n->team[pokemon_choice-1])->defense);     
    mvwprintw(menu, 7,0,"Speed: %d", saved_poke_list.at(n->team[pokemon_choice-1])->speed);     
    mvwprintw(menu, 8,30,"Special Attack: %d", saved_poke_list.at(n->team[pokemon_choice-1])->special_attack);     
    mvwprintw(menu, 8,0,"Special Defense: %d", saved_poke_list.at(n->team[pokemon_choice-1])->special_defense);     

    wprintw(menu, "\n\nMoves:");     
    for(long unsigned int i = 0; i < saved_poke_list.at(n->team[pokemon_choice-1])->
            move_list.size(); i++)
    {
        wprintw(menu, "\n%s", saved_poke_list.at(n->team[pokemon_choice-1])->move_list.at(i)->identifier.c_str());     
    }
    wprintw(menu, "\n\nPress e to exit");



    while(in_menu)
    {

        pokemon_choice = wgetch(menu);
        if(pokemon_choice - '0' <= levels.size() && pokemon_choice - '0' > 0) 
        {
            pokemon_choice = pokemon_choice - '0';
            werase(menu);
            wprintw(menu, "You have been challenged to a battle!!\n"); 
            wprintw(menu, "Trainer has %lu pokemon\nCycle through with number keys 1-n", levels.size());     
            mvwprintw(menu, 4,0,"%s", saved_poke_list.at(n->team[pokemon_choice-1])->poke->identifier.c_str());     
            mvwprintw(menu, 4,30,"Level: %d", saved_poke_list.at(n->team[pokemon_choice-1])->level);     
            mvwprintw(menu, 5,30,"Gender: %c", saved_poke_list.at(n->team[pokemon_choice-1])->gender);     
            mvwprintw(menu, 5,0,"Shiny: %s", saved_poke_list.at(n->team[pokemon_choice-1])->is_shiny != 0 ? "no" : "yes");     
            mvwprintw(menu, 6,30,"Hp: %d", saved_poke_list.at(n->team[pokemon_choice-1])->hp);     
            mvwprintw(menu, 6,0,"Attack: %d", saved_poke_list.at(n->team[pokemon_choice-1])->attack);     
            mvwprintw(menu, 7,30,"Defense: %d", saved_poke_list.at(n->team[pokemon_choice-1])->defense);     
            mvwprintw(menu, 7,0,"Speed: %d", saved_poke_list.at(n->team[pokemon_choice-1])->speed);     
            mvwprintw(menu, 8,30,"Special Attack: %d", saved_poke_list.at(n->team[pokemon_choice-1])->special_attack);     
            mvwprintw(menu, 8,0,"Special Defense: %d", saved_poke_list.at(n->team[pokemon_choice-1])->special_defense);     

            wprintw(menu, "\n\nMoves:");     
            for(long unsigned int i = 0; i < saved_poke_list.at(n->team[pokemon_choice-1])->
                    move_list.size(); i++)
            {
                wprintw(menu, "\n%s", saved_poke_list.at(n->team[pokemon_choice-1])->move_list.at(i)->identifier.c_str());     
            }
            wprintw(menu, "\n\nPress e to exit");

            
        }
        else if(pokemon_choice == 'E' || pokemon_choice == 'e')
        {
            in_menu = 0;
            n->is_defeated = 1;
            character_map[n->x][n->y] = -1;
            delwin(menu);
        }
    }
}


void pokemon_encounter(vector<saved_poke*>& saved_poke_list,
        std::vector<moves*>& moves_vec, std::vector<pokemon_moves*>& pokemon_moves_vec,
        std::vector<pokemon*>& pokemon_vec, std::vector<pokemon_stats*>& pokemon_stats_vec,
        int level)  
{
    int cur_pokemon = gen_pokemon(saved_poke_list, moves_vec, pokemon_moves_vec, pokemon_vec,
            pokemon_stats_vec, level);

    WINDOW * pick = newwin(15,52,5,15);
    int in_menu = 1;
    char exit;
    while(in_menu)
    {
            werase(pick);
            const char* pokemon = saved_poke_list.at(cur_pokemon)->poke->identifier.c_str();     

            mvwprintw(pick, 0,0,"%s%s%s", "You have encountered a ", pokemon, "!!");     

            mvwprintw(pick, 3,0,"Level: %d", saved_poke_list.at(cur_pokemon)->level);     
            mvwprintw(pick, 4,20,"Gender: %c", saved_poke_list.at(cur_pokemon)->gender);     
            mvwprintw(pick, 4,0,"Shiny: %s", saved_poke_list.at(cur_pokemon)->is_shiny != 0 ? "no" : "yes");     
            mvwprintw(pick, 5,20,"Hp: %d", saved_poke_list.at(cur_pokemon)->hp);     
            mvwprintw(pick, 5,0,"Attack: %d", saved_poke_list.at(cur_pokemon)->attack);     
            mvwprintw(pick, 6,20,"Defense: %d", saved_poke_list.at(cur_pokemon)->defense);     
            mvwprintw(pick, 6,0,"Speed: %d", saved_poke_list.at(cur_pokemon)->speed);     
            mvwprintw(pick, 7,20,"Special Attack: %d", saved_poke_list.at(cur_pokemon)->special_attack);     
            mvwprintw(pick, 7,0,"Special Defense: %d", saved_poke_list.at(cur_pokemon)->special_defense);     

            wprintw(pick, "\n\nMoves:");     
            for(long unsigned int i = 0; i < saved_poke_list.at(cur_pokemon)->
                    move_list.size(); i++)
            {
                wprintw(pick, "\n%s", saved_poke_list.at(cur_pokemon)->move_list.at(i)->identifier.c_str());     
            }
            wprintw(pick, "\n\nPress e to exit");     
            exit = wgetch(pick);
            if(exit == 'e' || exit == 'E')
            {
                in_menu = 0;
                delwin(pick);
            }


    }
}

void fly(int pair[2])
{
    char x[] = "-123";
    char y[] = "-123";
    echo();
    WINDOW * menu = newwin(10,52,5,15);
    wprintw(menu, "Where to?\n\n");
    wprintw(menu, "X-Value: ");
    wgetstr(menu, x);
    werase(menu);
    wrefresh(menu);
    wprintw(menu, "Where to?\n\n");
    wprintw(menu,"Y-Value: ");
    wgetstr(menu, y);
    wrefresh(menu);
    int x_int;
    int y_int;
    noecho();
    werase(menu);
    x_int = std::atoi(x);
    y_int = std::atoi(y);
    mvwprintw(menu,0,0,"%d, %d",x_int,y_int);
    wrefresh(menu);
    pair[0] = x_int;
    pair[1] = y_int;
    delwin(menu);
    
}



void show_trainers(npc* p, heapNode_t** npc_arr, int n)
{
    
    WINDOW * trainer_pad = newpad(6*n,52);
    keypad(trainer_pad,TRUE);
    scrollok(trainer_pad,TRUE); 
    idlok(trainer_pad,TRUE);
    npc* trainer;
    string x_dir;
    string y_dir;
    int x_dist;
    int y_dist;
    string status;
    int mv = 0;

    for(int i = 1; i <= n; i++)
    {
        trainer = npc_arr[i]->h_npc; 
        mvwprintw(trainer_pad,mv,0, "Type of trainer: %c", trainer->type);
        if((p->x - trainer->x) < 0) 
        {
            x_dir = "East";
            x_dist = trainer->x - p->x;
        } 
        else
        {
            x_dir = "West";
            x_dist = p->x - trainer->x;
        }

        if((p->y - trainer->y) < 0)
        {
            y_dir = "South";
            y_dist = trainer->y - p->y;
        }
        else
        {
            y_dir = "North";
            y_dist = p->y - trainer->y;
        }
        const char* x_dir_c = x_dir.c_str();
        const char* y_dir_c = y_dir.c_str();

        mv++;
        mvwprintw(trainer_pad,mv,0,"%s", "Distance from player:");
        mv++;
        mvwprintw(trainer_pad,mv,0,"%s : %d", x_dir_c, x_dist);
        mv++;
        mvwprintw(trainer_pad,mv,0,"%s : %d", y_dir_c, y_dist);
        mv++;
        if(trainer->is_defeated)
        {status = "Defeated";}
        else
        {status = "Ready for battle";}
        const char* status_c = status.c_str();
        mvwprintw(trainer_pad,mv,0,"Status : %s", status_c);
        mv+=2;

    }

    prefresh(trainer_pad,0,0,5,15,15,70);
    int pad_location = 0;
    int viewing = 1;
    int input; 
    while(viewing)
    {
       input = wgetch(trainer_pad);
       if(input == 27)
       {
         viewing = 0;
       }
       else if(input == KEY_UP && pad_location >= 0)
       {
           pad_location--;
           prefresh(trainer_pad, pad_location,0,5,15,15,70); 
       }
       else if(input == KEY_DOWN && pad_location <=50)
       {
           pad_location++;
           prefresh(trainer_pad, pad_location,0,5,15,15,70); 
       }

    }
    delwin(trainer_pad);



}

void compare(int x, int y, int min_pair[2], int* min, int dij[X_MAG][Y_MAG])
{
    if(dij[x][y] < *min)
    {
        *min = dij[x][y];
         min_pair[0]=x;
        min_pair[1]=y;
  }
     
   
}

char random_turn(char except)
{
    if(except == 'N')
    {
        switch ((rand() % 3) + 1)
        {
            case 1: 
                return 'W';
                break;

            case 2: 
                return 'S';
                break;

            case 3:
                return 'E';
                break;

            default: 
                return 'X';
                break;
        }
    }
    else if(except == 'S')
    {
        switch ((rand() % 3) + 1)
        {
            case 1: 
                return 'N';
                break;

            case 2: 
                return 'W';
                break;

            case 3:
                return 'E';
                break;

            default: 
                return 'X';
                break;
        }
        return 'f';
    }
    else if(except == 'E')
    {
        switch ((rand() % 3) + 1)
        {
            case 1: 
                return 'N';
                break;

            case 2: 
                return 'S';
                break;

            case 3:
                return 'W';
                break;

            default: 
                return 'X';
                break;
        }

    }
    else
    {
        switch ((rand() % 3) + 1)
        {
            case 1: 
                return 'N';
                break;

            case 2: 
                return 'S';
                break;

            case 3:
                return 'W';
                break;

            default: 
                return 'X';
                break;
        }

    }
}

//CHILLIN
int move_npc(npc* c, char map[X_MAG][Y_MAG], int cost_map[X_MAG][Y_MAG],
        int character_map[X_MAG][Y_MAG], int new_x, int new_y)
{
    if(character_map[new_x][new_y] == -1 && 
            cost_map[new_x][new_y] != INT16_MAX)
    {
        //setting values back to before character was there 
        character_map[c->x][c->y] = -1;
        map[c->x][c->y] = c->terrain;
       
        //setting new coords
        c->x = new_x;
        c->y = new_y;

        //occupy space
        c->terrain = map[c->x][c->y];
        map[c->x][c->y] = c->type;
        c->cost+=cost_map[c->x][c->y];
        character_map[c->x][c->y] = c->index;

        
    }
    else
    {  
        if(character_map[new_x][new_y] == 0 && c->type != '@')
        {
        return character_map[new_x][new_y];
        }
        else if(character_map[new_x][new_y] != -1 && c->type == '@')
        {
        return character_map[new_x][new_y];
        }
        else
        {
        c->cost+=5;
        }
    }
    return -1;
}




int explore(npc* p, char map[X_MAG][Y_MAG], int cost_map[X_MAG][Y_MAG],
        int character_map[X_MAG][Y_MAG])
{
    int collision;
    //game is printed upsidown so values are adjusted accordingly
    if(p->cur_dir == 'N')
    {
        if(p->y > 0 && cost_map[p->x][p->y-1] != INT16_MAX)
        {
            collision = move_npc(p, map, cost_map, character_map, p->x, p->y-1);
        }
        else
        {
            collision = move_npc(p, map, cost_map, character_map, p->x, p->y+1);
            p->cur_dir = random_turn('N');
        }
    }
    else if(p->cur_dir == 'S')
    {
        if(p->y < 20 && cost_map[p->x][p->y+1] != INT16_MAX)
        {
            collision = move_npc(p, map, cost_map, character_map, p->x, p->y+1);
        }
        else
        {
            collision = move_npc(p, map, cost_map, character_map, p->x, p->y-1);
            p->cur_dir = random_turn('S');
        }
    }
    else if(p->cur_dir == 'E')
    {
        if(p->x < 79 && cost_map[p->x+1][p->y] != INT16_MAX)
        {
            collision = move_npc(p, map, cost_map, character_map, p->x+1, p->y);
        }
        else
        {
            collision = move_npc(p, map, cost_map, character_map, p->x-1, p->y);
            p->cur_dir = random_turn('E');
        }
    }
    else if(p->cur_dir == 'W')
    {
        if(p->x > 0 && cost_map[p->x-1][p->y] != INT16_MAX)
        {
            collision = move_npc(p, map, cost_map, character_map, p->x-1, p->y);
        }
        else
        {
            collision = move_npc(p, map, cost_map, character_map, p->x+1, p->y);
            p->cur_dir = random_turn('W');
        }
    }
    return collision;
}


int wander(npc* p, char map[X_MAG][Y_MAG], int cost_map[X_MAG][Y_MAG],
        int character_map[X_MAG][Y_MAG])
{
    int collision;
    //game is printed upsidown so values are adjusted accordingly
    if(p->cur_dir == 'N')
    {
        if(p->y > 0 && map[p->x][p->y-1] == p->terrain)
        {
            collision = move_npc(p, map, cost_map, character_map, p->x, p->y-1);
        }
        else
        {
            collision = move_npc(p, map, cost_map, character_map, p->x, p->y+1);
            p->cur_dir = random_turn('N');
        }
    }
    else if(p->cur_dir == 'S')
    {
        if(p->y < 20 && map[p->x][p->y+1] == p->terrain)
        {
            collision = move_npc(p, map, cost_map, character_map, p->x, p->y+1);
        }
        else
        {
            collision = move_npc(p, map, cost_map, character_map, p->x, p->y-1);
            p->cur_dir = random_turn('S');
        }
    }
    else if(p->cur_dir == 'E')
    {
        if(p->x < 79 && map[p->x+1][p->y] == p->terrain)
        {
            collision = move_npc(p, map, cost_map, character_map, p->x+1, p->y);
        }
        else
        {
            collision = move_npc(p, map, cost_map, character_map, p->x-1, p->y);
            p->cur_dir = random_turn('E');
        }
    }
    else if(p->cur_dir == 'W')
    {
        if(p->x > 0 && map[p->x-1][p->y] == p->terrain)
        {
            collision = move_npc(p, map, cost_map, character_map, p->x-1, p->y);
        }
        else
        {
            collision = move_npc(p, map, cost_map, character_map, p->x+1, p->y);
            p->cur_dir = random_turn('W');
        }
    }
    return collision;
}


int pace(npc* p, char map[X_MAG][Y_MAG], int cost_map[X_MAG][Y_MAG],
        int character_map[X_MAG][Y_MAG])
{
    int collision;
    //game is printed upsidown so values are adjusted accordingly
    if(p->cur_dir == 'N')
    {
        if(p->y > 0 && cost_map[p->x][p->y-1] != INT16_MAX)
        {
            collision = move_npc(p, map, cost_map, character_map, p->x, p->y-1);
        }
        else
        {
            collision = move_npc(p, map, cost_map, character_map, p->x, p->y+1);
            p->cur_dir = 'S';
        }
    }
    else if(p->cur_dir == 'S')
    {
        if(p->y < 20 && cost_map[p->x][p->y+1] != INT16_MAX)
        {
            collision = move_npc(p, map, cost_map, character_map, p->x, p->y+1);
        }
        else
        {
            collision = move_npc(p, map, cost_map, character_map, p->x, p->y-1);
            p->cur_dir = 'N';
        }
    }
    else if(p->cur_dir == 'E')
    {
        if(p->x < 79 && cost_map[p->x+1][p->y] != INT16_MAX)
        {
            collision = move_npc(p, map, cost_map, character_map, p->x+1, p->y);
        }
        else
        {
            collision = move_npc(p, map, cost_map, character_map, p->x-1, p->y);
            p->cur_dir = 'W';
        }
    }
    else if(p->cur_dir == 'W')
    {
        if(p->x > 0 && cost_map[p->x-1][p->y] != INT16_MAX)
        {
            collision = move_npc(p, map, cost_map, character_map, p->x-1, p->y);
        }
        else
        {
            collision = move_npc(p, map, cost_map, character_map, p->x+1, p->y);
            p->cur_dir = 'E';
        }
    }
    return collision;

}

int chase(npc* c,char map[X_MAG][Y_MAG], int cost_map[X_MAG][Y_MAG],
        int character_map[X_MAG][Y_MAG], int dijkstra[X_MAG][Y_MAG])
{
    int min_pair[2] = {0,0};
    int min = INT16_MAX-1;
    int collision;

    
    if(c->x < 78)
    {
        compare(c->x+1, c->y, min_pair, &min, dijkstra);
    }
    if(c->y < 19)
    {
        compare(c->x, c->y+1, min_pair, &min, dijkstra);
    }

    if(c->x > 1)
    {
        compare(c->x-1, c->y, min_pair, &min, dijkstra);
    }

    if(c->y > 1)
    {
        compare(c->x, c->y-1, min_pair, &min, dijkstra);
    }

    if(c->x < 78 && c->y < 19)
    {
        compare(c->x+1, c->y+1, min_pair, &min, dijkstra);
    }

    if(c->x > 1 && c->y > 1)
    {
        compare(c->x-1, c->y-1, min_pair, &min, dijkstra);
    }

    if(c->x > 1 && c->y < 19)
    {
        compare(c->x-1, c->y+1, min_pair, &min, dijkstra);
    }

    if(c->x < 79 && c->y > 1)
    {
        compare(c->x+1, c->y-1, min_pair, &min, dijkstra);
    }
    collision = move_npc(c, map, cost_map, character_map, min_pair[0], min_pair[1]);

    
    return collision;
}

heap_t* init_turn_heap(int capacity)
{
    return createHeap_t(capacity);
}

void add_npc(heap_t* h, heapNode_t* ht)
{
        insert_t(h, ht); 

}

heapNode_t* create_npc(int index, int x, int y, char type, int cost_map[X_MAG][Y_MAG],
        int char_map[X_MAG][Y_MAG], char map[X_MAG][Y_MAG])
{
    npc* npc = (class npc*)malloc(sizeof(*npc));
    
    //initialize our basic values
    npc->x = x;
    npc->y = y;
    npc->is_defeated = 0;
    npc->type = type;
    if(type != '@')
    {npc->cost = cost_map[x][y];}
    else
    {npc->cost = 15;}
    npc->terrain = map[x][y];
    npc->index = index;

    //gen our random direction (only matters for npcs we care about)

    switch ((rand() % 4) + 1)
    {
        case 1: 
            npc->cur_dir = 'W';
            break;

        case 2: 
            npc->cur_dir = 'S';
            break;

        case 3:
            npc->cur_dir = 'E';
            break;

        case 4: 
            npc->cur_dir = 'N'; 
            break;
    }    
    char_map[x][y] = index;

    heapNode_t* ht;
    ht = (heapNode_t*)malloc(sizeof(heapNode_t*));
    ht->h_npc = npc;

    return ht;
}

void init_new_square(board *bd,int hiker_cost_map[X_MAG][Y_MAG], 
        int hiker_dij_map[X_MAG][Y_MAG],
        int rival_cost_map[X_MAG][Y_MAG],
        int rival_dij_map[X_MAG][Y_MAG],
        int pc_cost_map[X_MAG][Y_MAG],
        heapNode_t** npc_arr_board[BOARD_X][BOARD_Y],
        heap_t* queue_array[BOARD_X][BOARD_Y],
        int npc_count)
{

    initCostMap(bd->board[bd->curX][bd->curY], 
            hiker_cost_map, 
            rival_cost_map,
            pc_cost_map);
    dijkstra(bd->board[bd->curX][bd->curY], hiker_cost_map, rival_cost_map,
            rival_dij_map, hiker_dij_map);

    queue_array[bd->curX][bd->curY] = init_turn_heap(npc_count+1);

    
    npc_arr_board[bd->curX][bd->curY] = (heapNode_t**)malloc((npc_count+1) * sizeof(heapNode_t*));
    
    


    heapNode_t* playerNode = create_npc(0,bd->board[bd->curX][bd->curY]->px,
            bd->board[bd->curX][bd->curY]->py, '@', pc_cost_map, bd->board[bd->curX][bd->curY]->char_map,
            bd->board[bd->curX][bd->curY]->map);

    bd->board[bd->curX][bd->curY]->
        map[bd->board[bd->curX][bd->curY]->px][bd->board[bd->curX][bd->curY]->py] = '@';

    npc_arr_board[bd->curX][bd->curY][0] = playerNode;



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
                if(hiker_cost_map[x][y] != INT16_MAX && bd->board[bd->curX][bd->curY]->char_map[x][y] == -1)
                {
                    valid = 1;
                }
            }
            else
            {
                if(rival_cost_map[x][y] != INT16_MAX && bd->board[bd->curX][bd->curY]->char_map[x][y] == -1)
                {
                    valid = 1;
                }
            }
        }
        heapNode_t* npc;
        if(type == 'h')
        {
            npc = create_npc(i,x,y,type,hiker_cost_map,
                    bd->board[bd->curX][bd->curY]->char_map,bd->board[bd->curX][bd->curY]->map);
        }
        else
        {
            npc = create_npc(i,x,y,type,rival_cost_map,
                    bd->board[bd->curX][bd->curY]->char_map,bd->board[bd->curX][bd->curY]->map);

        }
        bd->board[bd->curX][bd->curY]->map[x][y] = type;
        if(type != 's')
        {
            add_npc(queue_array[bd->curX][bd->curY], npc); 
        }
        npc_arr_board[bd->curX][bd->curY][i] = npc;

    }


}
int next_player_turn(heapNode_t* hn, int c, char map[X_MAG][Y_MAG], 
        int cost_map[X_MAG][Y_MAG],
        int character_map[X_MAG][Y_MAG],
        square* sq,
        heapNode_t** npc_arr,
        int n,
        std::vector<saved_poke*>& poke_list,
        std::vector<moves*>& moves_vec, std::vector<pokemon_moves*>& pokemon_moves_vec,
        std::vector<pokemon*>& pokemon_vec, std::vector<pokemon_stats*>& pokemon_stats_vec,
        board* bd)
{

        int level;
        vector<int> levels;
        int manhat = abs(bd->curX - 200) + abs(bd->curY - 200);
        int min;
        int max;

        if(manhat <= 200)
        {
            min = 1;
            max = manhat / 2;
        }
        else
        {
            max = 100;
            min = (manhat - 200)/2;
             
        }
        
        int no_fail = 1;
        int num_trainer_pokemon = 1;
        while(num_trainer_pokemon < 6 && no_fail) 
        {
        rand() % 101 <= 60 ? num_trainer_pokemon++ : no_fail = 0;
        }

        for(int i = 0; i < num_trainer_pokemon; i++)
        {
            level = max == 0 ? min : rand() % max;
            level = level <= min ? min : level;
            levels.push_back(level);
        }
        


        int error_caught = 0;
        int collision;
        int menu_open = 0;
        int winchar;
        //move to the lower left
        if(c == '1' || c == 'b')
        {
            if (cost_map[sq->px-1][sq->py+1] != INT16_MAX)
            {
                sq->px -= 1;
                sq->py += 1;
                if ((rand() % 101) <= 10 && sq->map[sq->px][sq->py] == ':')
                {

                    pokemon_encounter(poke_list, moves_vec, pokemon_moves_vec,
                            pokemon_vec, pokemon_stats_vec, level);
                }
            }
            else
            {
                error_caught = 1;
                if (sq->map[sq->px-1][sq->py+1] == '~')
                {
                    return 1;
                }
                else
                {
                    return 2;
                }
            }
        }
        //move down
        else if(c == '2' || c == 'j')
        {
            if (cost_map[sq->px][sq->py+1] != INT16_MAX)
            {
                sq->py += 1;
                if ((rand() % 101) <= 10 && sq->map[sq->px][sq->py] == ':')
                {
                pokemon_encounter(poke_list, moves_vec, pokemon_moves_vec,
                            pokemon_vec, pokemon_stats_vec, level);
                }
            }
            else if(sq->px == sq->s && sq->py == 19)
            {
                return 'S';
            }
            else
            {
                error_caught = 1;
                if (sq->map[sq->px][sq->py+1] == '~')
                {
                    return 1;
                }
                else
                {
                    return 2;
                }
            }
        }
        //move to lower right
        else if(c == '3' || c == 'n')
        {
            if (cost_map[sq->px+1][sq->py+1] != INT16_MAX)
            {
                sq->px += 1;
                sq->py += 1;
                if ((rand() % 101) <= 10 && sq->map[sq->px][sq->py] == ':')
                {
                pokemon_encounter(poke_list, moves_vec, pokemon_moves_vec,
                            pokemon_vec, pokemon_stats_vec, level);
                }
            }
            else
            {
                error_caught = 1;
                if (sq->map[sq->px+1][sq->py+1] == '~')
                {
                    return 1;
                }
                else
                {
                    return 2;
                }
            }
        }
        //move one cell to left
        else if(c == '4' || c == 'h')
        {
            if (cost_map[sq->px-1][sq->py] != INT16_MAX)
            {
                sq->px -= 1;
                if ((rand() % 101) <= 10 && sq->map[sq->px][sq->py] == ':')
                {
                pokemon_encounter(poke_list, moves_vec, pokemon_moves_vec,
                            pokemon_vec, pokemon_stats_vec, level);
                }
            }
            else if(sq->py == sq->w && sq->px == 1)
            {
                return 'W';
            }
            else
            {
                error_caught = 1;
                if (sq->map[sq->px-1][sq->py] == '~')
                {
                    return 1;
                }
                else
                {
                    return 2;
                }
            } 
        }
        //rest
        else if(c == '5' || c == ' ' || c == '.')
        {
            hn->h_npc->cost += 10;
            if ((rand() % 101) <= 10 && sq->map[sq->px][sq->py] == ':')
                {
                pokemon_encounter(poke_list, moves_vec, pokemon_moves_vec,
                            pokemon_vec, pokemon_stats_vec, level);
                }
        }
        //move one cell to the right
        else if(c == '6' || c == 'l')
        {
            if (cost_map[sq->px+1][sq->py] != INT16_MAX)
            {
                sq->px += 1;
                if ((rand() % 101) <= 10 && sq->map[sq->px][sq->py] == ':')
                {
                pokemon_encounter(poke_list, moves_vec, pokemon_moves_vec,
                            pokemon_vec, pokemon_stats_vec, level);
                }
            }
            else if(sq->py == sq->e && sq->px == 78)
            {
                return 'E';
            }
            else
            {
                error_caught = 1;
                if (sq->map[sq->px+1][sq->py] == '~')
                {
                    return 1;
                }
                else
                {
                    return 2;
                }
            }
        }
        //move to the upper left
        else if(c == '7' || c == 'y')
        {
            if (cost_map[sq->px-1][sq->py-1] != INT16_MAX)
            {
                sq->px -= 1;
                sq->py -= 1;
                if ((rand() % 101) <= 10 && sq->map[sq->px][sq->py] == ':')
                {
                pokemon_encounter(poke_list, moves_vec, pokemon_moves_vec,
                            pokemon_vec, pokemon_stats_vec, level);
                }
            }
            else
            {
                error_caught = 1;
                if (sq->map[sq->px-1][sq->py-1] == '~')
                {
                    return 1;
                }
                else
                {
                    return 2;
                }
            }
        }
        //move one cell up
        else if(c == '8' || c == 'k')
        {
            if (cost_map[sq->px][sq->py-1] != INT16_MAX)
            {
                sq->py -= 1;
                if ((rand() % 101) <= 10 && sq->map[sq->px][sq->py] == ':')
                {
                pokemon_encounter(poke_list, moves_vec, pokemon_moves_vec,
                            pokemon_vec, pokemon_stats_vec, level);
                } 
            }
            else if(sq->px == sq->n && sq->py == 1)
            {
                return 'N';
            }
            else
            {
                error_caught = 1;
                if (sq->map[sq->px][sq->py-1] == '~')
                {
                    return 1;
                }
                else
                {
                    return 2;
                }
            }
        }
        else if(c == '9' || c == 'u')
        {
            if (cost_map[sq->px+1][sq->py-1] != INT16_MAX)
            {
                sq->py -= 1;
                sq->px += 1;
                if ((rand() % 101) <= 10 && sq->map[sq->px][sq->py] == ':')
                {
                    pokemon_encounter(poke_list, moves_vec, pokemon_moves_vec,
                            pokemon_vec, pokemon_stats_vec, level);
                }
            }
            else
            {
                error_caught = 1;
                if (sq->map[sq->px+1][sq->py-1] == '~')
                {
                    return 1;
                }
                else
                {
                    return 2;
                }
            }
        }
        else if(c =='F')
        {
            return c;
        }
        else if(c == '>' 
                && (hn->h_npc->terrain == 'C' || 
                hn->h_npc->terrain == 'M'))
            
        {
            menu_open = 1;
            WINDOW * menu = newwin(10,52,5,15);
            winchar = wgetch(menu);
            if(winchar == '<')
            {
            menu_open = 0;
            delwin(menu);
            }
        }
        else if (c == 't')
        {
            menu_open = 1;
            show_trainers(hn->h_npc, npc_arr, n);
            menu_open = 0;
        }
        else if(c == 'Q')
        {
            endwin();
            exit(0);
        }
        else
        {
            
            collision = move_npc(hn->h_npc, map, cost_map, character_map, sq->px, sq->py); 
            if(collision != -1 && collision != 0)
            {
                battle(hn->h_npc,npc_arr[collision]->h_npc,character_map,
                        poke_list, moves_vec, pokemon_moves_vec, pokemon_vec,
            pokemon_stats_vec, levels);

            }
            return 0; 
        }



        if(!error_caught && !menu_open)
        {
            collision = move_npc(hn->h_npc, map, cost_map, character_map, sq->px, sq->py); 
            if (collision != -1 && collision != 0) 
            {
                battle(hn->h_npc,npc_arr[collision]->h_npc,character_map,
                        poke_list, moves_vec, pokemon_moves_vec, pokemon_vec,
                        pokemon_stats_vec, levels);}
            return -1;
        }
        return -1;

}

// THE QUEUE THAT IS PASSED THROUGH THE ARRAY IS THE QUEUE
// FOR THE LAST SQUARE
// THEREFORE IF YOU CHANGE SQUARES, THE QUEUE YOU ADD YOURSELF TO
// IS FOR THE WRONG SQUARE

int next_turn(heap_t* h, char map[X_MAG][Y_MAG], 
        int hiker_cost_map[X_MAG][Y_MAG],
        int rival_cost_map[X_MAG][Y_MAG],
        int pc_cost_map[X_MAG][Y_MAG],
        int rival_dij[X_MAG][Y_MAG],
        int hiker_dij[X_MAG][Y_MAG], 
        square* sq,
        heapNode_t** npc_arr_board[BOARD_X][BOARD_Y],
        int n,
        board* bd,
        heap_t* queue_array[401][401],
        std::vector<saved_poke*>& poke_list,
        std::vector<moves*>& moves_vec, std::vector<pokemon_moves*>& pokemon_moves_vec,
        std::vector<pokemon*>& pokemon_vec, std::vector<pokemon_stats*>& pokemon_stats_vec)
{
    heapNode_t* hn = extractMin_t(queue_array[bd->curX][bd->curY]); 
    int response = -1; 

    int level;
        vector<int> levels;
        int manhat = abs(bd->curX - 200) + abs(bd->curY - 200);
        int min;
        int max;

        if(manhat <= 200)
        {
            min = 1;
            max = manhat / 2;
        }
        else
        {
            max = 100;
            min = (manhat - 200)/2;
             
        }
        
        int no_fail = 1;
        int num_trainer_pokemon = 1;
        while(num_trainer_pokemon <= 6 && no_fail) 
        {
        rand() % 101 <= 60 ? num_trainer_pokemon++ : no_fail = 0;
        }

        for(int i = 0; i < num_trainer_pokemon; i++)
        {
            level = max == 0 ? min : rand() % max;
            level = level <= min ? min : level;
            levels.push_back(level);
        }


    if(!hn->h_npc->is_defeated)
    {
        int c;
        int collision;
        switch(hn->h_npc->type)
        {
            case 'h':
                add_npc(queue_array[bd->curX][bd->curY], hn);
                collision = chase(hn->h_npc, map, hiker_cost_map, bd->board[bd->curX][bd->curY]->char_map, hiker_dij);
                if(collision == 0)
                {
                    battle(npc_arr_board[bd->curX][bd->curY][collision]->h_npc,hn->h_npc,
                            bd->board[bd->curX][bd->curY]->char_map,
                        poke_list, moves_vec, pokemon_moves_vec, pokemon_vec,
                        pokemon_stats_vec, levels);
                }
                break;
            case 'w':
                add_npc(queue_array[bd->curX][bd->curY], hn);
                collision = wander(hn->h_npc, map, rival_cost_map, bd->board[bd->curX][bd->curY]->char_map);
                if(collision == 0)
                {
                battle(npc_arr_board[bd->curX][bd->curY][collision]->h_npc,hn->h_npc,
                            bd->board[bd->curX][bd->curY]->char_map,
                        poke_list, moves_vec, pokemon_moves_vec, pokemon_vec,
                        pokemon_stats_vec, levels);
                }
                break;
            case 'p':
                add_npc(queue_array[bd->curX][bd->curY], hn);
                collision = pace(hn->h_npc, map, rival_cost_map, bd->board[bd->curX][bd->curY]->char_map);
                if(collision == 0)
                {
                    battle(npc_arr_board[bd->curX][bd->curY][collision]->h_npc,hn->h_npc,
                            bd->board[bd->curX][bd->curY]->char_map,
                        poke_list, moves_vec, pokemon_moves_vec, pokemon_vec,
                        pokemon_stats_vec, levels);
                }
                break;
            case 'e':
                add_npc(queue_array[bd->curX][bd->curY], hn);
                collision = explore(hn->h_npc, map, rival_cost_map, bd->board[bd->curX][bd->curY]->char_map);
                if(collision == 0)
                {
                    battle(npc_arr_board[bd->curX][bd->curY][collision]->h_npc,hn->h_npc,
                            bd->board[bd->curX][bd->curY]->char_map,
                        poke_list, moves_vec, pokemon_moves_vec, pokemon_vec,
                        pokemon_stats_vec, levels);
                }
                break;
            case 'r':
                add_npc(queue_array[bd->curX][bd->curY], hn);
                collision = chase(hn->h_npc, map, rival_cost_map, 
                        bd->board[bd->curX][bd->curY]->char_map, rival_dij);
                if(collision == 0)
                {
                    battle(npc_arr_board[bd->curX][bd->curY][collision]->h_npc,hn->h_npc,
                            bd->board[bd->curX][bd->curY]->char_map,
                        poke_list, moves_vec, pokemon_moves_vec, pokemon_vec,
                        pokemon_stats_vec, levels);
                }
                break;
            case '@':
                c = getch();
                response = next_player_turn(hn, c, map, pc_cost_map,
                        bd->board[bd->curX][bd->curY]->char_map, sq, npc_arr_board[bd->curX][bd->curY], n,
                        poke_list,
                        moves_vec, pokemon_moves_vec,
                        pokemon_vec, pokemon_stats_vec, bd);
                if(response == 78)
                {
                    //north
                    if(bd->curY+1 <= 400)
                    {
                        if(bd->board[bd->curX][bd->curY+1] == NULL)   
                        {
                            bd->board[bd->curX][bd->curY]->char_map[bd->board[bd->curX][bd->curY]->px][bd->board[bd->curX][bd->curY]->py] = 0;
                            checkTile(bd,bd->curX,bd->curY+1);
                            init_new_square(bd, hiker_cost_map, hiker_dij,
                                    rival_cost_map, rival_dij,
                                    pc_cost_map, npc_arr_board,
                                    queue_array, n);
                        }
                        else
                        {
                            bd->board[bd->curX][bd->curY]->char_map[bd->board[bd->curX][bd->curY]->px][bd->board[bd->curX][bd->curY]->py] = -1;
                            checkTile(bd,bd->curX,bd->curY+1);
                        }
                        bd->board[bd->curX][bd->curY]->
                            map[bd->board[bd->curX][bd->curY]->px][bd->board[bd->curX][bd->curY]->py] = '#';

                        npc_arr_board[bd->curX][bd->curY][0]->h_npc->x = bd->board[bd->curX][bd->curY]->s;
                        npc_arr_board[bd->curX][bd->curY][0]->h_npc->y = 19;

                        bd->board[bd->curX][bd->curY]
                            ->px = bd->board[bd->curX][bd->curY]->s;

                        bd->board[bd->curX][bd->curY]
                            ->py = 19;


                        bd->board[bd->curX][bd->curY] 
                            ->map[bd->board[bd->curX][bd->curY]->px][bd->board[bd->curX][bd->curY]->py] = '@';
                        bd->board[bd->curX][bd->curY]->char_map[bd->board[bd->curX][bd->curY]->px][bd->board[bd->curX][bd->curY]->py] = 0;

                        initCostMap(bd->board[bd->curX][bd->curY], 
                                hiker_cost_map, 
                                rival_cost_map,
                                pc_cost_map);
                        dijkstra(bd->board[bd->curX][bd->curY], hiker_cost_map, rival_cost_map,
                                rival_dij, hiker_dij);
                    }
                    else
                    {
                        mvprintw(0,0,"%s", "You can't move farther in that direction");
                    }
                    response =  -1;
                }
                else if(response == 87)
                {
                    //west

                    if(bd->curX-1 >= 0)
                    {
                        if(bd->board[bd->curX-1][bd->curY] == NULL)   
                        {
                            bd->board[bd->curX][bd->curY]->char_map[bd->board[bd->curX][bd->curY]->px][bd->board[bd->curX][bd->curY]->py] = -1;
                            checkTile(bd,bd->curX-1,bd->curY);
                            init_new_square(bd, hiker_cost_map, hiker_dij,
                                    rival_cost_map, rival_dij,
                                    pc_cost_map, npc_arr_board,
                                    queue_array, n);
                        }
                        else
                        {
                            bd->board[bd->curX][bd->curY]->char_map[bd->board[bd->curX][bd->curY]->px][bd->board[bd->curX][bd->curY]->py] = -1;
                            checkTile(bd,bd->curX-1,bd->curY);
                        }
                        bd->board[bd->curX][bd->curY]->
                            map[bd->board[bd->curX][bd->curY]->px][bd->board[bd->curX][bd->curY]->py] = '#';

                        npc_arr_board[bd->curX][bd->curY][0]->h_npc->y = bd->board[bd->curX][bd->curY]->e;
                        npc_arr_board[bd->curX][bd->curY][0]->h_npc->x = 78;

                        bd->board[bd->curX][bd->curY]
                            ->py = bd->board[bd->curX][bd->curY]->e;

                        bd->board[bd->curX][bd->curY]
                            ->px = 78;


                        bd->board[bd->curX][bd->curY] 
                            ->map[bd->board[bd->curX][bd->curY]->px][bd->board[bd->curX][bd->curY]->py] = '@';

                        bd->board[bd->curX][bd->curY]->char_map[bd->board[bd->curX][bd->curY]->px][bd->board[bd->curX][bd->curY]->py] = 0;

                        initCostMap(bd->board[bd->curX][bd->curY], 
                                hiker_cost_map, 
                                rival_cost_map,
                                pc_cost_map);
                        dijkstra(bd->board[bd->curX][bd->curY], hiker_cost_map, rival_cost_map,
                                rival_dij, hiker_dij);
                    }
                    else
                    {
                        mvprintw(0,0,"%s", "You can't move farther in that direction");
                    }
                    response =  -1;
                }
                else if(response == 69)
                {
                    //east
                    if(bd->curX+1 <= 400)
                    {

                        if(bd->board[bd->curX+1][bd->curY] == NULL)
                        {
                            bd->board[bd->curX][bd->curY]->char_map[bd->board[bd->curX][bd->curY]->px][bd->board[bd->curX][bd->curY]->py] = -1;
                            checkTile(bd,bd->curX+1,bd->curY);
                            init_new_square(bd, hiker_cost_map, hiker_dij,
                                    rival_cost_map, rival_dij,
                                    pc_cost_map, npc_arr_board,
                                    queue_array, n);
                        }
                        else
                        {

                            bd->board[bd->curX][bd->curY]->char_map[bd->board[bd->curX][bd->curY]->px][bd->board[bd->curX][bd->curY]->py] = -1;
                            checkTile(bd,bd->curX+1,bd->curY);
                        }
                        bd->board[bd->curX][bd->curY]->
                            map[bd->board[bd->curX][bd->curY]->px][bd->board[bd->curX][bd->curY]->py] = '#';

                        npc_arr_board[bd->curX][bd->curY][0]->h_npc->y = bd->board[bd->curX][bd->curY]->w;
                        npc_arr_board[bd->curX][bd->curY][0]->h_npc->x = 1;

                        bd->board[bd->curX][bd->curY]
                            ->py = bd->board[bd->curX][bd->curY]->w;

                        bd->board[bd->curX][bd->curY]
                            ->px = 1;


                        bd->board[bd->curX][bd->curY] 
                            ->map[bd->board[bd->curX][bd->curY]->px][bd->board[bd->curX][bd->curY]->py] = '@';

                        bd->board[bd->curX][bd->curY]->char_map[bd->board[bd->curX][bd->curY]->px][bd->board[bd->curX][bd->curY]->py] = 0;
                        initCostMap(bd->board[bd->curX][bd->curY], 
                                hiker_cost_map, 
                                rival_cost_map,
                                pc_cost_map);
                        dijkstra(bd->board[bd->curX][bd->curY], hiker_cost_map, rival_cost_map,
                                rival_dij, hiker_dij);
                    }
                    else
                    {
                        mvprintw(0,0,"%s", "You can't move farther in that direction");
                    }
                    response =  -1;
                }
                else if(response == 83)
                {
                    //South
                    if(bd->curY-1 >= 0)
                    {
                        if(bd->board[bd->curX][bd->curY-1] == NULL)
                        {
                            bd->board[bd->curX][bd->curY]->char_map[bd->board[bd->curX][bd->curY]->px][bd->board[bd->curX][bd->curY]->py] = -1;
                            checkTile(bd,bd->curX,bd->curY-1);
                            init_new_square(bd, hiker_cost_map, hiker_dij,
                                    rival_cost_map, rival_dij,
                                    pc_cost_map, npc_arr_board,
                                    queue_array, n);
                        }
                        else
                        {
                            bd->board[bd->curX][bd->curY]->char_map[bd->board[bd->curX][bd->curY]->px][bd->board[bd->curX][bd->curY]->py] = -1;
                            checkTile(bd,bd->curX,bd->curY-1);
                        }
                        bd->board[bd->curX][bd->curY]->
                            map[bd->board[bd->curX][bd->curY]->px][bd->board[bd->curX][bd->curY]->py] = '#';

                        npc_arr_board[bd->curX][bd->curY][0]->h_npc->x = bd->board[bd->curX][bd->curY]->n;
                        npc_arr_board[bd->curX][bd->curY][0]->h_npc->y = 1;

                        bd->board[bd->curX][bd->curY]
                            ->px = bd->board[bd->curX][bd->curY]->n;

                        bd->board[bd->curX][bd->curY]
                            ->py = 1;


                        bd->board[bd->curX][bd->curY] 
                            ->map[bd->board[bd->curX][bd->curY]->px][bd->board[bd->curX][bd->curY]->py] = '@';

                        bd->board[bd->curX][bd->curY]->char_map[bd->board[bd->curX][bd->curY]->px][bd->board[bd->curX][bd->curY]->py] = 0;
                        initCostMap(bd->board[bd->curX][bd->curY], 
                                hiker_cost_map, 
                                rival_cost_map,
                                pc_cost_map);
                        dijkstra(bd->board[bd->curX][bd->curY], hiker_cost_map, rival_cost_map,
                                rival_dij, hiker_dij);

                    }
                    else
                    {
                        mvprintw(0,0,"%s", "You can't move farther in that direction");
                    }
                    response = -1;
                }
                else if(response == 'F')
                {
                    int pair[] = {0,0};
                    fly(pair); 

                    if(!(pair[0]+200 >= 0 && pair[1]+200 >= 0  && pair[0]+200 <= 400 && pair[1]+200 <= 400))
                    {
                        return 0;
                    }

                    if(bd->board[pair[0]+200][pair[1]+200] == NULL)
                    {
                        bd->board[bd->curX][bd->curY]->char_map[bd->board[bd->curX][bd->curY]->px][bd->board[bd->curX][bd->curY]->py] = -1;
                        checkTile(bd,pair[0]+200,pair[1]+200);
                        init_new_square(bd, hiker_cost_map, hiker_dij,
                                rival_cost_map, rival_dij,
                                pc_cost_map, npc_arr_board,
                                queue_array, n);
                    }
                    else
                    {
                        bd->board[bd->curX][bd->curY]->char_map[bd->board[bd->curX][bd->curY]->px][bd->board[bd->curX][bd->curY]->py] = -1;
                        checkTile(bd,pair[0]+200,pair[1]+200);
                    }
                    bd->board[bd->curX][bd->curY]->
                        map[bd->board[bd->curX][bd->curY]->px][bd->board[bd->curX][bd->curY]->py] = '#';

                    npc_arr_board[bd->curX][bd->curY][0]->h_npc->x = bd->board[bd->curX][bd->curY]->n;
                    npc_arr_board[bd->curX][bd->curY][0]->h_npc->y = 1;

                    bd->board[bd->curX][bd->curY]
                        ->px = bd->board[bd->curX][bd->curY]->n;

                    bd->board[bd->curX][bd->curY]
                        ->py = 1;


                    bd->board[bd->curX][bd->curY] 
                        ->map[bd->board[bd->curX][bd->curY]->px][bd->board[bd->curX][bd->curY]->py] = '@';

                    bd->board[bd->curX][bd->curY]->char_map[bd->board[bd->curX][bd->curY]->px][bd->board[bd->curX][bd->curY]->py] = 0;
                    initCostMap(bd->board[bd->curX][bd->curY], 
                            hiker_cost_map, 
                            rival_cost_map,
                            pc_cost_map);
                    dijkstra(bd->board[bd->curX][bd->curY], hiker_cost_map, rival_cost_map,
                            rival_dij, hiker_dij);



                    response =  -1;

                }
                else
                {
                    return response;
                }
                response = -1;
                break;
        }
    }
    return response;
}

 
