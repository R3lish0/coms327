//check out this super cool C file
//
//ok here's what I have to do
//
//First create a heap 
//then get next move all characters and add them to heap
//then go through the heap and select next move for each character
//
//Things to consider
//
//characters cannot collide
//
//we need to check depending on character
//  If we need to do something like uhh turn around (we need turn function)
//
//  sentries might be a little hard to be honest
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ncurses.h>
#include <unistd.h>
#include <string>
#include <limits.h>

#include "../turn/turn.h"
#include "../terrain/terrain.h"
#include "../dj/dj.h"
#include "../data/data.h"

using namespace std;


// Define a createHeap function
heap_t* createHeap_t(int capacity)
{
    // Allocating memory to heap h
    heap_t* h = (heap_t*)malloc(sizeof(heap_t));
 
    // Checking if memory is allocated to h or not
    if (h == NULL) {
        printf("Memory error");
        return NULL;
    }
    // set the values to size and capacity
    h->size = 0;
    h->capacity = capacity;
 
    // Allocating memory to array
    h->arr = (heapNode_t**)malloc(capacity * sizeof(heapNode_t*));
 
    // Checking if memory is allocated to h or not
    if (h->arr == NULL) {
        printf("Memory error");
        return NULL;
    }
    int i = 0; 
    h->size = i;
    i = (h->size - 2) / 2;
    while (i >= 0) {
        heapify_t(h, i);
        i--;
    }
    return h;
}
 
// Defining insertHelper function
void insertHelper_t(heap_t* h, int index)
{
 
    // Store parent of element at index
    // in parent variable
    int parent = (index - 1) / 2;
 
    if (h->arr[parent]->h_npc->cost > h->arr[index]->h_npc->cost) {
        // Swapping when child is smaller
        // than parent element
        heapNode_t* temp = h->arr[parent];
        h->arr[parent] = h->arr[index];
        h->arr[index] = temp;
 
        // Recursively calling insertHelper
        insertHelper_t(h, parent);
    }
}
 
void heapify_t(heap_t* h, int index)
{
    int left = index * 2 + 1;
    int right = index * 2 + 2;
    int min = index;
 
    // Checking whether our left or child element
    // is at right index or not to avoid index error
    if (left >= h->size || left < 0)
        left = -1;
    if (right >= h->size || right < 0)
        right = -1;
 
    // store left or right element in min if
    // any of these is smaller that its parent
    if (left != -1 && h->arr[left]->h_npc->cost < h->arr[index]->h_npc->cost)
        min = left;
    if (right != -1 && h->arr[right]->h_npc->cost < h->arr[min]->h_npc->cost)
        min = right;
 
    // Swapping the nodes
    if (min != index) {
        heapNode_t* temp = h->arr[min];
        h->arr[min] = h->arr[index];
        h->arr[index] = temp;
 
        // recursively calling for their child elements
        // to maintain min heap
        heapify_t(h, min);
    }
}
 
heapNode_t* extractMin_t(heap_t* h)
{
    heapNode_t* deleteItem;
 
    // Checking if the heap is empty or not
    if (h->size == 0) {
        printf("\nHeap id empty.");
        return NULL;
    }
 
    // Store the node in deleteItem that
    // is to be deleted.
    deleteItem = h->arr[0];
 
    // Replace the deleted node with the last node
    h->arr[0] = h->arr[h->size - 1];
    // Decrement the size of heap
    h->size--;
 
    // Call minheapify_top_down for 0th index
    // to maintain the heap property
    heapify_t(h, 0);
    return deleteItem;
}
 
// Define a insert function
void insert_t(heap_t* h, heapNode_t* hn)
{
 
    // Checking if heap is full or not
    if (h->size < h->capacity) {
        // Inserting data into an array
        h->arr[h->size] = hn;
        // Calling insertHelper function
        insertHelper_t(h, h->size);
        // Incrementing size of array
        h->size++;
    }
}


void print_pokemon_card(WINDOW* win, vector<saved_poke*>& saved_poke_list,
        vector<moves*>& moves_vec,std::vector<pokemon_moves*>& pokemon_moves_vec,
        std::vector<pokemon*>& pokemon_vec, std::vector<pokemon_stats*>& pokemon_stats_vec,
        int pokemon)
{
    
    werase(win);
    box(win, '|', '-');
    init_pair(1, COLOR_GREEN, COLOR_GREEN);
    init_pair(2, COLOR_RED, COLOR_RED);
    saved_poke* curr_pokemon = saved_poke_list.at(pokemon);
    mvwprintw(win, 1,2,"%s", curr_pokemon->poke->identifier.c_str());     
    mvwprintw(win, 2,2,"Lvl: %d", curr_pokemon->level);     
    mvwprintw(win, 3,12,"HP: %d/%d", curr_pokemon->curr_hp, curr_pokemon->hp);     
    int health = curr_pokemon->curr_hp >= 0 ? (curr_pokemon->curr_hp * 20)/curr_pokemon->hp : 0;



    wattron(win, COLOR_PAIR(1));
    for(int i = 0; i <= health; i++)
    {
        mvwprintw(win, 4,i+2,"=");     
    }
    wattroff(win, COLOR_PAIR(1));

    wattron(win,  COLOR_PAIR(2));
    for(int i = health; i < 20; i++)
    {
        mvwprintw(win, 4,i+2,"=");     
    }
    wattroff(win,  COLOR_PAIR(2));

    wrefresh(win);


}

void print_moves(WINDOW* win, vector<saved_poke*>& saved_poke_list,
        int poke)
{
    werase(win);
    box(win, '|', '-');
    mvwprintw(win, 1,2, "%s", "Choose an available move");
    for(long unsigned int i = 0; i < saved_poke_list.at(poke)->
            move_list.size(); i++)
    {
        
        mvwprintw(win, 2+i, 2, "%lu: %s", i+1,  saved_poke_list.at(poke)->move_list.at(i)->identifier.c_str());     
    }
    wrefresh(win);
}


void print_options(WINDOW* win)
{

    werase(win);
    box(win, '|', '-');

    init_pair(5, COLOR_GREEN, COLOR_BLACK);
    init_pair(6, COLOR_RED, COLOR_BLACK);
    init_pair(7, COLOR_BLUE, COLOR_BLACK);
    init_pair(8, COLOR_YELLOW, COLOR_BLACK);



    wattron(win, COLOR_PAIR(5));
    mvwprintw(win, 2, 2, "1: Attack");
    wattroff(win, COLOR_PAIR(5));


    wattron(win, COLOR_PAIR(6));
    mvwprintw(win, 2, 13, "2: PKMN");
    wattroff(win, COLOR_PAIR(6));


    wattron(win, COLOR_PAIR(7));
    mvwprintw(win, 4, 2, "3: Bag");
    wattroff(win, COLOR_PAIR(7));


    wattron(win, COLOR_PAIR(8));
    mvwprintw(win, 4, 13, "4: Run");
    wattroff(win, COLOR_PAIR(8));



}


void make_move(int pp, int cp, moves* move, vector<saved_poke*>& saved_poke_list)
{
    
    saved_poke* p1_poke = saved_poke_list.at(pp);
    saved_poke* p2_poke = saved_poke_list.at(cp);


    int hit = (rand() % 100 ) <= move->accuracy ? 1 : 0;

    if(hit)
    {
        double crit = (rand() % 256) < (p1_poke->speed/2) ? 1.5 : 1;
        double stab;
        for(long unsigned int i = 0; i < p1_poke->type_id.size(); i++)
        {
            if(p1_poke->type_id.at(i) == move->type_id)
            {
                stab = 1.5;
            }
            else if(stab != 1.5)
            {
                stab = 1;
            }
        }
        int damage;
        if(move->power == INT_MAX)
        {
            damage = 1;
        }
        else
        {
            damage = 2*p1_poke->level;
            damage = (damage/5)+2;
            damage = damage * move->power;
            damage = damage * (p1_poke->attack/p2_poke->defense);
            damage = damage/50 + 2;
            damage = damage * crit * (((rand() % 15) + 85)/100.00) * stab * 1; 
        }

        p2_poke->curr_hp = p2_poke->curr_hp - damage;

        p2_poke->curr_hp = p2_poke->curr_hp < 0 ? 0 : p2_poke->curr_hp;

    }



}


void attack(int pp, int cp, int chosen_move, vector<saved_poke*>& saved_poke_list)
{

    saved_poke* player_poke = saved_poke_list.at(pp);
    saved_poke* trainer_poke = saved_poke_list.at(cp);

    
    moves* player_move = player_poke->move_list.at(chosen_move);
    moves* trainer_move = trainer_poke->move_list.at(rand() % trainer_poke->
            move_list.size());


    int pfirst;

    if(player_move->priority < trainer_move->priority)
    {
        pfirst = 0;
    }
    else if(player_move->priority > trainer_move->priority)
    {
        pfirst = 1;
    }
    else if(player_poke->curr_speed <= trainer_poke->curr_speed)
    {
           pfirst = 0; 
    }
    else
    {
        pfirst = 1;
    }

    if(pfirst)
    {
        make_move(pp, cp, player_move, saved_poke_list);
        if (trainer_poke->curr_hp == 0)
        {
            return;
        }
        make_move(cp, pp, trainer_move, saved_poke_list);
    }
    else
    {
        make_move(cp, pp, trainer_move, saved_poke_list);
        if (player_poke->curr_hp == 0)
        {
            return;
        }
        make_move(pp, cp, player_move, saved_poke_list);
    }


}


int pokemon_menu(WINDOW* win, vector<saved_poke*>& saved_poke_list,
        npc* p)
{
    werase(win);
    box(win, '|', '-');
    mvwprintw(win, 1, 2, "Choose a pokemon");
    int num_valid_options = 0;
    for(int i = 0; i < 6; i++)
    {
        if(p->team[i] != -1)
        {
            saved_poke* sp = saved_poke_list.at(p->team[i]);
            mvwprintw(win, 2+i, 2, "%d: %s", 
                    i+1, sp->poke->identifier.c_str());
            mvwprintw(win, 2+i, 25, "HP %d/%d", sp->curr_hp, sp->hp); 
            mvwprintw(win, 2+i, 40, "LVL %d", sp->level);
            num_valid_options++;
        }
    }
    wrefresh(win);

    int choice = wgetch(win);
    if(choice - '0' <= num_valid_options && choice - '0' > 0)
    {
        return (choice - '0' - 1);
    }
    return -1;

}


void battle(npc* p, npc* n, int character_map[X_MAG][Y_MAG],
        vector<saved_poke*>& saved_poke_list,
        std::vector<moves*>& moves_vec, std::vector<pokemon_moves*>& pokemon_moves_vec,
        std::vector<pokemon*>& pokemon_vec, std::vector<pokemon_stats*>& pokemon_stats_vec,
        vector<int>& levels, std::vector<pokemon_types*>& pokemon_types_vec)
{

    WINDOW * main = newwin(23,80,0,0);
    box(main, '|', '-');
    WINDOW * player = subwin(main,6,25,7,6); 
    box(player,'|','-');
    WINDOW * opponent = subwin(main,6,25,2,50); 
    box(opponent, '|', '-');
    WINDOW * menu = subwin(main,9,56,13,1);
    box(menu, '|', '-');
    WINDOW * options = subwin(main,9,22,13,57);
    box(options, '|', '-');

    
    int valid_player_poke = -1;
    int i = 0;

    while(valid_player_poke == -1)
    {
        if(saved_poke_list.at(p->team[i])->curr_hp > 0)
        {
            valid_player_poke = i;    
        }
        i++;
    }

    print_pokemon_card(player, saved_poke_list,
        moves_vec,pokemon_moves_vec,
        pokemon_vec,pokemon_stats_vec,
        p->team[valid_player_poke]);

    
    
    for(long unsigned int i = 0; i < levels.size(); i++)
    {
        n->team[i] = gen_pokemon(saved_poke_list, moves_vec, pokemon_moves_vec, pokemon_vec,
            pokemon_stats_vec, levels.at(i), pokemon_types_vec);
    }

    print_pokemon_card(opponent, saved_poke_list,
        moves_vec,pokemon_moves_vec,
        pokemon_vec,pokemon_stats_vec,
        n->team[0]);

    mvwprintw(menu, 1, 2, "%s", "You have been challenged to a battle!");
    

    print_options(options);


    int current_player_poke = p->team[valid_player_poke];
    int current_opponent_poke = n->team[0];




    int in_menu = 1;
    long unsigned int pokemon_choice = '0';
    while(in_menu)
    {
        wclear(menu);
        box(menu, '|', '-');
        mvwprintw(menu, 1, 2, "You have been challenged to a battle!");
        mvwprintw(menu, 2, 2, "What will you do?");
        wrefresh(menu);

        print_pokemon_card(player, saved_poke_list,
        moves_vec,pokemon_moves_vec,
        pokemon_vec,pokemon_stats_vec,
        current_player_poke);

        print_pokemon_card(opponent, saved_poke_list,
        moves_vec,pokemon_moves_vec,
        pokemon_vec,pokemon_stats_vec,
        current_opponent_poke);


        wrefresh(options);



        pokemon_choice = wgetch(main);

        if(pokemon_choice == '1')
        {
            print_moves(menu, saved_poke_list, current_player_poke);
            saved_poke* cp = saved_poke_list.at(current_player_poke);
            saved_poke* cnp = saved_poke_list.at(current_opponent_poke);
            int num_moves = cp->move_list.size();
            pokemon_choice = wgetch(main);

            if(pokemon_choice == '1')
            {
                //player selected move 1
                attack(current_player_poke,
                        current_opponent_poke, 0,
                        saved_poke_list);
            }
            else if(pokemon_choice == '2' && 
                    num_moves >= 2)
            {
                //player selected move 2
            attack(current_player_poke,
                        current_opponent_poke, 1,
                        saved_poke_list);
            }
            else if(pokemon_choice == '3' &&
                    num_moves >= 3)
            {
                //player selected move 3

                attack(current_player_poke,
                        current_opponent_poke, 2,
                        saved_poke_list);

            }
            else if(pokemon_choice == '4' &&
                    num_moves == 4)
            {
                //player selected move 4
                attack(current_player_poke,
                        current_opponent_poke, 3,
                        saved_poke_list);               

            }

            print_pokemon_card(player, saved_poke_list,
                    moves_vec,pokemon_moves_vec,
                    pokemon_vec,pokemon_stats_vec,
                    current_player_poke);

            print_pokemon_card(opponent, saved_poke_list,
                    moves_vec,pokemon_moves_vec,
                    pokemon_vec,pokemon_stats_vec,
                    current_opponent_poke);


            if(cp->curr_hp == 0)
            {
                //check if there are other pokemon options
                //
                //
                //trigger change pokemon menu
                int valid_option = 0;
                for(int i = 0; i < 6; i++)
                {
                    if(p->team[i] != -1)
                    {
                        saved_poke* po = saved_poke_list.at(p->team[i]);

                        if(po->curr_hp != 0)
                        {
                           valid_option = 1; 
                        }
                    }
                }
                if(valid_option)
                {
                    int picked = 1;
                    while(picked)
                    {
                        int val = pokemon_menu(menu, saved_poke_list, p); 
                        if(val != -1)
                        {
                            saved_poke* po = saved_poke_list.at(p->team[val]);
                            if(po->curr_hp > 0)
                            {
                                current_player_poke = p->team[val];
                                picked = 0;
                            }
                            else
                            {
                                werase(menu);
                                box(menu, '|', '-');
                                mvwprintw(menu, 1, 2, "That pokemon is fainted");
                                wrefresh(menu);
                                sleep(2);
                                flushinp();
                            }

                        }
                    }
                }
                else
                {
                    WINDOW * game_over = newwin(0,0,0,0);
                    werase(main);
                    mvwprintw(game_over, 10, 25, "As your last pokemon faints");
                    mvwprintw(game_over, 11, 25, "You feel yourself black out");
                    wrefresh(game_over);
                    sleep(3);
                    delwin(game_over);
                    delwin(main);
                    endwin();
                    exit(1);
                }


            }
            else if(cnp->curr_hp == 0)
            {
                for(int i = 0; i < 6; i++)
                {
                    if(n->team[i] != -1)
                    {
                        saved_poke* po = saved_poke_list.at(n->team[i]);
                        if(po->curr_hp != 0)
                        {
                            current_opponent_poke = n->team[i];
                        }
                    }
                    else
                    {
                        in_menu = 0;
                        i = 6;
                        werase(menu);
                        box(menu, '|', '-');
                        mvwprintw(menu, 1, 2, "YOU WIN!!!");
                        wrefresh(menu);
                        sleep(2);
                        flushinp();
                    }
                }
            }
        }
        else if(pokemon_choice == '2')
        {
            int val = pokemon_menu(menu, saved_poke_list, p); 
            if(val != -1)
            {
                current_player_poke = p->team[val];
            }
            else if(val == -1)
            {
                werase(menu);
                box(menu, '|', '-');
                mvwprintw(menu, 1, 2, "That is not a valid option");
                wrefresh(menu);
                sleep(2);
                flushinp();
            }
            else if(saved_poke_list.at(p->team[val])->curr_hp <= 0)
            {
                werase(menu);
                box(menu, '|', '-');
                mvwprintw(menu, 1, 2, "That pokemon has fainted");
                wrefresh(menu);
                sleep(2);
                flushinp();
            }
            
        }
        else if(pokemon_choice == '3')
        {
            werase(menu);
            box(menu, '|', '-');
            mvwprintw(menu, 1, 2, "Choose an item");

            mvwprintw(menu, 2, 2, "1: %s - %d", 
                    "Pokeball" , p->bag[0]);
            mvwprintw(menu, 3, 2, "2: %s - %d", 
                    "Potion" , p->bag[1]);
            mvwprintw(menu, 4, 2, "3: %s - %d", 
                    "Revive" , p->bag[2]);

            wrefresh(menu);

            int choice = wgetch(main);
            choice = choice - '0' - 1;
            if(choice == 0)
            {
                werase(menu);
                box(menu, '|', '-');
                mvwprintw(menu, 1, 2, "You cannot catch another trainer's pokemon");
                wrefresh(menu);
                sleep(2);
                flushinp();
            }
            else if(choice == 1)
            {

                int val = pokemon_menu(menu, saved_poke_list, p); 
                if(val == -1)
                {
                    werase(menu);
                    box(menu, '|', '-');
                    mvwprintw(menu, 1, 2, "That is not a valid choice");
                    wrefresh(menu);
                    sleep(2);
                    flushinp();
                }
                else if(p->bag[1] == 0)
                {
                    werase(menu);
                    box(menu, '|', '-');
                    mvwprintw(menu, 1, 2, "You don't have any more of these");
                    wrefresh(menu);
                    sleep(2);
                    flushinp();
                }
                else
                {
                    p->bag[1] -= 1;
                    saved_poke* pc = saved_poke_list.at(p->team[val]);
                    if(pc->curr_hp + 20 >= pc->hp)
                    {
                        pc->curr_hp = pc->hp;
                    }
                    else
                    {
                        pc->curr_hp += 20;
                    }
                }
            }
            else if(choice == 2)
            {
                int val = pokemon_menu(menu, saved_poke_list, p); 
                if(val == -1)
                {
                    werase(menu);
                    box(menu, '|', '-');
                    mvwprintw(menu, 1, 2, "That is not a valid choice");
                    wrefresh(menu);
                    sleep(2);
                    flushinp();
                }
                else if(p->bag[1] == 0)
                {
                    werase(menu);
                    box(menu, '|', '-');
                    mvwprintw(menu, 1, 2, "You don't have any more of these");
                    wrefresh(menu);
                    sleep(2);
                    flushinp();
                }
                else
                {
                    saved_poke* pc = saved_poke_list.at(p->team[val]);
                    if(pc->curr_hp == 0)
                    {
                        p->bag[2] -= 1;
                        pc->curr_hp = pc->hp/2;
                    }
                    else
                    {
                        werase(menu);
                        box(menu, '|', '-');
                        mvwprintw(menu, 1, 2, "You cannot revive a non-fainted pokemon");
                        wrefresh(menu);
                        sleep(2);
                        flushinp();
                    }
                }
            }
        }
        else if(pokemon_choice == '4')
        {
            werase(menu);
            box(menu, '|', '-');
            mvwprintw(menu, 1, 2,"You can't run from a trainer battle"); 
            wrefresh(menu);
            sleep(2);
            flushinp();
        }

    }
    n->is_defeated = 1;
    character_map[n->x][n->y] = -1;
    delwin(main);

}


void pokemon_encounter(npc* p, vector<saved_poke*>& saved_poke_list,
        std::vector<moves*>& moves_vec, std::vector<pokemon_moves*>& pokemon_moves_vec,
        std::vector<pokemon*>& pokemon_vec, std::vector<pokemon_stats*>& pokemon_stats_vec,
        int level, std::vector<pokemon_types*>& pokemon_types_vec)  
{
    int cur_pokemon = gen_pokemon(saved_poke_list, moves_vec, pokemon_moves_vec, pokemon_vec,
            pokemon_stats_vec, level, pokemon_types_vec);

    WINDOW * main = newwin(23,80,0,0);
    box(main, '|', '-');
    WINDOW * player = subwin(main,6,25,7,6); 
    box(player,'|','-');
    WINDOW * opponent = subwin(main,6,25,2,50); 
    box(opponent, '|', '-');
    WINDOW * menu = subwin(main,9,56,13,1);
    box(menu, '|', '-');
    WINDOW * options = subwin(main,9,22,13,57);
    box(options, '|', '-');

    
    int valid_player_poke = -1;
    int i = 0;

    
    while(valid_player_poke == -1)
    {
        if(saved_poke_list.at(p->team[i])->curr_hp > 0)
        {
            valid_player_poke = i;    
        }
        i++;
    }


    print_pokemon_card(player, saved_poke_list,
        moves_vec,pokemon_moves_vec,
        pokemon_vec,pokemon_stats_vec,
        p->team[valid_player_poke]);


    print_pokemon_card(opponent, saved_poke_list,
        moves_vec,pokemon_moves_vec,
        pokemon_vec,pokemon_stats_vec,
        cur_pokemon);


    
    print_options(options);


    int current_player_poke = p->team[valid_player_poke];
    int current_opponent_poke = cur_pokemon;




    int in_menu = 1;
    long unsigned int pokemon_choice = '0';
    while(in_menu)
    {
        wclear(menu);
        box(menu, '|', '-');
        mvwprintw(menu, 1, 2, "You have found a wild pokemon!");
        mvwprintw(menu, 2, 2, "What will you do?");
        wrefresh(menu);

        print_pokemon_card(player, saved_poke_list,
        moves_vec,pokemon_moves_vec,
        pokemon_vec,pokemon_stats_vec,
        current_player_poke);

        print_pokemon_card(opponent, saved_poke_list,
        moves_vec,pokemon_moves_vec,
        pokemon_vec,pokemon_stats_vec,
        current_opponent_poke);


        wrefresh(options);

        int num_escape_attemps = 0;



        pokemon_choice = wgetch(main);

        if(pokemon_choice == '1')
        {
            print_moves(menu, saved_poke_list, current_player_poke);
            saved_poke* cp = saved_poke_list.at(current_player_poke);
            saved_poke* cnp = saved_poke_list.at(current_opponent_poke);
            int num_moves = cp->move_list.size();
            pokemon_choice = wgetch(main);

            if(pokemon_choice == '1')
            {
                //player selected move 1
                attack(current_player_poke,
                        current_opponent_poke, 0,
                        saved_poke_list);
            }
            else if(pokemon_choice == '2' && 
                    num_moves >= 2)
            {
                //player selected move 2
            attack(current_player_poke,
                        current_opponent_poke, 1,
                        saved_poke_list);
            }
            else if(pokemon_choice == '3' &&
                    num_moves >= 3)
            {
                //player selected move 3

                attack(current_player_poke,
                        current_opponent_poke, 2,
                        saved_poke_list);

            }
            else if(pokemon_choice == '4' &&
                    num_moves == 4)
            {
                //player selected move 4
                attack(current_player_poke,
                        current_opponent_poke, 3,
                        saved_poke_list);               

            }
            print_pokemon_card(player, saved_poke_list,
                    moves_vec,pokemon_moves_vec,
                    pokemon_vec,pokemon_stats_vec,
                    current_player_poke);

            print_pokemon_card(opponent, saved_poke_list,
                    moves_vec,pokemon_moves_vec,
                    pokemon_vec,pokemon_stats_vec,
                    current_opponent_poke);


            if(cp->curr_hp == 0)
            {
                //check if there are other pokemon options
                //
                //
                //trigger change pokemon menu
                int valid_option = 0;
                for(int i = 0; i < 6; i++)
                {
                    if(p->team[i] != -1)
                    {
                        saved_poke* po = saved_poke_list.at(p->team[i]);

                        if(po->curr_hp != 0)
                        {
                           valid_option = 1; 
                        }
                    }
                }
                if(valid_option)
                {
                    int picked = 1;
                    while(picked);
                    int val = pokemon_menu(menu, saved_poke_list, p); 
                    if(val != -1)
                    {
                        saved_poke* po = saved_poke_list.at(p->team[val]);
                        if(po->curr_hp != 0)
                        {
                            current_player_poke = p->team[val];
                            picked = 0;
                        }
                        else
                        {
                            werase(menu);
                            box(menu, '|', '-');
                            mvwprintw(menu, 1, 2, "That pokemon is fainted");
                            wrefresh(menu);
                            sleep(2);
                            flushinp();
                        }

                    }
                }
                else
                {
                    WINDOW * game_over = newwin(0,0,0,0);
                    werase(main);
                    mvwprintw(game_over, 10, 25, "As your last pokemon faints");
                    mvwprintw(game_over, 11, 25, "You feel yourself black out");
                    wrefresh(game_over);
                    sleep(3);
                    delwin(game_over);
                    delwin(main);
                    endwin();
                    exit(1);
                }
            }
            else if(cnp->curr_hp == 0)
            {
                    in_menu = 0;
                    werase(menu);
                    box(menu, '|', '-');
                    mvwprintw(menu, 1, 2, "YOU WIN!!!");
                    wrefresh(menu);
                    sleep(2);
                    flushinp();
            }
        }
        else if(pokemon_choice == '2')
        {

            //pokemon change
            int val = pokemon_menu(menu, saved_poke_list, p); 
            if(val != -1)
            {
                current_player_poke = p->team[val];
            }
            else if(val == -1)
            {
                werase(menu);
                box(menu, '|', '-');
                mvwprintw(menu, 1, 2, "That is not a valid option");
                wrefresh(menu);
                sleep(2);
                flushinp();
            }
            else if(saved_poke_list.at(p->team[val])->curr_hp <= 0)
            {
                werase(menu);
                box(menu, '|', '-');
                mvwprintw(menu, 1, 2, "That pokemon has fainted");
                wrefresh(menu);
                sleep(2);
                flushinp();
            }
        }
        else if(pokemon_choice == '3')
        {
            werase(menu);
            box(menu, '|', '-');
            mvwprintw(menu, 1, 2, "choose an item");

            mvwprintw(menu, 2, 2, "1: %s - %d", 
                    "pokeball" , p->bag[0]);
            mvwprintw(menu, 3, 2, "2: %s - %d", 
                    "potion" , p->bag[1]);
            mvwprintw(menu, 4, 2, "3: %s - %d", 
                    "revive" , p->bag[2]);

            wrefresh(menu);

            int choice = wgetch(main);
            choice = choice - '0' - 1;
            if(choice == 0)
            {
                int empty_slot = -1;
                for(int i = 0; i < 6; i++)
                {

                   if(p->team[i] == -1)
                   {
                      empty_slot = i; 
                      i = 6;
                   }

                }
                if(empty_slot != -1)
                {
                    p->team[empty_slot] = cur_pokemon; 
                    p->bag[0] -= 1;
                    in_menu = 0;
                    werase(menu);
                    box(menu, '|', '-');
                    mvwprintw(menu, 1, 2, "you caught a new pokemon!");
                    wrefresh(menu);
                    sleep(2);
                    flushinp();
                }
                else
                {
                    in_menu = 0;
                    p->bag[0] -= 1;
                    werase(menu);
                    box(menu, '|', '-');
                    mvwprintw(menu, 1, 2, "aargh it got away!");
                    wrefresh(menu);
                    sleep(2);
                    flushinp();
                }
                
            }
            else if(choice == 1)
            {

                int val = pokemon_menu(menu, saved_poke_list, p); 
                if(val == -1)
                {
                    werase(menu);
                    box(menu, '|', '-');
                    mvwprintw(menu, 1, 2, "that is not a valid choice");
                    wrefresh(menu);
                    sleep(2);
                    flushinp();
                }
                else if(p->bag[1] == 0)
                {
                    werase(menu);
                    box(menu, '|', '-');
                    mvwprintw(menu, 1, 2, "you don't have any more of these");
                    wrefresh(menu);
                    sleep(2);
                    flushinp();
                }
                else
                {
                    p->bag[1] -= 1;
                    saved_poke* pc = saved_poke_list.at(p->team[val]);
                    if(pc->curr_hp + 20 >= pc->hp)
                    {
                        pc->curr_hp = pc->hp;
                    }
                    else
                    {
                        pc->curr_hp += 20;
                    }
                }
            }
            else if(choice == 2)
            {
                int val = pokemon_menu(menu, saved_poke_list, p); 
                if(val == -1)
                {
                    werase(menu);
                    box(menu, '|', '-');
                    mvwprintw(menu, 1, 2, "that is not a valid choice");
                    wrefresh(menu);
                    sleep(2);
                    flushinp();
                }
                else if(p->bag[1] == 0)
                {
                    werase(menu);
                    box(menu, '|', '-');
                    mvwprintw(menu, 1, 2, "you don't have any more of these");
                    wrefresh(menu);
                    sleep(2);
                    flushinp();
                }
                else
                {
                    saved_poke* pc = saved_poke_list.at(p->team[val]);
                    if(pc->curr_hp == 0)
                    {
                        p->bag[2] -= 1;
                        pc->curr_hp = pc->hp/2;
                    }
                    else
                    {
                        werase(menu);
                        box(menu, '|', '-');
                        mvwprintw(menu, 1, 2, "you cannot revive a non-fainted pokemon");
                        wrefresh(menu);
                        sleep(2);
                        flushinp();
                    }
                }
            }

        }
        else if(pokemon_choice == '4')
        {
            int escape = rand() % 10;

            if(escape + num_escape_attemps >= 5)
            {
                in_menu = 0;
                werase(menu);
                box(menu, '|', '-');
                mvwprintw(menu, 1, 2,"You ran away"); 
                wrefresh(menu);
                sleep(2);
                flushinp();
            }
            else
            {
                werase(menu);
                box(menu, '|', '-');
                mvwprintw(menu, 1, 2,"You couldn't get away"); 
                wrefresh(menu);
                sleep(2);
                flushinp();
            }
        }

    }
    delwin(main);


}

void fly(int pair[2])
{
    char x[] = "-123";
    char y[] = "-123";
    echo();
    WINDOW * menu = newwin(10,52,5,15);
    wprintw(menu, "Where to?\n\n");
    wprintw(menu, "X-Value: ");
    wgetstr(menu, x);
    werase(menu);
    wrefresh(menu);
    wprintw(menu, "Where to?\n\n");
    wprintw(menu,"Y-Value: ");
    wgetstr(menu, y);
    wrefresh(menu);
    int x_int;
    int y_int;
    noecho();
    werase(menu);
    x_int = std::atoi(x);
    y_int = std::atoi(y);
    mvwprintw(menu,0,0,"%d, %d",x_int,y_int);
    wrefresh(menu);
    pair[0] = x_int;
    pair[1] = y_int;
    delwin(menu);
    
}



void show_trainers(npc* p, heapNode_t** npc_arr, int n)
{
    
    WINDOW * trainer_pad = newpad(6*n,52);
    keypad(trainer_pad,TRUE);
    scrollok(trainer_pad,TRUE); 
    idlok(trainer_pad,TRUE);
    npc* trainer;
    string x_dir;
    string y_dir;
    int x_dist;
    int y_dist;
    string status;
    int mv = 0;

    for(int i = 1; i <= n; i++)
    {
        trainer = npc_arr[i]->h_npc; 
        mvwprintw(trainer_pad,mv,0, "Type of trainer: %c", trainer->type);
        if((p->x - trainer->x) < 0) 
        {
            x_dir = "East";
            x_dist = trainer->x - p->x;
        } 
        else
        {
            x_dir = "West";
            x_dist = p->x - trainer->x;
        }

        if((p->y - trainer->y) < 0)
        {
            y_dir = "South";
            y_dist = trainer->y - p->y;
        }
        else
        {
            y_dir = "North";
            y_dist = p->y - trainer->y;
        }
        const char* x_dir_c = x_dir.c_str();
        const char* y_dir_c = y_dir.c_str();

        mv++;
        mvwprintw(trainer_pad,mv,0,"%s", "Distance from player:");
        mv++;
        mvwprintw(trainer_pad,mv,0,"%s : %d", x_dir_c, x_dist);
        mv++;
        mvwprintw(trainer_pad,mv,0,"%s : %d", y_dir_c, y_dist);
        mv++;
        if(trainer->is_defeated)
        {status = "Defeated";}
        else
        {status = "Ready for battle";}
        const char* status_c = status.c_str();
        mvwprintw(trainer_pad,mv,0,"Status : %s", status_c);
        mv+=2;

    }

    prefresh(trainer_pad,0,0,5,15,15,70);
    int pad_location = 0;
    int viewing = 1;
    int input; 
    while(viewing)
    {
       input = wgetch(trainer_pad);
       if(input == 27)
       {
         viewing = 0;
       }
       else if(input == KEY_UP && pad_location >= 0)
       {
           pad_location--;
           prefresh(trainer_pad, pad_location,0,5,15,15,70); 
       }
       else if(input == KEY_DOWN && pad_location <=50)
       {
           pad_location++;
           prefresh(trainer_pad, pad_location,0,5,15,15,70); 
       }

    }
    delwin(trainer_pad);



}

void compare(int x, int y, int min_pair[2], int* min, int dij[X_MAG][Y_MAG])
{
    if(dij[x][y] < *min)
    {
        *min = dij[x][y];
         min_pair[0]=x;
        min_pair[1]=y;
  }
     
   
}

char random_turn(char except)
{
    if(except == 'N')
    {
        switch ((rand() % 3) + 1)
        {
            case 1: 
                return 'W';
                break;

            case 2: 
                return 'S';
                break;

            case 3:
                return 'E';
                break;

            default: 
                return 'X';
                break;
        }
    }
    else if(except == 'S')
    {
        switch ((rand() % 3) + 1)
        {
            case 1: 
                return 'N';
                break;

            case 2: 
                return 'W';
                break;

            case 3:
                return 'E';
                break;

            default: 
                return 'X';
                break;
        }
        return 'f';
    }
    else if(except == 'E')
    {
        switch ((rand() % 3) + 1)
        {
            case 1: 
                return 'N';
                break;

            case 2: 
                return 'S';
                break;

            case 3:
                return 'W';
                break;

            default: 
                return 'X';
                break;
        }

    }
    else
    {
        switch ((rand() % 3) + 1)
        {
            case 1: 
                return 'N';
                break;

            case 2: 
                return 'S';
                break;

            case 3:
                return 'W';
                break;

            default: 
                return 'X';
                break;
        }

    }
}

//CHILLIN
int move_npc(npc* c, char map[X_MAG][Y_MAG], int cost_map[X_MAG][Y_MAG],
        int character_map[X_MAG][Y_MAG], int new_x, int new_y)
{
    if(character_map[new_x][new_y] == -1 && 
            cost_map[new_x][new_y] != INT16_MAX)
    {
        //setting values back to before character was there 
        character_map[c->x][c->y] = -1;
        map[c->x][c->y] = c->terrain;
       
        //setting new coords
        c->x = new_x;
        c->y = new_y;

        //occupy space
        c->terrain = map[c->x][c->y];
        map[c->x][c->y] = c->type;
        c->cost+=cost_map[c->x][c->y];
        character_map[c->x][c->y] = c->index;

        
    }
    else
    {  
        if(character_map[new_x][new_y] == 0 && c->type != '@')
        {
        return character_map[new_x][new_y];
        }
        else if(character_map[new_x][new_y] != -1 && c->type == '@')
        {
        return character_map[new_x][new_y];
        }
        else
        {
        c->cost+=5;
        }
    }
    return -1;
}




int explore(npc* p, char map[X_MAG][Y_MAG], int cost_map[X_MAG][Y_MAG],
        int character_map[X_MAG][Y_MAG])
{
    int collision = -1;
    //game is printed upsidown so values are adjusted accordingly
    if(p->cur_dir == 'N')
    {
        if(p->y > 0 && cost_map[p->x][p->y-1] != INT16_MAX)
        {
            collision = move_npc(p, map, cost_map, character_map, p->x, p->y-1);
        }
        else
        {
            collision = move_npc(p, map, cost_map, character_map, p->x, p->y+1);
            p->cur_dir = random_turn('N');
        }
    }
    else if(p->cur_dir == 'S')
    {
        if(p->y < 20 && cost_map[p->x][p->y+1] != INT16_MAX)
        {
            collision = move_npc(p, map, cost_map, character_map, p->x, p->y+1);
        }
        else
        {
            collision = move_npc(p, map, cost_map, character_map, p->x, p->y-1);
            p->cur_dir = random_turn('S');
        }
    }
    else if(p->cur_dir == 'E')
    {
        if(p->x < 79 && cost_map[p->x+1][p->y] != INT16_MAX)
        {
            collision = move_npc(p, map, cost_map, character_map, p->x+1, p->y);
        }
        else
        {
            collision = move_npc(p, map, cost_map, character_map, p->x-1, p->y);
            p->cur_dir = random_turn('E');
        }
    }
    else if(p->cur_dir == 'W')
    {
        if(p->x > 0 && cost_map[p->x-1][p->y] != INT16_MAX)
        {
            collision = move_npc(p, map, cost_map, character_map, p->x-1, p->y);
        }
        else
        {
            collision = move_npc(p, map, cost_map, character_map, p->x+1, p->y);
            p->cur_dir = random_turn('W');
        }
    }
    return collision;
}


int wander(npc* p, char map[X_MAG][Y_MAG], int cost_map[X_MAG][Y_MAG],
        int character_map[X_MAG][Y_MAG])
{
    int collision = -1;
    //game is printed upsidown so values are adjusted accordingly
    if(p->cur_dir == 'N')
    {
        if(p->y > 0 && map[p->x][p->y-1] == p->terrain)
        {
            collision = move_npc(p, map, cost_map, character_map, p->x, p->y-1);
        }
        else
        {
            collision = move_npc(p, map, cost_map, character_map, p->x, p->y+1);
            p->cur_dir = random_turn('N');
        }
    }
    else if(p->cur_dir == 'S')
    {
        if(p->y < 20 && map[p->x][p->y+1] == p->terrain)
        {
            collision = move_npc(p, map, cost_map, character_map, p->x, p->y+1);
        }
        else
        {
            collision = move_npc(p, map, cost_map, character_map, p->x, p->y-1);
            p->cur_dir = random_turn('S');
        }
    }
    else if(p->cur_dir == 'E')
    {
        if(p->x < 79 && map[p->x+1][p->y] == p->terrain)
        {
            collision = move_npc(p, map, cost_map, character_map, p->x+1, p->y);
        }
        else
        {
            collision = move_npc(p, map, cost_map, character_map, p->x-1, p->y);
            p->cur_dir = random_turn('E');
        }
    }
    else if(p->cur_dir == 'W')
    {
        if(p->x > 0 && map[p->x-1][p->y] == p->terrain)
        {
            collision = move_npc(p, map, cost_map, character_map, p->x-1, p->y);
        }
        else
        {
            collision = move_npc(p, map, cost_map, character_map, p->x+1, p->y);
            p->cur_dir = random_turn('W');
        }
    }
    return collision;
}


int pace(npc* p, char map[X_MAG][Y_MAG], int cost_map[X_MAG][Y_MAG],
        int character_map[X_MAG][Y_MAG])
{
    int collision = -1;
    //game is printed upsidown so values are adjusted accordingly
    if(p->cur_dir == 'N')
    {
        if(p->y > 0 && cost_map[p->x][p->y-1] != INT16_MAX)
        {
            collision = move_npc(p, map, cost_map, character_map, p->x, p->y-1);
        }
        else
        {
            collision = move_npc(p, map, cost_map, character_map, p->x, p->y+1);
            p->cur_dir = 'S';
        }
    }
    else if(p->cur_dir == 'S')
    {
        if(p->y < 20 && cost_map[p->x][p->y+1] != INT16_MAX)
        {
            collision = move_npc(p, map, cost_map, character_map, p->x, p->y+1);
        }
        else
        {
            collision = move_npc(p, map, cost_map, character_map, p->x, p->y-1);
            p->cur_dir = 'N';
        }
    }
    else if(p->cur_dir == 'E')
    {
        if(p->x < 79 && cost_map[p->x+1][p->y] != INT16_MAX)
        {
            collision = move_npc(p, map, cost_map, character_map, p->x+1, p->y);
        }
        else
        {
            collision = move_npc(p, map, cost_map, character_map, p->x-1, p->y);
            p->cur_dir = 'W';
        }
    }
    else if(p->cur_dir == 'W')
    {
        if(p->x > 0 && cost_map[p->x-1][p->y] != INT16_MAX)
        {
            collision = move_npc(p, map, cost_map, character_map, p->x-1, p->y);
        }
        else
        {
            collision = move_npc(p, map, cost_map, character_map, p->x+1, p->y);
            p->cur_dir = 'E';
        }
    }
    return collision;

}

int chase(npc* c,char map[X_MAG][Y_MAG], int cost_map[X_MAG][Y_MAG],
        int character_map[X_MAG][Y_MAG], int dijkstra[X_MAG][Y_MAG])
{
    int min_pair[2] = {0,0};
    int min = INT16_MAX-1;
    int collision = -1;

    
    if(c->x < 78)
    {
        compare(c->x+1, c->y, min_pair, &min, dijkstra);
    }
    if(c->y < 19)
    {
        compare(c->x, c->y+1, min_pair, &min, dijkstra);
    }

    if(c->x > 1)
    {
        compare(c->x-1, c->y, min_pair, &min, dijkstra);
    }

    if(c->y > 1)
    {
        compare(c->x, c->y-1, min_pair, &min, dijkstra);
    }

    if(c->x < 78 && c->y < 19)
    {
        compare(c->x+1, c->y+1, min_pair, &min, dijkstra);
    }

    if(c->x > 1 && c->y > 1)
    {
        compare(c->x-1, c->y-1, min_pair, &min, dijkstra);
    }

    if(c->x > 1 && c->y < 19)
    {
        compare(c->x-1, c->y+1, min_pair, &min, dijkstra);
    }

    if(c->x < 79 && c->y > 1)
    {
        compare(c->x+1, c->y-1, min_pair, &min, dijkstra);
    }
    collision = move_npc(c, map, cost_map, character_map, min_pair[0], min_pair[1]);

    
    return collision;
}

heap_t* init_turn_heap(int capacity)
{
    return createHeap_t(capacity);
}

void add_npc(heap_t* h, heapNode_t* ht)
{
        insert_t(h, ht); 

}

heapNode_t* create_npc(int index, int x, int y, char type, int cost_map[X_MAG][Y_MAG],
        int char_map[X_MAG][Y_MAG], char map[X_MAG][Y_MAG])
{
    npc* npc = (class npc*)malloc(sizeof(*npc));
    
    //initialize our basic values
    npc->x = x;
    npc->y = y;
    npc->is_defeated = 0;
    npc->type = type;
    if(type != '@')
    {npc->cost = cost_map[x][y];}
    else
    {npc->cost = 15;}
    npc->terrain = map[x][y];
    npc->index = index;

    if(type == '@')
    {
        for(int i = 0; i < 6; i++)
        {
            npc->team[i] = player_team[i];
        }
        for(int i = 0; i < 3; i++)
        {
            npc->bag[i] = player_bag[i];
        }
    }
    else
    {
        for(int i = 0; i < 6; i++)
        {
            npc->team[i] = -1;
        }
        for(int i = 0; i < 3; i++)
        {
            npc->bag[i] = 10;
        }
    }
    //gen our random direction (only matters for npcs we care about)

    switch ((rand() % 4) + 1)
    {
        case 1: 
            npc->cur_dir = 'W';
            break;

        case 2: 
            npc->cur_dir = 'S';
            break;

        case 3:
            npc->cur_dir = 'E';
            break;

        case 4: 
            npc->cur_dir = 'N'; 
            break;
    }    
    char_map[x][y] = index;

    heapNode_t* ht;
    ht = (heapNode_t*)malloc(sizeof(heapNode_t*));
    ht->h_npc = npc;

    return ht;
}

void init_new_square(board *bd,int hiker_cost_map[X_MAG][Y_MAG], 
        int hiker_dij_map[X_MAG][Y_MAG],
        int rival_cost_map[X_MAG][Y_MAG],
        int rival_dij_map[X_MAG][Y_MAG],
        int pc_cost_map[X_MAG][Y_MAG],
        heapNode_t** npc_arr_board[BOARD_X][BOARD_Y],
        heap_t* queue_array[BOARD_X][BOARD_Y],
        int npc_count)
{

    initCostMap(bd->board[bd->curX][bd->curY], 
            hiker_cost_map, 
            rival_cost_map,
            pc_cost_map);
    dijkstra(bd->board[bd->curX][bd->curY], hiker_cost_map, rival_cost_map,
            rival_dij_map, hiker_dij_map);

    queue_array[bd->curX][bd->curY] = init_turn_heap(npc_count+1);

    
    npc_arr_board[bd->curX][bd->curY] = (heapNode_t**)malloc((npc_count+1) * sizeof(heapNode_t*));
    
    


    heapNode_t* playerNode = create_npc(0,bd->board[bd->curX][bd->curY]->px,
            bd->board[bd->curX][bd->curY]->py, '@', pc_cost_map, bd->board[bd->curX][bd->curY]->char_map,
            bd->board[bd->curX][bd->curY]->map);

    bd->board[bd->curX][bd->curY]->
        map[bd->board[bd->curX][bd->curY]->px][bd->board[bd->curX][bd->curY]->py] = '@';

    npc_arr_board[bd->curX][bd->curY][0] = playerNode;



    for(int i = 1; i <= npc_count; i++)
    {
        bool valid = 0;
        char type; 

        if(i % 2 == 0 || i % 2 == 1)
        {
            type = 'h';
        }
        if(i % 3 == 0)
        {
            if((rand() % 2) + 1 == 1)
            {
                type = 'e';
            }
            else
            {
                type = 'p';
            }
        }
        if(i % 4 == 0)
        {
            type = 'r';
        }
        if(i % 5 == 0)
        {
            if((rand() % 2) + 1 == 1)
            {
                type = 'w';
            }
            else
            {
                type = 's';
            }
        }
        int x;
        int y;
        while(!valid)
        {
            x = (rand() % (75)) + 2;
            y = (rand() % (16)) + 2;


            if(type == 'h')
            {
                if(hiker_cost_map[x][y] != INT16_MAX && bd->board[bd->curX][bd->curY]->char_map[x][y] == -1)
                {
                    valid = 1;
                }
            }
            else
            {
                if(rival_cost_map[x][y] != INT16_MAX && bd->board[bd->curX][bd->curY]->char_map[x][y] == -1)
                {
                    valid = 1;
                }
            }
        }
        heapNode_t* npc;
        if(type == 'h')
        {
            npc = create_npc(i,x,y,type,hiker_cost_map,
                    bd->board[bd->curX][bd->curY]->char_map,bd->board[bd->curX][bd->curY]->map);
        }
        else
        {
            npc = create_npc(i,x,y,type,rival_cost_map,
                    bd->board[bd->curX][bd->curY]->char_map,bd->board[bd->curX][bd->curY]->map);

        }
        bd->board[bd->curX][bd->curY]->map[x][y] = type;
        if(type != 's')
        {
            add_npc(queue_array[bd->curX][bd->curY], npc); 
        }
        npc_arr_board[bd->curX][bd->curY][i] = npc;

    }


}
int next_player_turn(heapNode_t* hn, int c, char map[X_MAG][Y_MAG], 
        int cost_map[X_MAG][Y_MAG],
        int character_map[X_MAG][Y_MAG],
        square* sq,
        heapNode_t** npc_arr,
        int n,
        std::vector<saved_poke*>& poke_list,
        std::vector<moves*>& moves_vec, std::vector<pokemon_moves*>& pokemon_moves_vec,
        std::vector<pokemon*>& pokemon_vec, std::vector<pokemon_stats*>& pokemon_stats_vec,
        board* bd, std::vector<pokemon_types*>& pokemon_types_vec)
{

        int level;
        vector<int> levels;
        int manhat = abs(bd->curX - 200) + abs(bd->curY - 200);
        int min;
        int max;

        if(manhat <= 200)
        {
            min = 1;
            max = manhat / 2;
        }
        else
        {
            max = 100;
            min = (manhat - 200)/2;
             
        }
        
        int no_fail = 1;
        int num_trainer_pokemon = 1;
        while(num_trainer_pokemon < 6 && no_fail) 
        {
        rand() % 101 <= 60 ? num_trainer_pokemon++ : no_fail = 0;
        }

        for(int i = 0; i < num_trainer_pokemon; i++)
        {
            level = max == 0 ? min : rand() % max;
            level = level <= min ? min : level;
            levels.push_back(level);
        }
        


        int error_caught = 0;
        int collision;
        int menu_open = 0;
        int winchar;
        //move to the lower left
        if(c == '1' || c == 'b')
        {
            if (cost_map[sq->px-1][sq->py+1] != INT16_MAX)
            {
                sq->px -= 1;
                sq->py += 1;
                if ((rand() % 101) <= 10 && sq->map[sq->px][sq->py] == ':')
                {

                    pokemon_encounter(hn->h_npc, poke_list, moves_vec, pokemon_moves_vec,
                            pokemon_vec, pokemon_stats_vec, level, pokemon_types_vec);
                }
            }
            else
            {
                error_caught = 1;
                if (sq->map[sq->px-1][sq->py+1] == '~')
                {
                    return 1;
                }
                else
                {
                    return 2;
                }
            }
        }
        //move down
        else if(c == '2' || c == 'j')
        {
            if (cost_map[sq->px][sq->py+1] != INT16_MAX)
            {
                sq->py += 1;
                if ((rand() % 101) <= 10 && sq->map[sq->px][sq->py] == ':')
                {
                pokemon_encounter(hn->h_npc, poke_list, moves_vec, pokemon_moves_vec,
                            pokemon_vec, pokemon_stats_vec, level, pokemon_types_vec);
                }
            }
            else if(sq->px == sq->s && sq->py == 19)
            {
                return 'S';
            }
            else
            {
                error_caught = 1;
                if (sq->map[sq->px][sq->py+1] == '~')
                {
                    return 1;
                }
                else
                {
                    return 2;
                }
            }
        }
        //move to lower right
        else if(c == '3' || c == 'n')
        {
            if (cost_map[sq->px+1][sq->py+1] != INT16_MAX)
            {
                sq->px += 1;
                sq->py += 1;
                if ((rand() % 101) <= 10 && sq->map[sq->px][sq->py] == ':')
                {
                pokemon_encounter(hn->h_npc, poke_list, moves_vec, pokemon_moves_vec,
                            pokemon_vec, pokemon_stats_vec, level, pokemon_types_vec);
                }
            }
            else
            {
                error_caught = 1;
                if (sq->map[sq->px+1][sq->py+1] == '~')
                {
                    return 1;
                }
                else
                {
                    return 2;
                }
            }
        }
        //move one cell to left
        else if(c == '4' || c == 'h')
        {
            if (cost_map[sq->px-1][sq->py] != INT16_MAX)
            {
                sq->px -= 1;
                if ((rand() % 101) <= 10 && sq->map[sq->px][sq->py] == ':')
                {
                pokemon_encounter(hn->h_npc, poke_list, moves_vec, pokemon_moves_vec,
                            pokemon_vec, pokemon_stats_vec, level, pokemon_types_vec);
                }
            }
            else if(sq->py == sq->w && sq->px == 1)
            {
                return 'W';
            }
            else
            {
                error_caught = 1;
                if (sq->map[sq->px-1][sq->py] == '~')
                {
                    return 1;
                }
                else
                {
                    return 2;
                }
            } 
        }
        //rest
        else if(c == '5' || c == ' ' || c == '.')
        {
            hn->h_npc->cost += 10;
            if ((rand() % 101) <= 10 && sq->map[sq->px][sq->py] == ':')
                {
                pokemon_encounter(hn->h_npc, poke_list, moves_vec, pokemon_moves_vec,
                            pokemon_vec, pokemon_stats_vec, level, pokemon_types_vec);
                }
        }
        //move one cell to the right
        else if(c == '6' || c == 'l')
        {
            if (cost_map[sq->px+1][sq->py] != INT16_MAX)
            {
                sq->px += 1;
                if ((rand() % 101) <= 10 && sq->map[sq->px][sq->py] == ':')
                {
                pokemon_encounter(hn->h_npc, poke_list, moves_vec, pokemon_moves_vec,
                            pokemon_vec, pokemon_stats_vec, level, pokemon_types_vec);
                }
            }
            else if(sq->py == sq->e && sq->px == 78)
            {
                return 'E';
            }
            else
            {
                error_caught = 1;
                if (sq->map[sq->px+1][sq->py] == '~')
                {
                    return 1;
                }
                else
                {
                    return 2;
                }
            }
        }
        //move to the upper left
        else if(c == '7' || c == 'y')
        {
            if (cost_map[sq->px-1][sq->py-1] != INT16_MAX)
            {
                sq->px -= 1;
                sq->py -= 1;
                if ((rand() % 101) <= 10 && sq->map[sq->px][sq->py] == ':')
                {
                pokemon_encounter(hn->h_npc, poke_list, moves_vec, pokemon_moves_vec,
                            pokemon_vec, pokemon_stats_vec, level, pokemon_types_vec);
                }
            }
            else
            {
                error_caught = 1;
                if (sq->map[sq->px-1][sq->py-1] == '~')
                {
                    return 1;
                }
                else
                {
                    return 2;
                }
            }
        }
        //move one cell up
        else if(c == '8' || c == 'k')
        {
            if (cost_map[sq->px][sq->py-1] != INT16_MAX)
            {
                sq->py -= 1;
                if ((rand() % 101) <= 10 && sq->map[sq->px][sq->py] == ':')
                {
                pokemon_encounter(hn->h_npc, poke_list, moves_vec, pokemon_moves_vec,
                            pokemon_vec, pokemon_stats_vec, level, pokemon_types_vec);
                } 
            }
            else if(sq->px == sq->n && sq->py == 1)
            {
                return 'N';
            }
            else
            {
                error_caught = 1;
                if (sq->map[sq->px][sq->py-1] == '~')
                {
                    return 1;
                }
                else
                {
                    return 2;
                }
            }
        }
        else if(c == '9' || c == 'u')
        {
            if (cost_map[sq->px+1][sq->py-1] != INT16_MAX)
            {
                sq->py -= 1;
                sq->px += 1;
                if ((rand() % 101) <= 10 && sq->map[sq->px][sq->py] == ':')
                {
                    pokemon_encounter(hn->h_npc, poke_list, moves_vec, pokemon_moves_vec,
                            pokemon_vec, pokemon_stats_vec, level, pokemon_types_vec);
                }
            }
            else
            {
                error_caught = 1;
                if (sq->map[sq->px+1][sq->py-1] == '~')
                {
                    return 1;
                }
                else
                {
                    return 2;
                }
            }
        }
        else if(c =='F')
        {
            return c;
        }
        else if(c == '>' 
                && (hn->h_npc->terrain == 'C' || 
                hn->h_npc->terrain == 'M'))
            
        {
            menu_open = 1;
            WINDOW * menu = newwin(10,52,5,15);
            winchar = wgetch(menu);
            if(winchar == '<')
            {
            menu_open = 0;
            delwin(menu);
            }
            for(int i = 0; i < 3; i++)
            {
                hn->h_npc->bag[i] = 10;
            }
        }
        else if (c == 't')
        {
            menu_open = 1;
            show_trainers(hn->h_npc, npc_arr, n);
            menu_open = 0;
        }
        else if (c == 'B')
        {
            //open bag
            WINDOW* menu = newwin(23,80,0,0);
            int in_menu = 1;
            while(in_menu)
            {
                werase(menu);
                box(menu, '|', '-');
                mvwprintw(menu, 1, 2, "choose an item or Q to quit");

                mvwprintw(menu, 2, 2, "1: %s - %d", 
                        "pokeball" , hn->h_npc->bag[0]);
                mvwprintw(menu, 3, 2, "2: %s - %d", 
                        "potion" , hn->h_npc->bag[1]);
                mvwprintw(menu, 4, 2, "3: %s - %d", 
                        "revive" , hn->h_npc->bag[2]);

                wrefresh(menu);

                int choice = wgetch(menu);
                if(choice == 'q' || choice == 'Q')
                {
                    in_menu = 0;
                    delwin(menu);
                }
                choice = choice - '0' - 1;
                if(choice == 0)
                {
                    werase(menu);
                    box(menu, '|', '-');
                    mvwprintw(menu, 1, 2, "There's nothing to catch");
                    wrefresh(menu);
                    sleep(2);
                    flushinp();
                }
                else if(choice == 1)
                {

                    int val = pokemon_menu(menu, poke_list, hn->h_npc); 
                    if(val == -1)
                    {
                        werase(menu);
                        box(menu, '|', '-');
                        mvwprintw(menu, 1, 2, "that is not a valid choice");
                        wrefresh(menu);
                        sleep(2);
                        flushinp();
                    }
                    else if(hn->h_npc->bag[1] == 0)
                    {
                        werase(menu);
                        box(menu, '|', '-');
                        mvwprintw(menu, 1, 2, "you don't have any more of these");
                        wrefresh(menu);
                        sleep(2);
                        flushinp();
                    }
                    else
                    {
                        hn->h_npc->bag[1] -= 1;
                        saved_poke* pc = poke_list.at(hn->h_npc->team[val]);
                        if(pc->curr_hp + 20 >= pc->hp)
                        {
                            pc->curr_hp = pc->hp;
                        }
                        else
                        {
                            pc->curr_hp += 20;
                        }
                    }
                }
                else if(choice == 2)
                {
                    int val = pokemon_menu(menu, poke_list, hn->h_npc); 
                    if(val == -1)
                    {
                        werase(menu);
                        box(menu, '|', '-');
                        mvwprintw(menu, 1, 2, "that is not a valid choice");
                        wrefresh(menu);
                        sleep(2);
                        flushinp();
                    }
                    else if(hn->h_npc->bag[1] == 0)
                    {
                        werase(menu);
                        box(menu, '|', '-');
                        mvwprintw(menu, 1, 2, "you don't have any more of these");
                        wrefresh(menu);
                        sleep(2);
                        flushinp();
                    }
                    else
                    {
                        saved_poke* pc = poke_list.at(hn->h_npc->team[val]);
                        if(pc->curr_hp == 0)
                        {
                            hn->h_npc->bag[2] -= 1;
                            pc->curr_hp = pc->hp/2;
                        }
                        else
                        {
                            werase(menu);
                            box(menu, '|', '-');
                            mvwprintw(menu, 1, 2, "you cannot revive a non-fainted pokemon");
                            wrefresh(menu);
                            sleep(2);
                            flushinp();
                        }
                    }
                }
            }


        }
        else if(c == 'Q')
        {
            endwin();
            exit(0);
        }
        else
        {
            
            collision = move_npc(hn->h_npc, map, cost_map, character_map, sq->px, sq->py); 
            if(collision != -1 && collision != 0)
            {
                battle(hn->h_npc,npc_arr[collision]->h_npc,character_map,
                        poke_list, moves_vec, pokemon_moves_vec, pokemon_vec,
            pokemon_stats_vec, levels, pokemon_types_vec);

            }
            return 0; 
        }



        if(!error_caught && !menu_open)
        {
            collision = move_npc(hn->h_npc, map, cost_map, character_map, sq->px, sq->py); 
            if (collision != -1 && collision != 0) 
            {
                battle(hn->h_npc,npc_arr[collision]->h_npc,character_map,
                        poke_list, moves_vec, pokemon_moves_vec, pokemon_vec,
                        pokemon_stats_vec, levels, pokemon_types_vec);}
            return -1;
        }
        return -1;

}

// THE QUEUE THAT IS PASSED THROUGH THE ARRAY IS THE QUEUE
// FOR THE LAST SQUARE
// THEREFORE IF YOU CHANGE SQUARES, THE QUEUE YOU ADD YOURSELF TO
// IS FOR THE WRONG SQUARE

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
        std::vector<saved_poke*>& poke_list,
        std::vector<moves*>& moves_vec, std::vector<pokemon_moves*>& pokemon_moves_vec,
        std::vector<pokemon*>& pokemon_vec, std::vector<pokemon_stats*>& pokemon_stats_vec,
        std::vector<pokemon_types*>& pokemon_types_vec)
{
    heapNode_t* hn = extractMin_t(queue_array[bd->curX][bd->curY]); 
    int response = -1; 

    int level;
        vector<int> levels;
        int manhat = abs(bd->curX - 200) + abs(bd->curY - 200);
        int min;
        int max;

        if(manhat <= 200)
        {
            min = 1;
            max = manhat / 2;
        }
        else
        {
            max = 100;
            min = (manhat - 200)/2;
             
        }
        
        int no_fail = 1;
        int num_trainer_pokemon = 1;
        while(num_trainer_pokemon <= 6 && no_fail) 
        {
        rand() % 101 <= 60 ? num_trainer_pokemon++ : no_fail = 0;
        }

        for(int i = 0; i < num_trainer_pokemon; i++)
        {
            level = max == 0 ? min : rand() % max;
            level = level <= min ? min : level;
            levels.push_back(level);
        }


    if(!hn->h_npc->is_defeated)
    {
        int c;
        int collision;
        switch(hn->h_npc->type)
        {
            case 'h':
                add_npc(queue_array[bd->curX][bd->curY], hn);
                collision = chase(hn->h_npc, map, hiker_cost_map, bd->board[bd->curX][bd->curY]->char_map, hiker_dij);
                if(collision == 0)
                {
                    battle(npc_arr_board[bd->curX][bd->curY][collision]->h_npc,hn->h_npc,
                            bd->board[bd->curX][bd->curY]->char_map,
                        poke_list, moves_vec, pokemon_moves_vec, pokemon_vec,
                        pokemon_stats_vec, levels, pokemon_types_vec);
                }
                break;
            case 'w':
                add_npc(queue_array[bd->curX][bd->curY], hn);
                collision = wander(hn->h_npc, map, rival_cost_map, bd->board[bd->curX][bd->curY]->char_map);
                if(collision == 0)
                {
                battle(npc_arr_board[bd->curX][bd->curY][collision]->h_npc,hn->h_npc,
                            bd->board[bd->curX][bd->curY]->char_map,
                        poke_list, moves_vec, pokemon_moves_vec, pokemon_vec,
                        pokemon_stats_vec, levels, pokemon_types_vec);
                }
                break;
            case 'p':
                add_npc(queue_array[bd->curX][bd->curY], hn);
                collision = pace(hn->h_npc, map, rival_cost_map, bd->board[bd->curX][bd->curY]->char_map);
                if(collision == 0)
                {
                    battle(npc_arr_board[bd->curX][bd->curY][collision]->h_npc,hn->h_npc,
                            bd->board[bd->curX][bd->curY]->char_map,
                        poke_list, moves_vec, pokemon_moves_vec, pokemon_vec,
                        pokemon_stats_vec, levels, pokemon_types_vec);
                }
                break;
            case 'e':
                add_npc(queue_array[bd->curX][bd->curY], hn);
                collision = explore(hn->h_npc, map, rival_cost_map, bd->board[bd->curX][bd->curY]->char_map);
                if(collision == 0)
                {
                    battle(npc_arr_board[bd->curX][bd->curY][collision]->h_npc,hn->h_npc,
                            bd->board[bd->curX][bd->curY]->char_map,
                        poke_list, moves_vec, pokemon_moves_vec, pokemon_vec,
                        pokemon_stats_vec, levels, pokemon_types_vec);
                }
                break;
            case 'r':
                add_npc(queue_array[bd->curX][bd->curY], hn);
                collision = chase(hn->h_npc, map, rival_cost_map, 
                        bd->board[bd->curX][bd->curY]->char_map, rival_dij);
                if(collision == 0)
                {
                    battle(npc_arr_board[bd->curX][bd->curY][collision]->h_npc,hn->h_npc,
                            bd->board[bd->curX][bd->curY]->char_map,
                        poke_list, moves_vec, pokemon_moves_vec, pokemon_vec,
                        pokemon_stats_vec, levels, pokemon_types_vec);
                }
                break;
            case '@':
                c = getch();
                response = next_player_turn(hn, c, map, pc_cost_map,
                        bd->board[bd->curX][bd->curY]->char_map, sq, npc_arr_board[bd->curX][bd->curY], n,
                        poke_list,
                        moves_vec, pokemon_moves_vec,
                        pokemon_vec, pokemon_stats_vec, bd, pokemon_types_vec);
                if(response == 78)
                {
                    //north
                    if(bd->curY+1 <= 400)
                    {
                        if(bd->board[bd->curX][bd->curY+1] == NULL)   
                        {
                            bd->board[bd->curX][bd->curY]->char_map[bd->board[bd->curX][bd->curY]->px][bd->board[bd->curX][bd->curY]->py] = 0;
                            checkTile(bd,bd->curX,bd->curY+1);
                            init_new_square(bd, hiker_cost_map, hiker_dij,
                                    rival_cost_map, rival_dij,
                                    pc_cost_map, npc_arr_board,
                                    queue_array, n);
                        }
                        else
                        {
                            bd->board[bd->curX][bd->curY]->char_map[bd->board[bd->curX][bd->curY]->px][bd->board[bd->curX][bd->curY]->py] = -1;
                            checkTile(bd,bd->curX,bd->curY+1);
                        }
                        bd->board[bd->curX][bd->curY]->
                            map[bd->board[bd->curX][bd->curY]->px][bd->board[bd->curX][bd->curY]->py] = '#';

                        npc_arr_board[bd->curX][bd->curY][0]->h_npc->x = bd->board[bd->curX][bd->curY]->s;
                        npc_arr_board[bd->curX][bd->curY][0]->h_npc->y = 19;

                        bd->board[bd->curX][bd->curY]
                            ->px = bd->board[bd->curX][bd->curY]->s;

                        bd->board[bd->curX][bd->curY]
                            ->py = 19;


                        bd->board[bd->curX][bd->curY] 
                            ->map[bd->board[bd->curX][bd->curY]->px][bd->board[bd->curX][bd->curY]->py] = '@';
                        bd->board[bd->curX][bd->curY]->char_map[bd->board[bd->curX][bd->curY]->px][bd->board[bd->curX][bd->curY]->py] = 0;

                        initCostMap(bd->board[bd->curX][bd->curY], 
                                hiker_cost_map, 
                                rival_cost_map,
                                pc_cost_map);
                        dijkstra(bd->board[bd->curX][bd->curY], hiker_cost_map, rival_cost_map,
                                rival_dij, hiker_dij);
                    }
                    else
                    {
                        mvprintw(0,0,"%s", "You can't move farther in that direction");
                    }
                    response =  -1;
                }
                else if(response == 87)
                {
                    //west

                    if(bd->curX-1 >= 0)
                    {
                        if(bd->board[bd->curX-1][bd->curY] == NULL)   
                        {
                            bd->board[bd->curX][bd->curY]->char_map[bd->board[bd->curX][bd->curY]->px][bd->board[bd->curX][bd->curY]->py] = -1;
                            checkTile(bd,bd->curX-1,bd->curY);
                            init_new_square(bd, hiker_cost_map, hiker_dij,
                                    rival_cost_map, rival_dij,
                                    pc_cost_map, npc_arr_board,
                                    queue_array, n);
                        }
                        else
                        {
                            bd->board[bd->curX][bd->curY]->char_map[bd->board[bd->curX][bd->curY]->px][bd->board[bd->curX][bd->curY]->py] = -1;
                            checkTile(bd,bd->curX-1,bd->curY);
                        }
                        bd->board[bd->curX][bd->curY]->
                            map[bd->board[bd->curX][bd->curY]->px][bd->board[bd->curX][bd->curY]->py] = '#';

                        npc_arr_board[bd->curX][bd->curY][0]->h_npc->y = bd->board[bd->curX][bd->curY]->e;
                        npc_arr_board[bd->curX][bd->curY][0]->h_npc->x = 78;

                        bd->board[bd->curX][bd->curY]
                            ->py = bd->board[bd->curX][bd->curY]->e;

                        bd->board[bd->curX][bd->curY]
                            ->px = 78;


                        bd->board[bd->curX][bd->curY] 
                            ->map[bd->board[bd->curX][bd->curY]->px][bd->board[bd->curX][bd->curY]->py] = '@';

                        bd->board[bd->curX][bd->curY]->char_map[bd->board[bd->curX][bd->curY]->px][bd->board[bd->curX][bd->curY]->py] = 0;

                        initCostMap(bd->board[bd->curX][bd->curY], 
                                hiker_cost_map, 
                                rival_cost_map,
                                pc_cost_map);
                        dijkstra(bd->board[bd->curX][bd->curY], hiker_cost_map, rival_cost_map,
                                rival_dij, hiker_dij);
                    }
                    else
                    {
                        mvprintw(0,0,"%s", "You can't move farther in that direction");
                    }
                    response =  -1;
                }
                else if(response == 69)
                {
                    //east
                    if(bd->curX+1 <= 400)
                    {

                        if(bd->board[bd->curX+1][bd->curY] == NULL)
                        {
                            bd->board[bd->curX][bd->curY]->char_map[bd->board[bd->curX][bd->curY]->px][bd->board[bd->curX][bd->curY]->py] = -1;
                            checkTile(bd,bd->curX+1,bd->curY);
                            init_new_square(bd, hiker_cost_map, hiker_dij,
                                    rival_cost_map, rival_dij,
                                    pc_cost_map, npc_arr_board,
                                    queue_array, n);
                        }
                        else
                        {

                            bd->board[bd->curX][bd->curY]->char_map[bd->board[bd->curX][bd->curY]->px][bd->board[bd->curX][bd->curY]->py] = -1;
                            checkTile(bd,bd->curX+1,bd->curY);
                        }
                        bd->board[bd->curX][bd->curY]->
                            map[bd->board[bd->curX][bd->curY]->px][bd->board[bd->curX][bd->curY]->py] = '#';

                        npc_arr_board[bd->curX][bd->curY][0]->h_npc->y = bd->board[bd->curX][bd->curY]->w;
                        npc_arr_board[bd->curX][bd->curY][0]->h_npc->x = 1;

                        bd->board[bd->curX][bd->curY]
                            ->py = bd->board[bd->curX][bd->curY]->w;

                        bd->board[bd->curX][bd->curY]
                            ->px = 1;


                        bd->board[bd->curX][bd->curY] 
                            ->map[bd->board[bd->curX][bd->curY]->px][bd->board[bd->curX][bd->curY]->py] = '@';

                        bd->board[bd->curX][bd->curY]->char_map[bd->board[bd->curX][bd->curY]->px][bd->board[bd->curX][bd->curY]->py] = 0;
                        initCostMap(bd->board[bd->curX][bd->curY], 
                                hiker_cost_map, 
                                rival_cost_map,
                                pc_cost_map);
                        dijkstra(bd->board[bd->curX][bd->curY], hiker_cost_map, rival_cost_map,
                                rival_dij, hiker_dij);
                    }
                    else
                    {
                        mvprintw(0,0,"%s", "You can't move farther in that direction");
                    }
                    response =  -1;
                }
                else if(response == 83)
                {
                    //South
                    if(bd->curY-1 >= 0)
                    {
                        if(bd->board[bd->curX][bd->curY-1] == NULL)
                        {
                            bd->board[bd->curX][bd->curY]->char_map[bd->board[bd->curX][bd->curY]->px][bd->board[bd->curX][bd->curY]->py] = -1;
                            checkTile(bd,bd->curX,bd->curY-1);
                            init_new_square(bd, hiker_cost_map, hiker_dij,
                                    rival_cost_map, rival_dij,
                                    pc_cost_map, npc_arr_board,
                                    queue_array, n);
                        }
                        else
                        {
                            bd->board[bd->curX][bd->curY]->char_map[bd->board[bd->curX][bd->curY]->px][bd->board[bd->curX][bd->curY]->py] = -1;
                            checkTile(bd,bd->curX,bd->curY-1);
                        }
                        bd->board[bd->curX][bd->curY]->
                            map[bd->board[bd->curX][bd->curY]->px][bd->board[bd->curX][bd->curY]->py] = '#';

                        npc_arr_board[bd->curX][bd->curY][0]->h_npc->x = bd->board[bd->curX][bd->curY]->n;
                        npc_arr_board[bd->curX][bd->curY][0]->h_npc->y = 1;

                        bd->board[bd->curX][bd->curY]
                            ->px = bd->board[bd->curX][bd->curY]->n;

                        bd->board[bd->curX][bd->curY]
                            ->py = 1;


                        bd->board[bd->curX][bd->curY] 
                            ->map[bd->board[bd->curX][bd->curY]->px][bd->board[bd->curX][bd->curY]->py] = '@';

                        bd->board[bd->curX][bd->curY]->char_map[bd->board[bd->curX][bd->curY]->px][bd->board[bd->curX][bd->curY]->py] = 0;
                        initCostMap(bd->board[bd->curX][bd->curY], 
                                hiker_cost_map, 
                                rival_cost_map,
                                pc_cost_map);
                        dijkstra(bd->board[bd->curX][bd->curY], hiker_cost_map, rival_cost_map,
                                rival_dij, hiker_dij);

                    }
                    else
                    {
                        mvprintw(0,0,"%s", "You can't move farther in that direction");
                    }
                    response = -1;
                }
                else if(response == 'F')
                {
                    int pair[] = {0,0};
                    fly(pair); 

                    if(!(pair[0]+200 >= 0 && pair[1]+200 >= 0  && pair[0]+200 <= 400 && pair[1]+200 <= 400))
                    {
                        return 0;
                    }

                    if(bd->board[pair[0]+200][pair[1]+200] == NULL)
                    {
                        bd->board[bd->curX][bd->curY]->char_map[bd->board[bd->curX][bd->curY]->px][bd->board[bd->curX][bd->curY]->py] = -1;
                        checkTile(bd,pair[0]+200,pair[1]+200);
                        init_new_square(bd, hiker_cost_map, hiker_dij,
                                rival_cost_map, rival_dij,
                                pc_cost_map, npc_arr_board,
                                queue_array, n);
                    }
                    else
                    {
                        bd->board[bd->curX][bd->curY]->char_map[bd->board[bd->curX][bd->curY]->px][bd->board[bd->curX][bd->curY]->py] = -1;
                        checkTile(bd,pair[0]+200,pair[1]+200);
                    }
                    bd->board[bd->curX][bd->curY]->
                        map[bd->board[bd->curX][bd->curY]->px][bd->board[bd->curX][bd->curY]->py] = '#';

                    npc_arr_board[bd->curX][bd->curY][0]->h_npc->x = bd->board[bd->curX][bd->curY]->n;
                    npc_arr_board[bd->curX][bd->curY][0]->h_npc->y = 1;

                    bd->board[bd->curX][bd->curY]
                        ->px = bd->board[bd->curX][bd->curY]->n;

                    bd->board[bd->curX][bd->curY]
                        ->py = 1;


                    bd->board[bd->curX][bd->curY] 
                        ->map[bd->board[bd->curX][bd->curY]->px][bd->board[bd->curX][bd->curY]->py] = '@';

                    bd->board[bd->curX][bd->curY]->char_map[bd->board[bd->curX][bd->curY]->px][bd->board[bd->curX][bd->curY]->py] = 0;
                    initCostMap(bd->board[bd->curX][bd->curY], 
                            hiker_cost_map, 
                            rival_cost_map,
                            pc_cost_map);
                    dijkstra(bd->board[bd->curX][bd->curY], hiker_cost_map, rival_cost_map,
                            rival_dij, hiker_dij);



                    response =  -1;

                }
                else
                {
                    return response;
                }
                response = -1;
                break;
        }
    }
    return response;
}

 
