#ifndef MAIN_H
#define MAIN_H


#include <vector>
#include "../data/data.h"

extern int player_bag[3];
extern int player_team[6];



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
        int curr_hp;
        int curr_attack;
        int curr_defense;
        int curr_speed;
        int curr_special_attack;
        int curr_special_defense;
        std::vector<int> type_id; 

} saved_poke;



int gen_pokemon(std::vector<saved_poke*>& poke_list,
        std::vector<moves*>& moves_vec, std::vector<pokemon_moves*>& pokemon_moves_vec,
        std::vector<pokemon*>& pokemon_vec, std::vector<pokemon_stats*>& pokemon_stats_vec,
        int level, std::vector<pokemon_types*>& pokemon_types_vec);


#endif 
