//This file will super cool things like:
//Hold all the player types
//Hikers: h - Hikers path to the PC by following a maximum gradient on the 
//hiker map
//
//Rival: r - Rivals path to the PC by following a maximum gradient on the 
//rival map
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
#include "../main/main.h"
#include <string>

#ifndef TURN_H 
#define TURN_H


#define X_MAG 80
#define Y_MAG 21


typedef class npc {
    public:
    int x;
    int y;
    int cost;
    int index;
    int is_defeated;
    char type;
    char terrain;
    char cur_dir;    
    int team[6];
    int bag[3];
} npc;


typedef class HeapNode_t {
    public:
    npc* h_npc; 
} heapNode_t;

typedef class Heap_t { 
    public:
    heapNode_t** arr;
    int size;
    int capacity;
} heap_t;



// define the class Heap name
// forward declarations
heap_t* createHeap_t(int capacity);
void insertHelper_t(heap_t* h, int index);
void heapify_t(heap_t* h, int index);
heapNode_t* extractMin_t(heap_t* h);
void insert_t(heap_t* h, heapNode_t* hn);


void compare(int x,int y,int min_pair[2], int* min, int dij[X_MAG][Y_MAG]);

char random_turn(char except);

int move_npc(npc* c, char map[X_MAG][Y_MAG], int cost_map[X_MAG][Y_MAG],
        int character_map[X_MAG][Y_MAG], int new_x, int new_y);

int chase(npc* c, char map[X_MAG][Y_MAG],
        int cost_map[X_MAG][Y_MAG],
        int character_map[X_MAG][Y_MAG],
        int dijkstra[X_MAG][Y_MAG]);

int pace(npc* p, char map[X_MAG][Y_MAG],
        int cost_map[X_MAG][Y_MAG], int character_map[X_MAG][Y_MAG]); 

int wander(npc* w, char map[X_MAG][Y_MAG],
        int cost_map[X_MAG][Y_MAG], int character_map[X_MAG][Y_MAG]);

int explore(npc* e, char map[X_MAG][Y_MAG],
        int cost_map[X_MAG][Y_MAG], int character_map[X_MAG][Y_MAG]);

heapNode_t* create_npc(int index, int x, int y, char type, int cost_map[X_MAG][Y_MAG],
        int char_map[X_MAG][Y_MAG], char map[X_MAG][Y_MAG]);

heap_t* init_turn_heap(int capacity);

void add_npc(heap_t* h, heapNode_t* ht);

int next_turn(heap_t* h, char map[X_MAG][Y_MAG], 
        int hiker_cost_map[X_MAG][Y_MAG],
        int rival_cost_map[X_MAG][Y_MAG],
        int pc_cost_map[X_MAG][Y_MAG],
         int rival_dij[X_MAG][Y_MAG],
         int hiker_dij[X_MAG][Y_MAG],
         square* sq,
         heapNode_t** npc_arr_board[BOARD_X][BOARD_Y],
         int n,
         board* bd,
         heap_t* queue_array[401][401],
        std::vector<saved_poke*>& saved_poke_list,
        std::vector<moves*>& moves_vec, std::vector<pokemon_moves*>& pokemon_moves_vec,
        std::vector<pokemon*>& pokemon_vec, std::vector<pokemon_stats*>& pokemon_stats_vec,
        std::vector<pokemon_types*>& pokemon_types_vec);


void init_new_square(board *bd,int hiker_cost_map[X_MAG][Y_MAG], 
        int hiker_dij_map[X_MAG][Y_MAG],
        int rival_cost_map[X_MAG][Y_MAG],
        int rival_dij_map[X_MAG][Y_MAG],
        int pc_cost_map[X_MAG][Y_MAG],
        heapNode_t** npc_arr_board[BOARD_X][BOARD_Y],
        heap_t* queue_array[BOARD_X][BOARD_Y],
        int npc_count);

#endif
