//libraries for output and random number gen
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "queue.h"

//defining board size
#define X_MAG 80
#define Y_MAG 21



int queue_init(struct queue *q)
{
    //head and tail don't point to anything -> they point to NULL
    //Null is the NULL pointer. It is defined as:
    //(void *) 0
    q->head = q->tail = NULL;
    q->length = 0;
    

    return 0;
}
int queue_destroy(struct queue *q)
{
    struct queue_node *n;

    for (n = q->head; n; n = q->head) {
        q->head = q->head->next;
        free(n);
    }
    q->length = 0;
    q->tail = NULL;
      
    return 0;
}
int queue_enqueue(struct queue *q, int l[2], char c)
{
    struct queue_node *tmp;
    

    //sizeof is a compile-time (static operator). It gives the static size
    //the expression given as its parameter
    //Idiomatically: x = malloc(sizeof (*x)) returns enough bytes to store
    //whatever x is
    if(!(tmp = malloc(sizeof(*tmp))))
    {
        return 1;
    }

    tmp->val = c;
    tmp->location[0] = l[0];
    tmp->location[1] = l[1];
    tmp->next = NULL;

    if (!q->head) 
    { //queue is empty
        q->head = q->tail = tmp;
    }
    else
    {
        q->tail->next = tmp;
        q->tail = tmp;
    }
    q->length++;
    return 0;

}
int queue_dequeue(struct queue *q, int location[2], char *val)
{
    struct queue_node *n;
    if(!q->head)
    {
        return 1;
    }
    n = q->head;
    q->head = q->head->next;
    *val = n->val;
    free(n);

    if (!q->head)
    {
        q->tail = NULL;
    }

    q->length--;
    return 0;
}
int queue_length(struct queue *q)
{
    return q->length;
}
int queue_is_empty(struct queue *q)
{
    return !q->head;
}

void printMap(char map[X_MAG][Y_MAG])
{
    for(int i = Y_MAG-1; i >= 0; i--)
    {
        for(int j = 0; j < X_MAG; j++)
        {
            printf("%c", map[j][i]);
        }
        printf("\n");
    }
}


//this will determine where the seeds will start 
void seedGen(int seedLocations[6][2], char map[X_MAG][Y_MAG])
{
    int randx;
    int randy;
    int seedLocal[6][2] = {{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}};
    //generating seed for random gen
    for(int i = 0; i < 6; i++)
    {
       randx =  1+(rand() % (X_MAG - 2));
       randy = 1+(rand() % (Y_MAG - 2));
       seedLocations[i][0] = randx;
       seedLocations[i][1] = randy;


       
    }

    //now that we have the positions for our seeds generated lets compare
    //and make sure that our 2 tall grass and 2 clearings are as far apart as possible
    int first_dif = 0;
    int first_pair[2] = {0,0};
    int second_dif = 0;
    int second_pair[2] = {0,0};
    int temp_dif_x;
    int temp_dif_y;
    int temp_dif;
    for(int i = 0; i < 6; i++)
    {
        for(int j = 1; j < 6; j++)
        {
            temp_dif_x =abs(seedLocations[i][0] - seedLocations[j][0]);  
            temp_dif_y =abs(seedLocations[i][1] - seedLocations[j][1]); 
            temp_dif = temp_dif_y + temp_dif_x;
            if(temp_dif > second_dif)
            {
                if(temp_dif > first_dif && second_pair[0] != i && second_pair[1] != j && second_pair[0] != j && second_pair[1] != i)
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
    
    //here we set the double biomes and then set them as "-1"
    map[seedLocations[first_pair[0]][0]][seedLocations[first_pair[0]][1]] = ':';
    map[seedLocations[second_pair[0]][0]][seedLocations[second_pair[0]][1]] = '.';
    map[seedLocations[first_pair[1]][0]][seedLocations[first_pair[1]][1]] = ':';
    map[seedLocations[second_pair[1]][0]][seedLocations[second_pair[1]][1]] = '.';
    seedLocal[first_pair[0]][0] = -1;
    seedLocal[first_pair[1]][0] = -1;
    seedLocal[second_pair[0]][0] = -1;
    seedLocal[second_pair[1]][0] = -1;


   //this printed the differences between the top most different pairs

   // printf("%d with pair %d and %d \n", first_dif, first_pair[0], first_pair[1]);
   // printf("%d with pair %d and %d \n", second_dif, second_pair[0], second_pair[1]); 

    //here we set the other biomes   

    int seedx;
    int water = 0;
    for(int i = 0; i < 6; i++)
    {
        seedx = seedLocal[i][0]; 
        if(!(seedx == -1))   
        {
            if(water == 0)
            {
                map[seedLocations[i][0]][seedLocations[i][1]] = '~';
                water = -1;
            }
            else
            {
                map[seedLocations[i][0]][seedLocations[i][1]] = '%';
            }
            seedLocal[i][0] = -1;
        }

    }


}
int checkSquare(struct queue *q, char map[X_MAG][Y_MAG], int offsetX, int offsetY)
{
    //this checks if the square is empty or not and then queues the next square if empty
    if(map[q->head->location[0]+offsetX][q->head->location[1]+offsetY] == 'f')
    {
        map[q->head->location[0]+offsetX][q->head->location[1]+offsetY] = q->head->val;
        queue_enqueue(*&q, (int[2]) {q->head->location[0]+offsetX,q->head->location[1]+offsetY}, q->head->val);
    }  
    return 0;
}

//this will handle the growing of the seeds
int grow(int seedLocations[6][2], char map[X_MAG][Y_MAG]) 
{
    struct queue q;
    queue_init(&q);
    char c;
    char val;
   
    for(int i = 0; i < 6; i++)
    {
        int local[2] = {seedLocations[i][0],seedLocations[i][1]};
        val = map[seedLocations[i][0]][seedLocations[i][1]];
        queue_enqueue(&q, local,val); 
    }
    while(queue_length(&q) > 0)
    {
        //QUEUE TIME
        checkSquare(&q,map,1,0);
        checkSquare(&q,map,0,1);
        checkSquare(&q,map,-1,0);
        checkSquare(&q,map,0,-1);
        checkSquare(&q,map,1,-1);
        checkSquare(&q,map,-1,1);

        queue_dequeue(&q, q.head->location, &q.head->val);
    }
    return 0;
}


//this will handle last touches like path gen and buildings
int manMade(char map[X_MAG][Y_MAG])
{
    struct queue q;
    queue_init(&q);
    
    //using these numbers for these cause I dont want them close to the edge
    int ew =  7+(rand() % (Y_MAG - 15));
    int ns = 5+(rand() % (X_MAG - 12));


    //make sure that NE path doesnt eat buildings
    int poke = 2+(rand() % (X_MAG - 5));
    if(abs(ns -  poke) <= 10) 
    {
        if(ns > 40)
        {
            poke-=20;
        }
        else
        {
            poke+=20;
        }
    }
    for(int i = 0; i < X_MAG; i++)
    {
        //this is an ew path
        map[i][ew] = '#';
        if(i % 12  == 0)
        {
            int rando = rand() % 10;
            if(rando >= 5 && ew < Y_MAG-1)
            {
                ew++;
                map[i][ew] = (map[i][ew]  == 'C' || map[i][ew] == 'M') ? map[i][ew] : '#'; 
                map[i-1][ew] = (map[i-1][ew]  == 'C' || map[i-1][ew] == 'M') ? map[i-1][ew] : '#';
                map[i][ew-1] = (map[i][ew-1] == 'C' || map[i][ew-1] == 'M') ? map[i][ew-1] : '#';
                map[i+1][ew] = (map[i+1][ew]  == 'C' || map[i+1][ew] == 'M') ? map[i+1][ew] : '#';
                map[i+1][ew-1] = (map[i+1][ew-1]  == 'C' || map[i+1][ew-1] == 'M') ? map[i+1][ew-1] : '#';
            }
            else if(rando < 5 && ew > 1) 
            {
                ew--;
                map[i][ew] = (map[i][ew] == 'C' || map[i][ew] == 'M') ? map[i][ew] : '#'; 
                map[i][ew+1] = (map[i][ew+1] == 'C' || map[i][ew+1] == 'M') ? map[i][ew+1] : '#';
                map[i-1][ew] = (map[i-1][ew]  == 'C' || map[i-1][ew] == 'M') ? map[i-1][ew] : '#';
                map[i+1][ew] = (map[i+1][ew]  == 'C' || map[i+1][ew] == 'M') ? map[i+1][ew] : '#';
                map[i+1][ew+1] = (map[i+1][ew+1]  == 'C' || map[i+1][ew+1] == 'M') ? map[i+1][ew+1] : '#';

            }


        }
        //spawns the buildings 
        if(i == poke)
        {
           map[i][ew+1] = 'M';
           map[i][ew+2] = 'M';
           map[i][ew-1] = 'C';
           map[i][ew-2] = 'C';

           map[i+1][ew+1] = 'M';
           map[i+1][ew+2] = 'M';
           map[i+1][ew-1] = 'C';
           map[i+1][ew-2] = 'C';


        }


    
    }
    //this is the NS path
    for(int j = 0; j < Y_MAG; j++)
    {
        map[ns][j] = '#';
        if(j % 5  == 0)
        {
            int rando = rand() % 10;
            if(rando >= 5 && ns < X_MAG-1)
            {
                ns++;
                map[ns][j] = '#';
                map[ns-1][j] = '#';
                map[ns][j-1] = '#';
            }
            else if(rando < 5 && ns > 1) 
            {
                ns--;
                map[ns][j] = '#';
                map[ns+1][j] = '#';
                map[ns][j+1] = '#';
            }
        }
    }




    return 0;
}



int main()
{


    //we love a simple main()
    srand((unsigned)time(NULL));
    char map[X_MAG][Y_MAG];
    for(int i = 0; i < X_MAG; i++)
    {
        for(int j = 0; j < Y_MAG; j++)
        {
            if (i == 0 || i == X_MAG - 1 || j == 0 || j == Y_MAG - 1)
            {
                map[i][j] = '%';
            }
            else
            {

                map[i][j] = 'f';
            }

        }
    }
     
    
    int seedLocations[6][2] = {{0,0},{0,0},{0,0},{0,0},{0,0}};
    

    seedGen(seedLocations, map);
    grow(seedLocations, map);
    manMade(map);
    printMap(map);
    



    return 0;
}

















