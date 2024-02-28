//This file will super cool things like:
//Hold all the player types
//Hikers: h - Hikers path to the PC by following a maximum gradient on the 
//hiker map
//
//Rival: r - Rivals path to the PC by following a maximum gradient on the 
//rival map
//
//Pacers: p - Pacers start with a direction a walk until they hit some terrain
//they cannot traverse, then they turn around and repeat, pacing back and forth
//
//Wanderers: w - Wanderers never leave the terrain region they were spawn in.
//they have a direction and wlk straight ahead to the edge of terrain, whereupon
//they turn in a random direction and repeat.
//
//Sentries: s- Sentries don't move; they just wait for the action to come to 
//them
//
//Explorers: e - Explorers move like wanderers, but they cross terrain type
//boundaries, only changing to a new, random direction when they reach an
//impassable terrain element
//
#ifndef TURN_H 
#define TURN_H
#include "../terrain/terrain.h"

typedef struct npc {
    int x;
    int y;
    int cost;
    char type;
    char terrain;
    char cur_dir;    
} npc;


typedef struct HeapNode {
    npc* npc; 
    int cost;
} heapNode;

typedef struct Heap {
    heapNode** arr;
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


void compare(int x,int y,int min_pair[2], int* min, int cost_map[X_MAG][Y_MAG]);

char random_turn(char except);

void move(npc* c, char map[X_MAG][Y_MAG], int cost_map[X_MAG][Y_MAG],
        int character_map[X_MAG][Y_MAG], int new_x, int new_y);

void chase(npc* c, char map[X_MAG][Y_MAG],
        int cost_map[X_MAG][Y_MAG], int character_map[X_MAG][Y_MAG]);

void pace(npc* p, char map[X_MAG][Y_MAG],
        int cost_map[X_MAG][Y_MAG], int character_map[X_MAG][Y_MAG]); 

void wander(npc* w, char map[X_MAG][Y_MAG],
        int cost_map[X_MAG][Y_MAG], int character_map[X_MAG][Y_MAG]);

void explore(npc* e, char map[X_MAG][Y_MAG],
        int cost_map[X_MAG][Y_MAG], int character_map[X_MAG][Y_MAG]);



#endif
