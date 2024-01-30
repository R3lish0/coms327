//libraries for output and random number gen
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
//defining board size
#define X_MAG 80
#define Y_MAG 21



//this will determine where the seeds will start 
void seedGen(int (*seedLocations)[6][2])
{
    //we need 2 :
    //1 ~
    //2 .
    //1 %
    //So 6 total biomes (but for there to be 2 for some
    //they cannot be next to each other?)
    //
    //we have to make clearing on opposite sides of map
    //we also have to make tall grass on opposite sides of map



    //generating seed for random gen
      
    for(int i = 0; i < 6; i++)
    {
       *seedLocations[i][0] = rand() % X_MAG;
       *seedLocations[i][1] = rand() % Y_MAG;
       sleep(0.3); 
       
    }
}


int main()
{

    srand((unsigned)time(NULL));
    int map[X_MAG][Y_MAG];
    int seedLocations[6][2] = {{0,0},{0,0},{0,0},{0,0},{0,0}};
    for(int i = 0; i < X_MAG; i++)
    {
        for(int j = 0; j < Y_MAG; j++)
        {
            map[i][j] = 0;
        }
    }

    int (*seedPointer)[6][2] = &seedLocations;
    
    seedGen(seedPointer);

    for(int i = 0; i < 6;i++)
    {
        printf("%d\n", (*seedPointer[i][0]));
        printf("%d\n", (*seedPointer[i][1]));
        printf("pause\n");
    }


    printf("hello");
    return 0;
}



//this will handle the growing of the seeds
int grow()
{
}

//this will handle last touches like path gen and buildings
int manMade()
{
}





