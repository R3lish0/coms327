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

#include "../turn/turn.h"
#include "../terrain/terrain.h"


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
    h->arr = malloc(capacity * sizeof(heapNode_t*));
 
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
 
    if (h->arr[parent]->npc->cost > h->arr[index]->npc->cost) {
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
    if (left != -1 && h->arr[left]->npc->cost < h->arr[index]->npc->cost)
        min = left;
    if (right != -1 && h->arr[right]->npc->cost < h->arr[min]->npc->cost)
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

void battle(npc* p, npc* n, int character_map[X_MAG][Y_MAG])
{
    int battle_choice;
    WINDOW * menu = newwin(10,52,5,15);
    wprintw(menu, "escape (e)"); 
    int in_menu = 1;
    while(in_menu)
    {
        battle_choice = wgetch(menu);
        if(battle_choice == 'e')
        {
            in_menu = 0;
            n->is_defeated = 1;
            character_map[n->x][n->y] = -1;
            endwin();
        }
    }
}

void show_trainers(npc* p, heapNode_t** num_arr, int n)
{
    
    WINDOW * trainer_pad = newpad(6*n,52);
    keypad(trainer_pad,TRUE);
    scrollok(trainer_pad,TRUE); 
    idlok(trainer_pad,TRUE);
    npc* trainer;
    char* x_dir;
    char* y_dir;
    int x_dist;
    int y_dist;
    char * status;
    int mv = 0;

    for(int i = 1; i <= n; i++)
    {
        trainer = num_arr[i]->npc; 
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
        mv++;
        mvwprintw(trainer_pad,mv,0,"%s", "Distance from player:");
        mv++;
        mvwprintw(trainer_pad,mv,0,"%s : %d", x_dir, x_dist);
        mv++;
        mvwprintw(trainer_pad,mv,0,"%s : %d", y_dir, y_dist);
        mv++;
        if(trainer->is_defeated)
        {status = "Defeated";}
        else
        {status = "Ready for battle";}
        mvwprintw(trainer_pad,mv,0,"Status : %s", status);
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
    endwin();



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
    npc* npc = malloc(sizeof(*npc));
    
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
    ht = malloc(sizeof(heapNode_t*));
    ht->npc = npc;

    return ht;
}

int next_player_turn(heapNode_t* hn, int c, char map[X_MAG][Y_MAG], 
        int cost_map[X_MAG][Y_MAG],
        int character_map[X_MAG][Y_MAG],
        square* sq,
        heapNode_t** npc_arr,
        int n)
{

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
            hn->npc->cost += 10;
        }
        //move one cell to the right
        else if(c == '6' || c == 'l')
        {
            if (cost_map[sq->px+1][sq->py] != INT16_MAX)
            {
                sq->px += 1;
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
        else if(c == '>' 
                && (hn->npc->terrain == 'C' || 
                hn->npc->terrain == 'M'))
            
        {
            menu_open = 1;
            WINDOW * menu = newwin(10,52,5,15);
            winchar = wgetch(menu);
            if(winchar == '<')
            {
            endwin();
            }
        }
        else if (c == 't')
        {
            menu_open = 1;
            show_trainers(hn->npc, npc_arr, n);
        }
        else if(c == 'Q')
        {
            endwin();
            exit(0);
        }
        else
        {
            
            collision = move_npc(hn->npc, map, cost_map, character_map, sq->px, sq->py); 
            if(collision != -1 && collision != 0)
            {
                battle(hn->npc,npc_arr[collision]->npc,character_map);

            }
            return 0; 
        }

        if(!error_caught && !menu_open)
        {
            collision = move_npc(hn->npc, map, cost_map, character_map, sq->px, sq->py); 
            if (collision != -1 && collision != 0) 
            {
                battle(hn->npc,npc_arr[collision]->npc,character_map);
            }
            return -1;
        }
        return -1;

}


int next_turn(heap_t* h, char map[X_MAG][Y_MAG], 
        int hiker_cost_map[X_MAG][Y_MAG],
        int rival_cost_map[X_MAG][Y_MAG],
        int pc_cost_map[X_MAG][Y_MAG],
        int character_map[X_MAG][Y_MAG],
        int rival_dij[X_MAG][Y_MAG],
        int hiker_dij[X_MAG][Y_MAG], 
        square* sq,
        heapNode_t** npc_arr,
        int n)
{
    heapNode_t* hn = extractMin_t(h); 
    int response = -1; 
    if(!hn->npc->is_defeated)
    {
    int c;
    int collision;
    switch(hn->npc->type)
    {
        case 'h':
            collision = chase(hn->npc, map, hiker_cost_map, character_map, hiker_dij);
            if(collision == 0)
            {
                battle(npc_arr[collision]->npc, hn->npc, character_map);
            }
            break;
        case 'w':
            collision = wander(hn->npc, map, rival_cost_map, character_map);
            if(collision == 0)
            {
                battle(npc_arr[collision]->npc, hn->npc, character_map);
            }
            break;
        case 'p':
            collision = pace(hn->npc, map, rival_cost_map, character_map);
            if(collision == 0)
            {
                battle(npc_arr[collision]->npc, hn->npc, character_map);
            }
            break;
        case 'e':
            collision = explore(hn->npc, map, rival_cost_map, character_map);
            if(collision == 0)
            {
                battle(npc_arr[collision]->npc, hn->npc, character_map);
            }
            break;
        case 'r':
            collision = chase(hn->npc, map, rival_cost_map, 
                    character_map, rival_dij);
            if(collision == 0)
            {
                battle(npc_arr[collision]->npc, hn->npc, character_map);
            }
            break;
        case '@':
            c = getch();
            response = next_player_turn(hn, c, map, pc_cost_map,
                    character_map, sq, npc_arr, n);
            break;
    }
     
    add_npc(h, hn);
    }
    return response;

}

 
