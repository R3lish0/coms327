//libraries for output and random number gen
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
//defining board size
#define X_MAG 80
#define Y_MAG 21



//this will determine where the seeds will start 
void seedGen(int (*seedLocations)[6][2], char (*map)[X_MAG][Y_MAG])
{
    //generating seed for random gen
    for(int i = 0; i < 6; i++)
    {
       *seedLocations[i][0] = rand() % X_MAG;
       *seedLocations[i][1] = rand() % Y_MAG;
       sleep(0.3); 
       
    }

    //now that we have the positions for our seeds generated lets compare
    //and make sure that our 2 tall grass and 2 clearings are as far apart as possible
    int first_dif = 0;
    int first_pair[2] = {0,0};
    int second_dif = 0;
    int second_pair[2] = {0,0};
    int temp_dif;
    for(int i = 0; i < 6; i++)
    {
        for(int j = 1; j < 6; j++)
        {
            temp_dif =abs(*seedLocations[i][0] - *seedLocations[j][0]);  
            if(temp_dif > second_dif)
            {
                if(temp_dif > first_dif)
                {
                    first_dif = temp_dif;
                    first_pair[0] = i;
                    first_pair[1] = j;
                }
                else if(temp_dif != first_dif && first_pair[0] != i && first_pair[1] != j && first_pair[0] != j && first_pair[1] != i)
                {
                    second_dif = temp_dif;
                    second_pair[0] = i;
                    second_pair[1] = j;
                }
            }
        }
    }
    //epic, now that we have the two most farthest pairs on the x-axis
    //we have to assign all the pairs to their respective biomes
        

    //we need 2 :
    //1 ~
    //2 .
    //1 %
    //So 6 total biomes (but for there to be 2 for some
    //they cannot be next to each other?)
    //
    //we have to make clearing on opposite sides of map
    //we also have to make tall grass on opposite sides of map
   int local = *seedLocations[first_pair[0]][0];
   int local2 = *seedLocations[first_pair[0]][1];
  // *map[local][local2] = ':';

   printf("%d with pair %d and %d \n", first_dif, first_pair[0], first_pair[1]);
   printf("%d with pair %d and %d \n", second_dif, second_pair[0], second_pair[1]); 


   for(int i = 0; i < 6; i++)
   {
       printf("%d\n",*seedLocations[i][0]);
       printf("%d\n",*seedLocations[i][1]);
   }


}

//this will handle the growing of the seeds
int grow()
{
}

//this will handle last touches like path gen and buildings
int manMade()
{
}



int main()
{

    srand((unsigned)time(NULL));
    char map[X_MAG][Y_MAG];
    for(int i = 0; i < X_MAG; i++)
    {
        for(int j = 0; j < Y_MAG; j++)
        {
            map[i][j] = 'w';

        }
    }
    
    int seedLocations[6][2] = {{0,0},{0,0},{0,0},{0,0},{0,0}};
     

 


   
    seedGen(&seedLocations, &map);

    
    return 0;
}

















