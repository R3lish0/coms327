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


#include "../terrain/terrain.h"

#ifndef TURN_H 
#define TURN_H


#define X_MAG 80
#define Y_MAG 21


typedef struct npc {
    int x;
    int y;
    int cost;
    int index;
    int is_defeated;
    char type;
    char terrain;
    char cur_dir;    
} npc;


typedef struct HeapNode_t {
    npc* npc; 
} heapNode_t;

typedef struct Heap_t { 
    heapNode_t** arr;
    int size;
    int capacity;
} heap_t;



// define the struct Heap name
// forward declarations
heap_t* createHeap_t(int capacity);
void insertHelper_t(heap_t* h, int index);
void heapify_t(heap_t* h, int index);
heapNode_t* extractMin_t(heap_t* h);
void insert_t(heap_t* h, heapNode_t* hn);


void compare(int x,int y,int min_pair[2], int* min, int dij[X_MAG][Y_MAG]);

char random_turn(char except);

void move_npc(npc* c, char map[X_MAG][Y_MAG], int cost_map[X_MAG][Y_MAG],
        int character_map[X_MAG][Y_MAG], int new_x, int new_y);

void chase(npc* c, char map[X_MAG][Y_MAG],
        int cost_map[X_MAG][Y_MAG],
        int character_map[X_MAG][Y_MAG],
        int dijkstra[X_MAG][Y_MAG]);

void pace(npc* p, char map[X_MAG][Y_MAG],
        int cost_map[X_MAG][Y_MAG], int character_map[X_MAG][Y_MAG]); 

void wander(npc* w, char map[X_MAG][Y_MAG],
        int cost_map[X_MAG][Y_MAG], int character_map[X_MAG][Y_MAG]);

void explore(npc* e, char map[X_MAG][Y_MAG],
        int cost_map[X_MAG][Y_MAG], int character_map[X_MAG][Y_MAG]);

heapNode_t* create_npc(int index, int x, int y, char type, int cost_map[X_MAG][Y_MAG],
        int char_map[X_MAG][Y_MAG], char map[X_MAG][Y_MAG]);

heap_t* init_turn_heap(int capacity);

void add_npc(heap_t* h, heapNode_t* ht);

int next_turn(heap_t* h, char map[X_MAG][Y_MAG], 
        int hiker_cost_map[X_MAG][Y_MAG],
        int rival_cost_map[X_MAG][Y_MAG],
        int pc_cost_map[X_MAG][Y_MAG],
        int character_map[X_MAG][Y_MAG],
         int rival_dij[X_MAG][Y_MAG],
         int hiker_dij[X_MAG][Y_MAG],
         square* sq);

#endif
