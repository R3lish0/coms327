#ifndef PRI_H
#define PRI_H

typedef struct node{
    int x;
    int y;
    int weight;
} node;




int swap(node *a,node *b);
int heapify(node* array[], int size, int i);
int insert(node* array[], node *newNode);
int deleteRoot(node* array[], node *target);

#endif
