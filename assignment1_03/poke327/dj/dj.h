#ifndef DJ_H
#define DJ_H


#define V 9

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

int minDistance(int dist[], bool sptSet[]);
void printSolution(int dist[]);
void dijkstra(int graph[V][V], int src);




#endif
