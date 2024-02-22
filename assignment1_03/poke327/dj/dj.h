#ifndef DJ_H
#define DJ_H
#define MAG_X 80
#define MAG_Y 21

# include "../terrain/terrain.h"
# include <stdint.h>
# include <stdbool.h>



typedef struct HeapNode {
    float dist;
    float cost;
    int x;
    int y;
    bool visited;
} heapNode;

typedef struct Heap {
    heapNode* arr;
    int size;
    int capacity;
} heap;


// define the struct Heap name
// forward declarations
heap* createHeap(int capacity);
void insertHelper(heap* h, int index);
void heapify(heap* h, int index);
heapNode* extractMin(heap* h);
void insert(heap* h, heapNode* hn);
void initCostMap(board* bd, float hiker_cost_map[MAG_X][MAG_Y], float rival_cost_map[MAG_X][MAG_Y]);
int dijkstra(board* bd, float hiker_cost_map[MAG_X][MAG_Y], float rival_cost_map[MAG_X][MAG_Y]);



#endif
