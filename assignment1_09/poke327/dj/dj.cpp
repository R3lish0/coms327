#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    h->arr = (heapNode**)malloc(capacity * sizeof(heapNode*));
 
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
 
    if (h->arr[parent]->dist > h->arr[index]->dist) {
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
    if (left != -1 && h->arr[left]->dist < h->arr[index]->dist)
        min = left;
    if (right != -1 && h->arr[right]->dist < h->arr[min]->dist)
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
 
 
void initCostMap(square* sq, 
        int hiker_cost_map[X_MAG][Y_MAG], 
        int rival_cost_map[X_MAG][Y_MAG],
        int pc_cost_map[X_MAG][Y_MAG])

{
    

    for(int i = 0; i < X_MAG; i++)
    {
        for(int j = 0; j < Y_MAG; j++)
        {
            if(i == 0 || j == 0 || j == 20 || i == 79)
            {
                hiker_cost_map[i][j] = INT16_MAX;
                rival_cost_map[i][j] = INT16_MAX;
                pc_cost_map[i][j] = INT16_MAX;
            }
            else
            {
                switch(sq->map[i][j])
                {
                    case '~':
                        hiker_cost_map[i][j] = INT16_MAX;
                        rival_cost_map[i][j] = INT16_MAX;
                        pc_cost_map[i][j] = INT16_MAX;
                        break;
                    case '.':
                        hiker_cost_map[i][j] = 10;
                        rival_cost_map[i][j] = 10;
                        pc_cost_map[i][j] = 10;
                        break;
                    case ':':
                        hiker_cost_map[i][j] = 15;
                        rival_cost_map[i][j] = 20;
                        pc_cost_map[i][j] = 20;
                        break;
                    case '%':
                        hiker_cost_map[i][j] = 15;
                        rival_cost_map[i][j] = INT16_MAX;
                        pc_cost_map[i][j] = INT16_MAX;
                        break;
                    case '#':
                        hiker_cost_map[i][j] = 10;
                        rival_cost_map[i][j] = 10;
                        pc_cost_map[i][j] = 10;
                        break;
                    case 'M':
                        hiker_cost_map[i][j] = 50;
                        rival_cost_map[i][j] = 50;
                        pc_cost_map[i][j] = 10;
                        break;
                    case 'C':
                        hiker_cost_map[i][j] = 50;
                        rival_cost_map[i][j] = 50;
                        pc_cost_map[i][j] = 10;
                        break;
                    case '@':
                        hiker_cost_map[i][j] = 0;
                        rival_cost_map[i][j] = 0;
                        pc_cost_map[i][j] = 0;
                        break;
                    default:
                        hiker_cost_map[i][j] = -1;
                        rival_cost_map[i][j] = -1;
                        pc_cost_map[i][j] = -1;
                        break;
                }
            }
        }
    }

}

int dijkstra(square* sq, int hiker_cost_map[MAG_X][MAG_Y], 
        int rival_cost_map[MAG_X][MAG_Y],
        int rival_dij_map[MAG_X][MAG_Y],
        int hiker_dij_map[MAG_X][MAG_Y])
{
    heapNode* hiker_dist_map[MAG_X][MAG_Y];
    heapNode* rival_dist_map[MAG_X][MAG_Y];

    heap* h = createHeap(80*21);
    heap* h2 = createHeap(80*21);
    
    for(int i = 0; i < 80; i++)
    {
        for(int j = 0; j < 21; j++)
        {
            heapNode *rt = (heapNode*)malloc(sizeof(*rt));
            heapNode *ht = (heapNode*)malloc(sizeof(*ht));

            rt->dist = INT16_MAX;
            ht->dist = INT16_MAX;

            rt->x = i;
            ht->x = i;

            rt->y = j;
            ht->y = j;

            rt->cost = rival_cost_map[i][j];
            ht->cost = hiker_cost_map[i][j];

            rt->visited = 0;
            ht->visited = 0;
            
            rival_dist_map[i][j] = rt;
            hiker_dist_map[i][j] = ht;

        }
    }
    heapNode *hn = (heapNode*)malloc(sizeof(*hn));
    hn->dist = 10;
    hn->x = sq->px;
    hn->y = sq->py;
    hn->cost = 0;
    hn->visited = 1;
    insert(h, hn);
    insert(h2, hn);
    rival_dist_map[hn->x][hn->y] = hn;
    hiker_dist_map[hn->x][hn->y] = hn;



    while(h->size != 0)
    {

        heapNode* curr = extractMin(h);
        heapNode* tmp = NULL;

        if(curr->x < 79)
        {

            if(!rival_dist_map[(curr->x)+1][(curr->y)]->visited)
            {
                rival_dist_map[(curr->x)+1][(curr->y)]->visited = 1;
                if(rival_dist_map[(curr->x)+1][(curr->y)]->cost != INT16_MAX)
                {
                    rival_dist_map[(curr->x)+1][(curr->y)]->dist = curr->dist + rival_dist_map[(curr->x)+1][(curr->y)]->cost;
                    insert(h,rival_dist_map[(curr->x)+1][(curr->y)]);
                }
            }
        }
        if(curr->x > 0)
        {
            tmp = rival_dist_map[(curr->x)-1][(curr->y)];
            if(!tmp->visited)
            {
                tmp->visited = 1; 
                if(tmp->cost != INT16_MAX)
                { 
                    tmp->dist = curr->dist + tmp->cost;
                    insert(h,tmp);
                }

            }
            tmp = NULL;
        }

        if(curr->y < 20)
        {
            tmp = rival_dist_map[(curr->x)][(curr->y)+1];
            if(!tmp->visited)
            {
                tmp->visited = 1; 
                if(tmp->cost != INT16_MAX)
                { 
                    tmp->dist = curr->dist + tmp->cost;
                    insert(h,tmp);
                }
            }
            tmp = NULL;
        }

        if(curr->y > 0)
        {
            tmp = rival_dist_map[(curr->x)][(curr->y)-1];
            if(!tmp->visited)
            {
                tmp->visited = 1;
                if(tmp->cost != INT16_MAX)
                { 
                    tmp->dist = curr->dist + tmp->cost;
                    insert(h,tmp);
                }
            }
            tmp = NULL;
        }

        if(curr->x < 79 && curr->y < 20)
        {
            tmp = rival_dist_map[(curr->x)+1][(curr->y)+1];
            if(!tmp->visited)
            {
                tmp->visited = 1;
                if(tmp->cost != INT16_MAX)
                { 
                    tmp->dist = curr->dist + tmp->cost;
                    insert(h,tmp);
                }
            } 
            tmp = NULL;
        }

        if(curr->x < 79 && curr->y > 0)
        {
            tmp = rival_dist_map[(curr->x)+1][(curr->y)-1];
            if(!tmp->visited)
            {
                tmp->visited = 1;
                if(tmp->cost != INT16_MAX)
                { 
                    tmp->dist = curr->dist + tmp->cost;
                    insert(h,tmp);
                }
            }
            tmp = NULL;
        }

        if(curr->x > 0 && curr->y < 20)
        {
            tmp = rival_dist_map[(curr->x)-1][(curr->y)+1];
            if(!tmp->visited)
            {
                tmp->visited = 1;
                if(tmp->cost != INT16_MAX)
                { 
                    tmp->dist = curr->dist + tmp->cost;
                    insert(h,tmp);
                }
            }
            tmp = NULL;
        }

        if(curr->x > 0 && curr->y > 0)
        {
            tmp = rival_dist_map[(curr->x)-1][(curr->y)-1];
            if(!tmp->visited)
            {
                tmp->visited = 1;
                if(tmp->cost != INT16_MAX)
                { 
                    tmp->dist = curr->dist + tmp->cost;
                    insert(h,tmp);
                }
            }
            tmp = NULL;
        }
    }
   printf("\n\n\n");
   for(int i = 1; i < 20; i++)
    {
        for(int j = 1; j < 79; j++)
        {
    
           rival_dij_map[j][i] = rival_dist_map[j][i]->dist;

        }
    }





   while(h2->size != 0)
   {

       heapNode* curr = extractMin(h2);
       heapNode* tmp = NULL;
       if(curr->x < 79)
       {

           tmp = hiker_dist_map[(curr->x)+1][(curr->y)];
           if(!tmp->visited)
           {
               tmp->visited = 1;
               if(tmp->cost != INT16_MAX)
               {
                   tmp->dist = curr->dist + tmp->cost;
                   insert(h2,tmp);
               }
           }
           tmp = NULL;
       }
       if(curr->x > 0)
       {
           tmp = hiker_dist_map[(curr->x)-1][(curr->y)];
           if(!tmp->visited)
           {
               tmp->visited = 1; 
               if(tmp->cost != INT16_MAX)
               { 
                   tmp->dist = curr->dist + tmp->cost;
                   insert(h2,tmp);
               }

           }
           tmp = NULL;
       }

       if(curr->y < 20)
       {
           tmp = hiker_dist_map[(curr->x)][(curr->y)+1];
           if(!tmp->visited)
           {
               tmp->visited = 1; 
               if(tmp->cost != INT16_MAX)
               { 
                   tmp->dist = curr->dist + tmp->cost;
                   insert(h2,tmp);
               }
           }
           tmp = NULL;
       }

       if(curr->y > 0)
       {
           tmp = hiker_dist_map[(curr->x)][(curr->y)-1];
           if(!tmp->visited)
           {
               tmp->visited = 1;
               if(tmp->cost != INT16_MAX)
               { 
                   tmp->dist = curr->dist + tmp->cost;
                   insert(h2,tmp);
               }
           }
           tmp = NULL;
       }

       if(curr->x < 79 && curr->y > 20)
       {
           tmp = hiker_dist_map[(curr->x)+1][(curr->y)+1];
           if(!tmp->visited)
           {
               tmp->visited = 1;
               if(tmp->cost != INT16_MAX)
               { 
                   tmp->dist = curr->dist + tmp->cost;
                   insert(h2,tmp);
               }
           } 
           tmp = NULL;
       }

       if(curr->x < 79 && curr->y > 0)
       {
           tmp = hiker_dist_map[(curr->x)+1][(curr->y)-1];
           if(!tmp->visited)
           {
               tmp->visited = 1;
               if(tmp->cost != INT16_MAX)
               { 
                   tmp->dist = curr->dist + tmp->cost;
                   insert(h2,tmp);
               }
           }
           tmp = NULL;
       }

       if(curr->x > 0 && curr->y < 20)
       {
           tmp = hiker_dist_map[(curr->x)-1][(curr->y)+1];
           if(!tmp->visited)
           {
               tmp->visited = 1;
               if(tmp->cost != INT16_MAX)
               { 
                   tmp->dist = curr->dist + tmp->cost;
                   insert(h2,tmp);
               }
           }
           tmp = NULL;
       }

       if(curr->x > 0 && curr->y > 0)
       {
           tmp = hiker_dist_map[(curr->x)-1][(curr->y)-1];
           if(!tmp->visited)
           {
               tmp->visited = 1;
               if(tmp->cost != INT16_MAX)
               { 
                   tmp->dist = curr->dist + tmp->cost;
                   insert(h2,tmp);
               }
           }
           tmp = NULL;
       }
   }
   printf("\n\n\n");
   
   for(int i = 1; i < 20; i++)
   {
       for(int j = 1; j < 79; j++)
       {

           hiker_dij_map[j][i] = hiker_dist_map[j][i]->dist;

       }
   }




 return 0;

}
