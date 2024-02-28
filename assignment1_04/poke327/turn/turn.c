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


#include "../turn/turn.h"
#include "../terrain/terrain.h"


// Define a createHeap function
heap* createHeap(int capacity)
{
    // Allocating memory to heap h
    heap* h = (heap*)malloc(sizeof(heap));
 
    // Checking if memory is allocated to h or not
    if (h == NULL) {
        printf("Memory error");
        return NULL;
    }
    // set the values to size and capacity
    h->size = 0;
    h->capacity = capacity;
 
    // Allocating memory to array
    h->arr = malloc(capacity * sizeof(heapNode*));
 
    // Checking if memory is allocated to h or not
    if (h->arr == NULL) {
        printf("Memory error");
        return NULL;
    }
    int i = 0; 
    h->size = i;
    i = (h->size - 2) / 2;
    while (i >= 0) {
        heapify(h, i);
        i--;
    }
    return h;
}
 
// Defining insertHelper function
void insertHelper(heap* h, int index)
{
 
    // Store parent of element at index
    // in parent variable
    int parent = (index - 1) / 2;
 
    if (h->arr[parent]->cost > h->arr[index]->cost) {
        // Swapping when child is smaller
        // than parent element
        heapNode* temp = h->arr[parent];
        h->arr[parent] = h->arr[index];
        h->arr[index] = temp;
 
        // Recursively calling insertHelper
        insertHelper(h, parent);
    }
}
 
void heapify(heap* h, int index)
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
    if (left != -1 && h->arr[left]->cost < h->arr[index]->cost)
        min = left;
    if (right != -1 && h->arr[right]->cost < h->arr[min]->cost)
        min = right;
 
    // Swapping the nodes
    if (min != index) {
        heapNode* temp = h->arr[min];
        h->arr[min] = h->arr[index];
        h->arr[index] = temp;
 
        // recursively calling for their child elements
        // to maintain min heap
        heapify(h, min);
    }
}
 
heapNode* extractMin(heap* h)
{
    heapNode* deleteItem;
 
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
    heapify(h, 0);
    return deleteItem;
}
 
// Define a insert function
void insert(heap* h, heapNode* hn)
{
 
    // Checking if heap is full or not
    if (h->size < h->capacity) {
        // Inserting data into an array
        h->arr[h->size] = hn;
        // Calling insertHelper function
        insertHelper(h, h->size);
        // Incrementing size of array
        h->size++;
    }
}


void compare(int x, int y, int min_pair[2], int* min, int cost_map[X_MAG][Y_MAG])
{
    if (cost_map[x][y] < *min)
    {
        *min = cost_map[x][y];
    }
    min_pair[0]=x;
    min_pair[1]=y;

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


void move(npc* c, char map[X_MAG][Y_MAG], int cost_map[X_MAG][Y_MAG],
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
            move(p, map, cost_map, character_map, p->x, p->y-1);
        }
        else
        {
            move(p, map, cost_map, character_map, p->x, p->y+1);
            p->cur_dir = random_turn('N');
        }
    }
    else if(p->cur_dir == 'S')
    {
        if(p->y < 20 && cost_map[p->x][p->y+1] != INT16_MAX)
        {
            move(p, map, cost_map, character_map, p->x, p->y+1);
        }
        else
        {
            move(p, map, cost_map, character_map, p->x, p->y-1);
            p->cur_dir = random_turn('S');
        }
    }
    else if(p->cur_dir == 'E')
    {
        if(p->x < 79 && cost_map[p->x+1][p->y] != INT16_MAX)
        {
            move(p, map, cost_map, character_map, p->x+1, p->y);
        }
        else
        {
            move(p, map, cost_map, character_map, p->x-1, p->y);
            p->cur_dir = random_turn('E');
        }
    }
    else if(p->cur_dir == 'W')
    {
        if(p->x > 0 && cost_map[p->x-1][p->y] != INT16_MAX)
        {
            move(p, map, cost_map, character_map, p->x-1, p->y);
        }
        else
        {
            move(p, map, cost_map, character_map, p->x+1, p->y);
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
        if(p->y > 0 && map[p->x][p->y-1] != p->terrain)
        {
            move(p, map, cost_map, character_map, p->x, p->y-1);
        }
        else
        {
            move(p, map, cost_map, character_map, p->x, p->y+1);
            p->cur_dir = random_turn('N');
        }
    }
    else if(p->cur_dir == 'S')
    {
        if(p->y < 20 && map[p->x][p->y+1] != p->terrain)
        {
            move(p, map, cost_map, character_map, p->x, p->y+1);
        }
        else
        {
            move(p, map, cost_map, character_map, p->x, p->y-1);
            p->cur_dir = random_turn('S');
        }
    }
    else if(p->cur_dir == 'E')
    {
        if(p->x < 79 && map[p->x+1][p->y] != p->terrain)
        {
            move(p, map, cost_map, character_map, p->x+1, p->y);
        }
        else
        {
            move(p, map, cost_map, character_map, p->x-1, p->y);
            p->cur_dir = random_turn('E');
        }
    }
    else if(p->cur_dir == 'W')
    {
        if(p->x > 0 && map[p->x-1][p->y] != p->terrain)
        {
            move(p, map, cost_map, character_map, p->x-1, p->y);
        }
        else
        {
            move(p, map, cost_map, character_map, p->x+1, p->y);
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
            move(p, map, cost_map, character_map, p->x, p->y-1);
        }
        else
        {
            move(p, map, cost_map, character_map, p->x, p->y+1);
            p->cur_dir = 'S';
        }
    }
    else if(p->cur_dir == 'S')
    {
        if(p->y < 20 && cost_map[p->x][p->y+1] != INT16_MAX)
        {
            move(p, map, cost_map, character_map, p->x, p->y+1);
        }
        else
        {
            move(p, map, cost_map, character_map, p->x, p->y-1);
            p->cur_dir = 'N';
        }
    }
    else if(p->cur_dir == 'E')
    {
        if(p->x < 79 && cost_map[p->x+1][p->y] != INT16_MAX)
        {
            move(p, map, cost_map, character_map, p->x+1, p->y);
        }
        else
        {
            move(p, map, cost_map, character_map, p->x-1, p->y);
            p->cur_dir = 'W';
        }
    }
    else if(p->cur_dir == 'W')
    {
        if(p->x > 0 && cost_map[p->x-1][p->y] != INT16_MAX)
        {
            move(p, map, cost_map, character_map, p->x-1, p->y);
        }
        else
        {
            move(p, map, cost_map, character_map, p->x+1, p->y);
            p->cur_dir = 'E';
        }
    }

}

void chase(npc* c,char map[X_MAG][Y_MAG], int cost_map[X_MAG][Y_MAG],
        int character_map[X_MAG][Y_MAG])
{
    int min_pair[2];
    int min = INT16_MAX;
    
    if(c->x < 79)
    {
        compare(c->x+1, c->y, min_pair, &min, cost_map);
    }

    if(c->y < 20)
    {
        compare(c->x, c->y+1, min_pair, &min, cost_map);
    }

    if(c->x > 0)
    {
        compare(c->x-1, c->y, min_pair, &min, cost_map);
    }

    if(c->y > 0)
    {
        compare(c->x, c->y-1, min_pair, &min, cost_map);
    }

    if(c->x < 79 && c->y < 20)
    {
        compare(c->x+1, c->y+1, min_pair, &min, cost_map);
    }

    if(c->x > 0 && c->y > 0)
    {
        compare(c->x-1, c->y-1, min_pair, &min, cost_map);
    }

    if(c->x > 0 && c->y < 20)
    {
        compare(c->x-1, c->y+1, min_pair, &min, cost_map);
    }

    if(c->x < 79 && c->y > 0)
    {
        compare(c->x+1, c->y-1, min_pair, &min, cost_map);
    }
    //requeue

}
