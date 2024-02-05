#include "../queue/queue.h"

#ifndef TERRAIN_H
#define TERRAIN_H

#define X_MAG 80
#define Y_MAG 21

struct square{
    char map[X_MAG][Y_MAG];
};

struct seeds{
    int seedLocations[6][2];
};



void printMap(struct square *sq);
void seedGen(struct seeds *sd, struct square *sq);
int checkSquare(struct queue *q, struct square *sq,int offsetX, int offsetY);
int grow(struct seeds *sd, struct square *sq);
int manMade(struct square *sq);
int genMap(struct square *sq);




#endif
