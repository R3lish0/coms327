//head file for data reading and populating
#ifndef DATA_H 
#define DATA_H 

#include <iostream>
#include <any>
#include <vector>


typedef class pokemon {
    public:
    int id;
    std::string identifier; 
    int species_id;
    int height;
    int weight;
    int base_xp;
    int order;
    int is_default;
} pokemon;

typedef class moves {
    public:
    int id;
    std::string identifier;
    int generation_id;
    int type_id;
    int power;
    int pp;
    int accuracy;
    int priority; 
    int target_id;
    int damage_class_id;
    int effect_id;
    int effect_chance;
    int contest_type_id;
    int contest_effect_id;
    int super_contest_effect_id;
} moves;

typedef class pokemon_moves {
    public:
    int pokemon_id;
    int version_group_id;
    int move_id;
    int pokemon_move_method_id;
    int level;
    int order;
} pokemon_moves;

typedef class pokemon_species {
    public:
    int id;
    std::string identifier;
    int generation_id;
    int evolves_from_species_id;
    int evolution_chain_id;
    int color_id;
    int shape_id;
    int habitat_id;
    int gender_rate;
    int capture_rate;
    int base_happiness;
    int is_baby;
    int hatch_counter;
    int has_gender_differences;
    int growth_rate_id;
    int forms_switchable;
    int is_legendary;
    int is_mythical;
    int order;
    int conquest_order;
} pokemon_species;

typedef class experience {
    public:
    int growth_rate_id;
    int level;
    int experience;
} experience;

typedef class type_names {
    public:
    int type_id;
    int local_language_id;
    std::string name;
} type_names;

typedef class pokemon_stats {
    public:
    int pokemon_id;
    int stat_id;
    int base_stat;
    int effort;
} pokemon_stats;

typedef class stats {
    public:
    int id;
    int damage_class_id;
    std::string identifier;
    int is_battle_only;
    int game_index;
} stats;

typedef class pokemon_types {
    public:
    int pokemon_id;
    int type_id;
    int slot;
} pokemon_types;





int check_file(const std::string& name);


int get_pokemon_data(const std::string& name, 
        std::vector<pokemon*>& pokemon);

int get_pokemon_moves_data(const std::string& name, 
        std::vector<pokemon_moves*>& pokemon_moves_vec);

int get_pokemon_stats_data(const std::string& name, 
        std::vector<pokemon_stats*>& pokemon_stats);

int get_pokemon_types_data(const std::string& name, 
        std::vector<pokemon_types*>& pokemon_types);

int get_moves_data(const std::string& name, 
        std::vector<moves*>& moves);

int get_pokemon_species_data(const std::string& name, 
        std::vector<pokemon_species*>& species_vec);

int get_type_name_data(const std::string& name, 
        std::vector<type_names*>& types_vec);


int get_types_data(const std::string& name, 
        std::vector<pokemon_types*>& pokemon_types_vec);

int get_stats_data(const std::string& name, 
        std::vector<stats*>& pokemon_stats_vec);

int get_exp_data(const std::string& name, 
        std::vector<experience*>& exp_vec);

void print_pokemon_data(std::vector<pokemon*>& poke);

void print_pokemon_moves_data(std::vector<pokemon_moves*>& poke);

void print_moves_data(std::vector<moves*>& poke);

void print_pokemon_stats_data(std::vector<pokemon_stats*>& poke);

void print_stats_data(std::vector<stats*>& poke);

void print_pokemon_species_data(std::vector<pokemon_species*>& poke);

void print_pokemon_types_data(std::vector<pokemon_types*>& poke);

void print_exp_data(std::vector<experience*>& poke);

void print_type_name_data(std::vector<type_names*>& poke);


#endif
