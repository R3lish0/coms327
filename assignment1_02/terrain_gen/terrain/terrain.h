#include "../queue/queue.h"

#ifndef TERRAIN_H
#define TERRAIN_H

#define X_MAG 80
#define Y_MAG 21

typedef struct square{
    char map[X_MAG][Y_MAG];
    int n;
    int s;
    int e;
    int w;
} square;

typedef struct seeds{
    int seedLocations[6][2];
} seeds;



void printSquare(square *sq);
void seedGen(seeds *sd, square *sq);
int checkSquare(queue *q, square *sq, int offsetX, int offsetY);
int grow(seeds *sd, square *sq);
int manMade(square *sq);
int genSquare(square *sq, int n, int s, int e, int w);




#endif
