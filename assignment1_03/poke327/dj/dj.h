#ifndef DJ_H
#define DJ_H
#define MAG_X 81
#define MAG_Y 20

# include "../terrain/terrain.h"
# include <stdint.h>

struct Heap {
    int* arr;
    int size;
    int capacity;
};
 
// define the struct Heap name
typedef struct Heap heap;
 
// forward declarations
heap* createHeap(int capacity, int* nums);
void insertHelper(heap* h, int index);
void heapify(heap* h, int index);
int extractMin(heap* h);
void insert(heap* h, int data);
void initCostMap(board* bd);
void djkstra(char* board);



#endif
