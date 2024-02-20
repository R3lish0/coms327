#ifndef DJ_H
#define DJ_H


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

void djkstra(char* board);



#endif
