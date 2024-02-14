#ifndef DJ_H
#define DJ_H

typedef struct heap{
    int *arr; 
    int size;
    int capacity;
} heap;

heap* createHeap(int capacity, int *nums);
void insert(heap* h, int data);
int extractMin(heap* h);
void insertHelper(heap* h, int index);
void heapify(heap* h, int index);






#endif
