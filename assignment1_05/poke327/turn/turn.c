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
//#include "../terrain/terrain.h"


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
void move_npc(npc* c, char map[X_MAG][Y_MAG], int cost_map[X_MAG][Y_MAG],
        int character_map[X_MAG][Y_MAG], int new_x, int new_y)
{
    if(character_map[new_x][new_y] != 1)
    {
        //setting values back to before character was there 
        character_map[c->x][c->y] = 0;
        map[c->x][c->y] = c->terrain;
       
        //setting new coords
        c->x = new_x;
        c->y = new_y;

        //occupy space
        c->terrain = map[c->x][c->y];
        map[c->x][c->y] = c->type;
        c->cost+=cost_map[c->x][c->y];
        character_map[c->x][c->y] = 1;

        
    }
    else
    {
        c->cost+=5;
    }
}




void explore(npc* p, char map[X_MAG][Y_MAG], int cost_map[X_MAG][Y_MAG],
        int character_map[X_MAG][Y_MAG])
{
    //game is printed upsidown so values are adjusted accordingly
    if(p->cur_dir == 'N')
    {
        if(p->y > 0 && cost_map[p->x][p->y-1] != INT16_MAX)
        {
            move_npc(p, map, cost_map, character_map, p->x, p->y-1);
        }
        else
        {
            move_npc(p, map, cost_map, character_map, p->x, p->y+1);
            p->cur_dir = random_turn('N');
        }
    }
    else if(p->cur_dir == 'S')
    {
        if(p->y < 20 && cost_map[p->x][p->y+1] != INT16_MAX)
        {
            move_npc(p, map, cost_map, character_map, p->x, p->y+1);
        }
        else
        {
            move_npc(p, map, cost_map, character_map, p->x, p->y-1);
            p->cur_dir = random_turn('S');
        }
    }
    else if(p->cur_dir == 'E')
    {
        if(p->x < 79 && cost_map[p->x+1][p->y] != INT16_MAX)
        {
            move_npc(p, map, cost_map, character_map, p->x+1, p->y);
        }
        else
        {
            move_npc(p, map, cost_map, character_map, p->x-1, p->y);
            p->cur_dir = random_turn('E');
        }
    }
    else if(p->cur_dir == 'W')
    {
        if(p->x > 0 && cost_map[p->x-1][p->y] != INT16_MAX)
        {
            move_npc(p, map, cost_map, character_map, p->x-1, p->y);
        }
        else
        {
            move_npc(p, map, cost_map, character_map, p->x+1, p->y);
            p->cur_dir = random_turn('W');
        }
    }
}


void wander(npc* p, char map[X_MAG][Y_MAG], int cost_map[X_MAG][Y_MAG],
        int character_map[X_MAG][Y_MAG])
{
    //game is printed upsidown so values are adjusted accordingly
    if(p->cur_dir == 'N')
    {
        if(p->y > 0 && map[p->x][p->y-1] == p->terrain)
        {
            move_npc(p, map, cost_map, character_map, p->x, p->y-1);
        }
        else
        {
            move_npc(p, map, cost_map, character_map, p->x, p->y+1);
            p->cur_dir = random_turn('N');
        }
    }
    else if(p->cur_dir == 'S')
    {
        if(p->y < 20 && map[p->x][p->y+1] == p->terrain)
        {
            move_npc(p, map, cost_map, character_map, p->x, p->y+1);
        }
        else
        {
            move_npc(p, map, cost_map, character_map, p->x, p->y-1);
            p->cur_dir = random_turn('S');
        }
    }
    else if(p->cur_dir == 'E')
    {
        if(p->x < 79 && map[p->x+1][p->y] == p->terrain)
        {
            move_npc(p, map, cost_map, character_map, p->x+1, p->y);
        }
        else
        {
            move_npc(p, map, cost_map, character_map, p->x-1, p->y);
            p->cur_dir = random_turn('E');
        }
    }
    else if(p->cur_dir == 'W')
    {
        if(p->x > 0 && map[p->x-1][p->y] == p->terrain)
        {
            move_npc(p, map, cost_map, character_map, p->x-1, p->y);
        }
        else
        {
            move_npc(p, map, cost_map, character_map, p->x+1, p->y);
            p->cur_dir = random_turn('W');
        }
    }

}


void pace(npc* p, char map[X_MAG][Y_MAG], int cost_map[X_MAG][Y_MAG],
        int character_map[X_MAG][Y_MAG])
{
    //game is printed upsidown so values are adjusted accordingly
    if(p->cur_dir == 'N')
    {
        if(p->y > 0 && cost_map[p->x][p->y-1] != INT16_MAX)
        {
            move_npc(p, map, cost_map, character_map, p->x, p->y-1);
        }
        else
        {
            move_npc(p, map, cost_map, character_map, p->x, p->y+1);
            p->cur_dir = 'S';
        }
    }
    else if(p->cur_dir == 'S')
    {
        if(p->y < 20 && cost_map[p->x][p->y+1] != INT16_MAX)
        {
            move_npc(p, map, cost_map, character_map, p->x, p->y+1);
        }
        else
        {
            move_npc(p, map, cost_map, character_map, p->x, p->y-1);
            p->cur_dir = 'N';
        }
    }
    else if(p->cur_dir == 'E')
    {
        if(p->x < 79 && cost_map[p->x+1][p->y] != INT16_MAX)
        {
            move_npc(p, map, cost_map, character_map, p->x+1, p->y);
        }
        else
        {
            move_npc(p, map, cost_map, character_map, p->x-1, p->y);
            p->cur_dir = 'W';
        }
    }
    else if(p->cur_dir == 'W')
    {
        if(p->x > 0 && cost_map[p->x-1][p->y] != INT16_MAX)
        {
            move_npc(p, map, cost_map, character_map, p->x-1, p->y);
        }
        else
        {
            move_npc(p, map, cost_map, character_map, p->x+1, p->y);
            p->cur_dir = 'E';
        }
    }

}

void chase(npc* c,char map[X_MAG][Y_MAG], int cost_map[X_MAG][Y_MAG],
        int character_map[X_MAG][Y_MAG], int dijkstra[X_MAG][Y_MAG])
{
    int min_pair[2] = {0,0};
    int min = INT16_MAX;

    
    if(c->x < 79)
    {
        compare(c->x+1, c->y, min_pair, &min, dijkstra);
    }
    if(c->y < 20)
    {
        compare(c->x, c->y+1, min_pair, &min, dijkstra);
    }

    if(c->x > 0)
    {
        compare(c->x-1, c->y, min_pair, &min, dijkstra);
    }

    if(c->y > 0)
    {
        compare(c->x, c->y-1, min_pair, &min, dijkstra);
    }

    if(c->x < 79 && c->y < 20)
    {
        compare(c->x+1, c->y+1, min_pair, &min, dijkstra);
    }

    if(c->x > 0 && c->y > 0)
    {
        compare(c->x-1, c->y-1, min_pair, &min, dijkstra);
    }

    if(c->x > 0 && c->y < 20)
    {
        compare(c->x-1, c->y+1, min_pair, &min, dijkstra);
    }

    if(c->x < 79 && c->y > 0)
    {
        compare(c->x+1, c->y-1, min_pair, &min, dijkstra);
    }
    move_npc(c, map, cost_map, character_map, min_pair[0], min_pair[1]);
}

heap_t* init_turn_heap(int capacity)
{
    return createHeap_t(capacity);
}

void add_npc(heap_t* h, heapNode_t* ht)
{
        insert_t(h, ht); 

}

heapNode_t* create_npc(int x, int y, char type, int cost_map[X_MAG][Y_MAG],
        int char_map[X_MAG][Y_MAG], char map[X_MAG][Y_MAG])
{
    npc* npc = malloc(sizeof(*npc));
    
    //initialize our basic values
    npc->x = x;
    npc->y = y;
    npc->type = type;
    npc->cost = cost_map[x][y];
    npc->terrain = map[x][y];

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
    char_map[x][y] = 1;

    heapNode_t* ht;
    ht = malloc(sizeof(heapNode_t*));
    ht->npc = npc;

    return ht;
}

void next_player_turn(heapNode_t* hn, int c, char map[X_MAG][Y_MAG], 
        int rival_cost_map[X_MAG][Y_MAG],
        int character_map[X_MAG][Y_MAG],
        square* sq)
{

        //move to the lower left
        if(c == '1' || c == 'b')
        {
            sq->px -= 1;
            sq->py += 1;
        }
        //move down
        else if(c == '2' || c == 'j')
        {
            sq->py += 1;
        }
        //move to lower right
        else if(c == '3' || c == 'n')
        {
            sq->px += 1;
            sq->py += 1;
        }
        //move one cell to left
        else if(c == '4' || c == 'h')
        {
            sq->px -= 1;
        }
        //rest
        else if(c == '5' || c == ' ' || c == '.')
        {
            ;
        }
        //move one cell to the right
        else if(c == '6' || c == 'l')
        {
            sq->px += 1;
        }
        //move to the upper left
        else if(c == '7' || c == 'y')
        {
            sq->px -= 1;
            sq->py -= 1;
        }
        //move one cell up
        else if(c == '8' || c == 'k')
        {
            sq->py -= 1;
        }
        else if(c == '9' || c == 'u')
        {
            sq->px += 1;
            sq->py -= 1;
        }
        move_npc(hn->npc, map, rival_cost_map, character_map, sq->px, sq->py); 
}
//void move_npc(npc* c, char map[X_MAG][Y_MAG], int cost_map[X_MAG][Y_MAG],
//        int character_map[X_MAG][Y_MAG], int new_x, int new_y)
//{
void next_turn(heap_t* h, char map[X_MAG][Y_MAG], 
        int hiker_cost_map[X_MAG][Y_MAG],
        int rival_cost_map[X_MAG][Y_MAG],
        int character_map[X_MAG][Y_MAG],
        int rival_dij[X_MAG][Y_MAG],
        int hiker_dij[X_MAG][Y_MAG], 
        square* sq)
{
    heapNode_t* hn = extractMin_t(h); 
    int c;
    switch(hn->npc->type)
    {
        case 'h':
            chase(hn->npc, map, hiker_cost_map, character_map, hiker_dij);
            break;
        case 'w':
            wander(hn->npc, map, rival_cost_map, character_map);
            break;
        case 'p':
            pace(hn->npc, map, rival_cost_map, character_map);
            break;
        case 'e':
            explore(hn->npc, map, rival_cost_map, character_map);
            break;
        case 'r':
            chase(hn->npc, map, rival_cost_map, character_map, rival_dij);
            break;
        case '@':
            c = getch();
            next_player_turn(hn, c, map, rival_cost_map, character_map, sq);
            break;
            
    }
    
    add_npc(h, hn);

}

 
