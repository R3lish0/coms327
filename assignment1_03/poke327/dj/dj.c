#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "dj.h"

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
    h->arr = (heapNode*)malloc(capacity * sizeof(heapNode));
 
    // Checking if memory is allocated to h or not
    if (h->arr == NULL) {
        printf("Memory error");
        return NULL;
    }
    int i = 1000; 
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
 
    if (h->arr[parent].dist > h->arr[index].dist) {
        // Swapping when child is smaller
        // than parent element
        int temp = h->arr[parent].dist;
        h->arr[parent].dist = h->arr[index].dist;
        h->arr[index].dist = temp;
 
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
    if (left != -1 && h->arr[left].dist < h->arr[index].dist)
        min = left;
    if (right != -1 && h->arr[right].dist < h->arr[min].dist)
        min = right;
 
    // Swapping the nodes
    if (min != index) {
        int temp = h->arr[min].dist;
        h->arr[min].dist = h->arr[index].dist;
        h->arr[index].dist = temp;
 
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
    deleteItem = &h->arr[0];
 
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
        h->arr[h->size] = *hn;
        // Calling insertHelper function
        insertHelper(h, h->size);
        // Incrementing size of array
        h->size++;
    }
}
 
void printHeap(heap* h)
{
 
    for (int i = 0; i < h->size; i++) {
        printf("%f ", h->arr[i].dist);
    }
    printf("\n");
}
 
void initCostMap(board *bd, float hiker_cost_map[X_MAG][Y_MAG], float rival_cost_map[X_MAG][Y_MAG])
{
    

    for(int i = 0; i < X_MAG; i++)
    {
        for(int j = 0; j < Y_MAG; j++)
        {
            if(i == 0 || j == 0 || j == 20 || i == 79)
            {
                hiker_cost_map[i][j] = INFINITY;
                rival_cost_map[i][j] = INFINITY;
            }
            else
            {
                switch(bd->board[bd->curX][bd->curY]->map[i][j])
                {
                    case '~':
                        hiker_cost_map[i][j] = INFINITY;
                        rival_cost_map[i][j] = INFINITY;
                        break;
                    case '.':
                        hiker_cost_map[i][j] = 10;
                        rival_cost_map[i][j] = 10;
                        break;
                    case ':':
                        hiker_cost_map[i][j] = 15;
                        rival_cost_map[i][j] = 15;
                        break;
                    case '%':
                        hiker_cost_map[i][j] = 15;
                        rival_cost_map[i][j] = 15;
                        break;
                    case '#':
                        hiker_cost_map[i][j] = 10;
                        rival_cost_map[i][j] = 10;
                        break;
                    case 'M':
                        hiker_cost_map[i][j] = 50;
                        rival_cost_map[i][j] = 50;
                        break;
                    case 'C':
                        hiker_cost_map[i][j] = 50;
                        rival_cost_map[i][j] = 50;
                        break;
                    case '@':
                        hiker_cost_map[i][j] = 0;
                        rival_cost_map[i][j] = 0;
                        break;
                    default:
                        hiker_cost_map[i][j] = -1;
                        rival_cost_map[i][j] = -1;
                        break;
                }
            }
        }
    }

    //for(int i = 0; i < Y_MAG; i++)
    //{
    //    for(int j = 0; j < X_MAG; j++)
    //    {
    //       printf("%g ", (hiker_cost_map[j][i]));
    //    }
    //    printf("\n");
    //}
    //printf("\n\n\n\n");
    //for(int i = 0; i < Y_MAG; i++)
    //{
    //    for(int j = 0; j < X_MAG; j++)
    //    {
    //       printf("%g ", (rival_cost_map[j][i]));
    //    }
    //    printf("\n");
    //}
}

int dijkstra(board* bd, float hiker_cost_map[MAG_X][MAG_Y], float rival_cost_map[MAG_X][MAG_Y])
{
    heapNode* hiker_dist_map[MAG_X][MAG_Y];
    heapNode* rival_dist_map[MAG_X][MAG_Y];

    heap* h = createHeap(80*21);

    
    for(int i = 0; i < 80; i++)
    {
        for(int j = 0; j < 21; j++)
        {
            heapNode *rt;
            heapNode *ht;
            if(!(rt = malloc(sizeof(*rt)))){return 1;}
            if(!(ht = malloc(sizeof(*ht)))){return 1;}

            rt->dist = INFINITY;
            ht->dist = INFINITY;

            rt->x = i;
            ht->x = i;

            rt->y = j;
            ht->y = j;

            rt->cost = rival_cost_map[i][j];
            ht->cost = hiker_cost_map[i][j];

            rt->visited = 0;
            ht->visited = 0;
            
            hiker_dist_map[i][j] = ht;
            rival_dist_map[i][j] = rt;


        }
    }
    heapNode *hn;
    if(!(hn = malloc(sizeof(*hn))))
    {
        return 1; 
    }
    hn->dist = 0;
    hn->x = bd->board[bd->curX][bd->curY]->px;
    hn->y = bd->board[bd->curX][bd->curY]->py;
    hn->cost = 0;
    hn->visited = 1;
    insert(h, hn);

    rival_dist_map[hn->x][hn->y] = hn;
    hiker_dist_map[hn->x][hn->y] = hn;






    
    while(h->size != 0)
    { 
        heapNode* curr = extractMin(h);

        if(curr->x != 79)
        {
            if(!rival_dist_map[(curr->x)+1][(curr->y)]->visited)
            {
                insert(h,rival_dist_map[(curr->x)+1][(curr->y)]);
                rival_dist_map[(curr->x)+1][(curr->y)]->visited = 1;
            }
        }
        if(curr->x != 0)
        {
            if(!rival_dist_map[(curr->x)-1][(curr->y)]->visited)
            {
                insert(h,rival_dist_map[(curr->x)-1][(curr->y)]);
                rival_dist_map[(curr->x)-1][(curr->y)]->visited = 1;
            }
        }

        if(curr->y != 20)
        {
            if(!rival_dist_map[(curr->x)][(curr->y)+1]->visited)
            {
                insert(h,rival_dist_map[(curr->x)][(curr->y)+1]);
                rival_dist_map[(curr->x)][(curr->y)+1]->visited = 1;
            }
        }

        if(curr->y != 0)
        {
            if(!rival_dist_map[(curr->x)][(curr->y)-1]->visited)
            {
                insert(h,rival_dist_map[(curr->x)][(curr->y)-1]);
                rival_dist_map[(curr->x)][(curr->y)-1]->visited = 1;
            }
        }

        if(curr->x != 79 && curr->y != 20)
        {
            if(!rival_dist_map[(curr->x)+1][(curr->y)+1]->visited)
            {
                insert(h,rival_dist_map[(curr->x)+1][(curr->y)+1]);
                rival_dist_map[(curr->x)+1][(curr->y)+1]->visited = 1;
            }
        }

        if(curr->x != 79 && curr->y != 0)
        {
            if(!rival_dist_map[(curr->x)+1][(curr->y)-1]->visited)
            {
                insert(h,rival_dist_map[(curr->x)+1][(curr->y)-1]);
                rival_dist_map[(curr->x)+1][(curr->y)-1]->visited = 1;
            }
        }

        if(curr->x != 0 && curr->y != 20){
            if(!rival_dist_map[(curr->x)-1][(curr->y)+1]->visited)
            {
                insert(h,rival_dist_map[(curr->x)-1][(curr->y)+1]);
                rival_dist_map[(curr->x)-1][(curr->y)+1]->visited = 1;
            }
        }

        if(curr->x != 0 && curr->y != 0)
        {
            if(!rival_dist_map[(curr->x)-1][(curr->y)-1]->visited)
            {
                insert(h,rival_dist_map[(curr->x)-1][(curr->y)-1]);
                rival_dist_map[(curr->x)-1][(curr->y)-1]->visited = 1;
            }
        }
    }

   for(int i = 0; i < 80; i++)
    {
        for(int j = 0; j < 21; j++)
        {
            printf("This is the hiker node at %d , %d --",hiker_dist_map[i][j]->x, hiker_dist_map[i][j]->y);
            printf(" its dist is %f, and it's cost is %f",hiker_dist_map[i][j]->dist, hiker_dist_map[i][j]->cost);

            printf("\n\n");

            printf("This is the hiker node at %d , %d --",rival_dist_map[i][j]->x, rival_dist_map[i][j]->y);
            printf(" its dist is %f, and it's cost is %f",rival_dist_map[i][j]->dist, rival_dist_map[i][j]->cost);


            printf("\n\n");
        }
    }
 return 0;

}
