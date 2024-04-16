#ifndef MAIN_H
#define MAIN_H


#include <vector>
#include "../data/data.h"

typedef class saved_poke {
    public:
        int index;
        pokemon* poke;
        int level;
        std::vector<moves*> move_list;
        int iv_hp;
        int iv_attack;
        int iv_defense;
        int iv_speed;
        int iv_special_attack;
        int iv_special_defense;
        int gender;
        char is_shiny; 
        int hp;
        int attack;
        int defense;
        int speed;
        int special_attack;
        int special_defense;

} saved_poke;



int gen_pokemon(std::vector<saved_poke*>& poke_list,
        std::vector<moves*>& moves_vec, std::vector<pokemon_moves*>& pokemon_moves_vec,
        std::vector<pokemon*>& pokemon_vec, std::vector<pokemon_stats*>& pokemon_stats_vec,
        int level);


#endif 
