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
#include "../dj/dj.h"


typedef struct Character {
    char type;
    int x;
    int y;
} character;





#endif
