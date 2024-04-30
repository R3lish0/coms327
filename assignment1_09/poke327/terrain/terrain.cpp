//libraries for output and random number gen
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <ncurses.h>
#include "../queue/queue.h"
#include "../terrain/terrain.h"
//defining board size

#define S_GRASS 1
#define T_GRASS 2
#define PATH 3
#define WATER 4
#define MOUNTAIN 5
#define NPC 6
#define PLAYER 7
#define MART 8
#define CENTER 9




void printSquare(class square *sq)
{
//    clear();
    erase();
    refresh();
    init_pair(S_GRASS, COLOR_GREEN, COLOR_GREEN);
    init_pair(T_GRASS, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(PATH, COLOR_WHITE, COLOR_WHITE);
    init_pair(WATER, COLOR_BLUE, COLOR_BLUE);
    init_pair(MOUNTAIN, COLOR_WHITE, COLOR_BLACK);
    init_pair(NPC, COLOR_BLACK, COLOR_RED);
    init_pair(PLAYER, COLOR_BLACK, COLOR_MAGENTA);
    init_pair(MART, COLOR_BLUE, COLOR_WHITE);
    init_pair(CENTER, COLOR_RED, COLOR_WHITE);

    for(int i = 0; i < Y_MAG; i++)
    {
        for(int j = 0; j < X_MAG; j++)
        {
            switch(sq->map[j][i])
            {
                case '.':
                    attron(COLOR_PAIR(S_GRASS));
                    mvaddch(i+1,j,sq->map[j][i]);
                    attroff(COLOR_PAIR(S_GRASS));
                    break;
                case ':':
                    attron(COLOR_PAIR(T_GRASS));
                    mvaddch(i+1,j,sq->map[j][i]);
                    attroff(COLOR_PAIR(T_GRASS));
                    break;
                case '~':
                    attron(COLOR_PAIR(WATER));
                    mvaddch(i+1,j,sq->map[j][i]);
                    attroff(COLOR_PAIR(WATER));
                    break;
                case '%':
                    attron(COLOR_PAIR(MOUNTAIN)); 
                    mvaddch(i+1,j,sq->map[j][i]);
                    attroff(COLOR_PAIR(MOUNTAIN));
                    break;
                case '#':
                    attron(COLOR_PAIR(PATH));
                    mvaddch(i+1,j,sq->map[j][i]);
                    attroff(COLOR_PAIR(PATH));
                    break;
                case '@':
                    attron(COLOR_PAIR(PLAYER));
                    mvaddch(i+1,j,sq->map[j][i]);
                    attroff(COLOR_PAIR(PLAYER));
                    break;
                case 'C':
                    attron(COLOR_PAIR(CENTER));
                    mvaddch(i+1,j,sq->map[j][i]);
                    attroff(COLOR_PAIR(CENTER));
                    break;
                case 'M':
                    attron(COLOR_PAIR(MART));
                    mvaddch(i+1,j,sq->map[j][i]);
                    attroff(COLOR_PAIR(MART));
                    break;
                default:
                    attron(COLOR_PAIR(NPC));
                    mvaddch(i+1,j,sq->map[j][i]);
                    attroff(COLOR_PAIR(NPC));
                    break;
            }
        }
    }
}


//this will determine where the seeds will start 
void seedGen(class seeds *sd, class square *sq)
{
    int randx;
    int randy;
    int seedLocal[6][2] = {{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}};
    //generating seed for random gen
    for(int i = 0; i < 6; i++)
    {
       randx =  1+(rand() % (X_MAG - 2));
       randy = 1+(rand() % (Y_MAG - 2));
       sd->seedLocations[i][0] = randx;
       sd->seedLocations[i][1] = randy;


       
    }

    //now that we have the positions_b for our seeds generated lets compare
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
            temp_dif_x =abs(sd->seedLocations[i][0] - sd->seedLocations[j][0]);  
            temp_dif_y =abs(sd->seedLocations[i][1] - sd->seedLocations[j][1]); 
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
        

    //we need 
    //2 :
    //1 ~
    //2 .
    //1 %
    //So 6 total biomes (but for there to be 2 for some
    //they cannot be next to each other?)
    //
    //we have to make clearing on opposite sides of map
    //we also have to make tall grass on opposite sides of map
    
    //here we set the double biomes and then set them as "-1"
    sq->map[sd->seedLocations[first_pair[0]][0]][sd->seedLocations[first_pair[0]][1]] = ':';
    sq->map[sd->seedLocations[second_pair[0]][0]][sd->seedLocations[second_pair[0]][1]] = '.';
    sq->map[sd->seedLocations[first_pair[1]][0]][sd->seedLocations[first_pair[1]][1]] = ':';
    sq->map[sd->seedLocations[second_pair[1]][0]][sd->seedLocations[second_pair[1]][1]] = '.';
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
                sq->map[sd->seedLocations[i][0]][sd->seedLocations[i][1]] = '~';
                water = -1;
            }
            else
            {
                sq->map[sd->seedLocations[i][0]][sd->seedLocations[i][1]] = '%';
            }
            seedLocal[i][0] = -1;
        }

    }


}
int checkSquare(class queue *q, class square *sq, int offsetX, int offsetY)
{
    //this checks if the square is empty or not and then queues the next square if empty
    int* temp_arr;
    int t_arr[2] =  {q->head->location[0]+offsetX,q->head->location[1]+offsetY};
    if(sq->map[q->head->location[0]+offsetX][q->head->location[1]+offsetY] == 'f')
    {
        sq->map[q->head->location[0]+offsetX][q->head->location[1]+offsetY] = q->head->val;
        temp_arr = &t_arr[0];
        queue_enqueue(q,temp_arr, q->head->val);
    }  
    return 0;
}

//this will handle the growing of the seeds
int grow(class seeds *sd, class square *sq) 
{
    class queue q;
    queue_init(&q);
    char val;
   
    for(int i = 0; i < 6; i++)
    {
        int local[2] = {sd->seedLocations[i][0],sd->seedLocations[i][1]};
        val = sq->map[sd->seedLocations[i][0]][sd->seedLocations[i][1]];
        queue_enqueue(&q, local,val); 
    }
    while(queue_length(&q) > 0)
    {
        //QUEUE TIME
        checkSquare(&q,sq,1,0);
        checkSquare(&q,sq,0,1);
        checkSquare(&q,sq,-1,0);
        checkSquare(&q,sq,0,-1);
        checkSquare(&q,sq,1,-1);
        checkSquare(&q,sq,-1,1);

        queue_dequeue(&q, q.head->location, &q.head->val);
    }
    queue_destroy(&q);
    return 0;
}

int pathChangeUp(class square *sq, int i, int c)
{
    sq->map[i][c] = (sq->map[i][c]  == 'C' || sq->map[i][c] == 'M') ? sq->map[i][c] : '#'; 
    sq->map[i-1][c] = (sq->map[i-1][c]  == 'C' || sq->map[i-1][c] == 'M') ? sq->map[i-1][c] : '#';
    sq->map[i][c-1] = (sq->map[i][c-1] == 'C' || sq->map[i][c-1] == 'M') ? sq->map[i][c-1] : '#';
    sq->map[i+1][c] = (sq->map[i+1][c]  == 'C' || sq->map[i+1][c] == 'M') ? sq->map[i+1][c] : '#';
    sq->map[i+1][c-1] = (sq->map[i+1][c-1]  == 'C' || sq->map[i+1][c-1] == 'M') ? sq->map[i+1][c-1] : '#';
    return 0;
}
int pathChangeDown(class square *sq, int i, int c)
{
    sq->map[i][c] = (sq->map[i][c] == 'C' || sq->map[i][c] == 'M') ? sq->map[i][c] : '#'; 
    sq->map[i][c+1] = (sq->map[i][c+1] == 'C' || sq->map[i][c+1] == 'M') ? sq->map[i][c+1] : '#';
    sq->map[i-1][c] = (sq->map[i-1][c]  == 'C' || sq->map[i-1][c] == 'M') ? sq->map[i-1][c] : '#';
    sq->map[i+1][c] = (sq->map[i+1][c]  == 'C' || sq->map[i+1][c] == 'M') ? sq->map[i+1][c] : '#';
    sq->map[i+1][c+1] = (sq->map[i+1][c+1]  == 'C' || sq->map[i+1][c+1] == 'M') ? sq->map[i+1][c+1] : '#';
    return 0;
}
//this will handle last touches like path gen and buildings
int manMade(class square *sq, int pk)
{
    class queue q;
    queue_init(&q);
   
    int e;
    int n;
    int w;
    int s;
    int quota = (rand() % 10)+3;
    int delta;
    int ch = 0;
   
    int edge_top = 0;
    int edge_bottom = 0;
    int edge_left = 0;
    int edge_right = 0;


    int player = 4;



    if(sq->n == -1)
    {
       edge_top = 1;
       sq->n = 0;
    }
    
    if(sq->s == -1)
    {
        edge_bottom = 1;
        sq->s = 0;
    }

    if(sq->w == -1)
    {
        edge_left = 1;
        sq->w = 0;
    }

    if(sq->e == -1)
    {
        edge_right = 1;
        sq->e = 0;
    }

    



    //gen starting or just put starting
    sq->e = (sq->e == 0) ? 7+(rand() % (Y_MAG - 14)) : sq->e;
    sq->n = (sq->n == 0) ? (rand() % (52-37)+ 30) : sq->n;  
    sq->w = (sq->w == 0) ? 7+(rand() % (Y_MAG - 14)) : sq->w;
    sq->s = (sq->s == 0) ? (rand() % (52-37) + 30) : sq->s;
    
    //e and w are swapped because im bad with directions and switched them
    w = sq->e;
    n = sq->n;
    e = sq->w;
    s = sq->s;
    
    int poke = -1;
     
    if(pk)
    {
        poke = 5+(rand() % (X_MAG - 9));
        if(abs(n - poke) <= 10) 
        {
            if(n > 40)
            {
                poke-=20;
            }
            else
            {
                poke+=20;
            }
        }
    }
    sq->martX = poke; 
    double multiplier_x;
    double multiplier_y;


    if(edge_right)
    {
        multiplier_x = 0.75;
    }
    else
    {
        multiplier_x = 1;
    }
    if(edge_bottom)
    {
        multiplier_y = 0.75;
    }
    else
    {
        multiplier_y = 1;
    }


    
    delta = abs(e - w);
    for(int i = 0; i < X_MAG*multiplier_x; i++)
    {
        if(edge_left)
        {
            i+=20;
            edge_left = 0;
        }

        if(i+3 == (X_MAG-(delta*2+5)))
        {
            quota = 0;
        }

        sq->map[i][e] = '#';
        if(i > (X_MAG - (delta*2+5)) && delta != 0)
        {
            if(e < w)
            {
                e++;
                delta--;
                pathChangeUp(sq,i,e);
            }
            else
            {
                e--;
                delta--;
                pathChangeDown(sq,i,e);
            }
        }
        else if(i < (X_MAG - 15) && quota != 0)
        {
            if(i % 15 == 0 && quota != 0 && i != 0)
            {
                ch = (rand() % 2);
                if(ch == 1)
                {
                    e++;
                    quota--;
                    pathChangeUp(sq, i, e);
                }
                else
                {
                    e--;
                    quota--;
                    pathChangeDown(sq, i, e);
                }

            }
            delta = abs(e-w);
        }

        if(i == poke)
            {
                sq->map[i][e+1] = 'M';
                sq->map[i][e+2] = 'M';
                sq->map[i][e-1] = 'C';
                sq->map[i][e-2] = 'C';

                sq->map[i+1][e+1] = 'M';
                sq->map[i+1][e+2] = 'M';
                sq->map[i+1][e-1] = 'C';
                sq->map[i+1][e-2] = 'C';

                sq->martY = e;


            }
        if(i == player)
            {
                sq->px = i;
                sq->py = e;
            }

    }
    delta = abs(n - s);
    quota = (rand() % 6);

    for(int i = 0; i < Y_MAG*multiplier_y; i++)
    {
        if(edge_top)
        {
            i+=5;
            edge_top = 0;
        }
    



        if(i+3 == (Y_MAG-(18)))
        {
            quota = 0;
        }

        sq->map[n][i] = '#';
        if(i > (Y_MAG - (17)) && delta != 0)
        {
            if(n < s)
            {
                n++;
                delta--;
                sq->map[n][i] = '#';
                sq->map[n-1][i] = '#';
                sq->map[n][i-1] = '#';



            }
            else
            {
                n--;
                delta--;
                sq->map[n][i] = '#';
                sq->map[n+1][i] = '#';
                sq->map[n][i+1] = '#';
            }
        }
        else if(i < (Y_MAG - 5) && quota != 0)
        {
            if(i % 3 == 0 && quota != 0 && i != 0)
            {
                ch = (rand() % 2);
                if(ch == 1)
                {
                    n++;
                    quota--;
                    sq->map[n][i] = '#';
                    sq->map[n-1][i] = '#';
                    sq->map[n][i-1] = '#';

                }
                else
                {
                    n--;
                    quota--;
                    sq->map[n][i] = '#';
                    sq->map[n+1][i] = '#';
                    sq->map[n][i+1] = '#';
                }

            }
            delta = abs(n-s);
        }
    }
    return 0;
}



int genSquare(square *sq, int n, int s, int e, int w, int pk)
{
    
    //we love a simple main()
    srand((unsigned)time(NULL));

    for(int i = 0; i < X_MAG; i++)
    {
        for(int j = 0; j < Y_MAG; j++)
        {
            if (i == 0 || i == X_MAG - 1 || j == 0 || j == Y_MAG - 1)
            {
                sq->map[i][j] = '%';
            }
            else
            {

                sq->map[i][j] = 'f';
            }

        }
    }
    


    class seeds seed;
    for(int i = 0; i < 6; i++)
    {
        for(int j = 0; j < 2; j++)
        {
            seed.seedLocations[i][j] = 0;
        }
    }

    sq->n = n;
    sq->s = s;
    sq->e = e;
    sq->w = w;
                
    for(int i = 0; i < X_MAG; i++)
    {
        for(int j = 0; j < Y_MAG; j++)
        {
            sq->char_map[i][j] = -1;
        }
    }

    seedGen(&seed, sq);
    grow(&seed, sq);
    manMade(sq, pk);
    return 0;
}




int initBoard(board *bd)
{
    //init starting square 
    square *sq;


    if(!(sq = (class square*)malloc(sizeof(*sq))))
    {
        return 1;
    }

    
    genSquare(sq,0,0,0,0,1);
    //lets init a board
    for(int i = 0; i < BOARD_X; i++)
    {
        for(int j = 0; j < BOARD_Y; j++)
        {
            bd->board[i][j] = NULL;
        }
    }
    bd->curX = 200;
    bd->curY = 200;

    bd->board[200][200] = sq;

    return 0;
}

int checkTile(board *bd, int x, int y)
{


    int pk;
    int xk = abs(x-200);
    int yk = abs(y-200);
    
    pk = xk + yk;
    


    if((rand() % 400) < abs(pk))
    {
        pk = 0;
    }
    else
    {
        pk = 1;
    }

    if(bd->board[x][y] == NULL)
    {
        square *sq;
        if(!(sq = (class square*)malloc(sizeof(*sq))))
        {
            return 1;
        }

                
       

        int e;
        int w;
        int s;
        int n;
        if(!(x == 400)){e=(!(bd->board[x+1][y] == NULL)) ? bd->board[x+1][y]->w : 0;}
        else{ e = -1;}
        if(!(x == 0)){w = (!(bd->board[x-1][y] == NULL)) ? bd->board[x-1][y]->e : 0;}
        else{ w = -1;}
        if(!(y == 400)){n = (!(bd->board[x][y+1] == NULL)) ? bd->board[x][y+1]->s : 0;}
        else{n = -1;}
        if(!(y == 0)){s = (!(bd->board[x][y-1] == NULL)) ? bd->board[x][y-1]->n : 0;}
        else{s = -1;}

        genSquare(sq,n,s,e,w,pk);
        bd->board[x][y] = sq; 
    }
    bd->curX=x;
    bd->curY=y;

    return 0;
}













