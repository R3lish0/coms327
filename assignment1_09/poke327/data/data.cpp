//this is the impletation of data manipulation
#include <iostream>
#include <fstream>
#include <limits.h>
#include <any>
#include "../data/data.h"


using namespace std;


int check_file(const std::string& name){
    ifstream file(name);
   
    if(!file.is_open()){
        
        return 0;
    }
    file.close();
    return 1;
}




int get_pokemon_data(const std::string& name, std::vector<pokemon*>& poke)
{
    ifstream file(name.c_str());
    if(!file.is_open())
    {
        cerr << "file could not be opened" << endl;
        exit(0);
    }
    string line;
    int is_first = 1;
    while(getline(file,line)) 
    {
        if(is_first)
        {
            is_first = 0;
            continue;
        }
        vector<string> cells; 
        pokemon* tempemon = new pokemon();
        for(int i = 0; i < 7; i++)
        {
            string token = line.substr(0,line.find(","));
            line = line.substr(token.length()+1,line.length());
            cells.push_back(token); 
        }
        cells.push_back(line);
        tempemon->id = cells.at(0) != "" ? stoi(cells.at(0)): INT_MAX;
        tempemon->identifier = cells.at(1) != "" ? cells.at(1) : "";
        tempemon->species_id = cells.at(2) != "" ? stoi(cells.at(2)): INT_MAX;
        tempemon->height = cells.at(3) != "" ? stoi(cells.at(3)): INT_MAX;
        tempemon->weight = cells.at(4) != "" ? stoi(cells.at(4)): INT_MAX;
        tempemon->base_xp = cells.at(5) != "" ? stoi(cells.at(5)): INT_MAX;
        tempemon->order = cells.at(6) != "" ? stoi(cells.at(6)): INT_MAX;
        tempemon->is_default = cells.at(7) != "" ? stoi(cells.at(7)): INT_MAX;

        poke.push_back(tempemon);
    }
    file.close();
    return 0;
}

void print_pokemon_data(std::vector<pokemon*>& poke)
{
    long unsigned int i;
    pokemon* p;
    for(i = 0; i < poke.size(); i++)
    {
        p = poke.at(i);
        cout << to_string(p->id)+ ",";
        cout << p->identifier + ",";
        cout << to_string(p->species_id)+ ",";
        cout << to_string(p->height)+ ",";
        cout << to_string(p->weight)+ ",";
        cout << to_string(p->base_xp)+ ",";
        cout << to_string(p->order) + ",";
        cout << poke.at(i)->is_default << endl;
    }
}



int get_pokemon_moves_data(const std::string& name, 
        std::vector<pokemon_moves*>& pokemon_moves_vec)
{
    ifstream file(name.c_str());
    if(!file.is_open())
    {
        cerr << "file could not be opened" << endl;
        exit(0);
    }
    string line;
    int is_first = 1;
    while(getline(file,line)) {
        if(is_first)
        {
            is_first = 0;
            continue;
        }
        vector<string> cells; 
        pokemon_moves* tempemon = new pokemon_moves();
        for(int i = 0; i < 5; i++)
        {
            string token = line.substr(0,line.find(","));
            line = line.substr(token.length()+1,line.length());
            cells.push_back(token); 
        }
        cells.push_back(line);
        tempemon->pokemon_id = cells.at(0) != "" ? stoi(cells.at(0)) : INT_MAX;
        tempemon->version_group_id = cells.at(1) != "" ? stoi(cells.at(1)) : INT_MAX;
        tempemon->move_id = cells.at(2) != "" ? stoi(cells.at(2)) : INT_MAX;
        tempemon->pokemon_move_method_id = cells.at(3) != "" ? stoi(cells.at(3)) : INT_MAX;
        tempemon->level = cells.at(4) != "" ? stoi(cells.at(4)) : INT_MAX;
        tempemon->order = cells.at(5) != "" ? stoi(cells.at(5)) : INT_MAX;


        pokemon_moves_vec.push_back(tempemon);
    }
    file.close();
    return 0;
}


void print_pokemon_moves_data(std::vector<pokemon_moves*>& poke)
{
    pokemon_moves* p;
    long unsigned int i;
    for(i = 0; i < poke.size(); i++)
    {
        p = poke.at(i);
        p->pokemon_id == INT_MAX ? 
           cout << "" << ",": cout << p->pokemon_id << ",";
        p->version_group_id == INT_MAX ? 
           cout << "" << ",": cout << p->version_group_id << ",";
        p->move_id == INT_MAX ?
           cout << "" << ",": cout << p->move_id << ",";
        p->pokemon_move_method_id == INT_MAX ?
           cout << "" << ",": cout << p->pokemon_move_method_id << ",";
        p->level == INT_MAX ?
           cout << "" << ",": cout << p->level << ",";
        p->order == INT_MAX ?
            cout << "" << endl: cout << p->order << endl;

    }
}


int get_moves_data(const std::string& name, 
        std::vector<moves*>& moves_vec)
{
    ifstream file(name.c_str());
    if(!file.is_open())
    {
        cerr << "file could not be opened" << endl;
        exit(0);
    }
    string line;
    int is_first = 1;
    while(getline(file,line)) {
        if(is_first)
        {
            is_first = 0;
            continue;
        }
        vector<string> cells; 
        moves* tempemon = new moves();
        for(int i = 0; i < 14; i++)
        {
            string token = line.substr(0,line.find(","));
            line = line.substr(token.length()+1,line.length());
            cells.push_back(token); 
        }
        cells.push_back(line);
        tempemon->id = cells.at(0) != "" ? stoi(cells.at(0)) : INT_MAX;
        tempemon->identifier = cells.at(1) != "" ? cells.at(1) : to_string(INT_MAX);
        tempemon->generation_id = cells.at(2) != "" ? stoi(cells.at(2)) : INT_MAX;
        tempemon->type_id = cells.at(3) != "" ? stoi(cells.at(3)) : INT_MAX;
        tempemon->power = cells.at(4) != "" ? stoi(cells.at(4)) : INT_MAX;
        tempemon->pp = cells.at(5) != "" ? stoi(cells.at(5)) : INT_MAX;
        tempemon->accuracy = cells.at(6) != "" ? stoi(cells.at(6)) : INT_MAX;
        tempemon->priority = cells.at(7) != "" ? stoi(cells.at(7)) : INT_MAX;
        tempemon->target_id = cells.at(8) != "" ? stoi(cells.at(8)) : INT_MAX;
        tempemon->damage_class_id = cells.at(9) != "" ? stoi(cells.at(9)) : INT_MAX;
        tempemon->effect_id = cells.at(10) != "" ? stoi(cells.at(10)) : INT_MAX;
        tempemon->effect_chance = cells.at(11) != "" ? stoi(cells.at(11)) : INT_MAX;
        tempemon->contest_type_id = cells.at(12) != "" ? stoi(cells.at(12)) : INT_MAX;
        tempemon->contest_effect_id = cells.at(13) != "" ? stoi(cells.at(13)) : INT_MAX;
        tempemon->super_contest_effect_id = cells.at(14) != "" ? stoi(cells.at(14)) : INT_MAX;
        moves_vec.push_back(tempemon);
    }
    file.close();
    return 0;
}


void print_moves_data(std::vector<moves*>& poke)
{
    moves* p;
    long unsigned int i;
    for(i = 0; i < poke.size(); i++)
    {
        p = poke.at(i);
        p->id == INT_MAX ?
            cout << ""<< ",": cout << p->id << ",";
        p->identifier == to_string(INT_MAX) ?
            cout << ""<< ",": cout << p->identifier << ",";
        p->generation_id == INT_MAX ?
            cout << ""<< ",": cout << p->generation_id << ",";
        p->type_id == INT_MAX ?
            cout << ""<< ",": cout << p->type_id << ",";
        p->power == INT_MAX ?
            cout << ""<< ",": cout << p->power << ",";
        p->pp == INT_MAX ?
            cout << ""<< ",": cout << p->pp << ",";
        p->accuracy == INT_MAX ?
            cout << ""<< ",": cout << p->accuracy << ",";
        p->priority == INT_MAX ?
            cout << ""<< ",": cout << p->priority << ",";
        p->target_id == INT_MAX ?
            cout << ""<< ",": cout << p->target_id << ",";
        p->damage_class_id == INT_MAX ?
            cout << ""<< ",": cout << p->damage_class_id << ",";
        p->effect_id == INT_MAX ?
            cout << ""<< ",": cout << p->effect_id << ",";
        p->effect_chance == INT_MAX ?
            cout << ""<< ",": cout << p->effect_chance << ",";
        p->contest_type_id == INT_MAX ?
            cout << ""<< ",": cout << p->contest_type_id << ",";
        p->contest_effect_id == INT_MAX ?
            cout << ""<< ",": cout << p->contest_effect_id << ",";
        p->super_contest_effect_id == INT_MAX ?
            cout << "" << endl: cout << p->super_contest_effect_id << endl;
    }
}



int get_pokemon_species_data(const std::string& name, std::vector<pokemon_species*>& species_vec)
{
    ifstream file(name.c_str());
    if(!file.is_open())
    {
        cerr << "file could not be opened" << endl;
        exit(0);
    }
    string line;
    int is_first = 1;
    while(getline(file,line)) {
        if(is_first)
        {
            is_first = 0;
            continue;
        }
        vector<string> cells; 
        pokemon_species* tempemon = new pokemon_species();
        for(int i = 0; i < 19; i++)
        {
            string token = line.substr(0,line.find(","));
            line = line.substr(token.length()+1,line.length());
            cells.push_back(token); 
        }
        cells.push_back(line);
        tempemon->id = cells.at(0) != "" ? stoi(cells.at(0)) : INT_MAX;
        tempemon->identifier = cells.at(1) != "" ? cells.at(1): to_string(INT_MAX);
        tempemon->generation_id = cells.at(2) != "" ? stoi(cells.at(2)): INT_MAX;
        tempemon->evolves_from_species_id = cells.at(3) != "" ? stoi(cells.at(3)): INT_MAX;
        tempemon->evolution_chain_id = cells.at(4) != "" ? stoi(cells.at(4)): INT_MAX;
        tempemon->color_id = cells.at(5) != "" ? stoi(cells.at(5)): INT_MAX;
        tempemon->shape_id = cells.at(6) != "" ? stoi(cells.at(6)): INT_MAX;
        tempemon->habitat_id = cells.at(7) != "" ? stoi(cells.at(7)): INT_MAX;
        tempemon->gender_rate = cells.at(8) != "" ? stoi(cells.at(8)): INT_MAX;
        tempemon->capture_rate = cells.at(9) != "" ? stoi(cells.at(9)): INT_MAX;
        tempemon->base_happiness = cells.at(10) != "" ? stoi(cells.at(10)): INT_MAX;
        tempemon->is_baby = cells.at(11) != "" ? stoi(cells.at(11)): INT_MAX;
        tempemon->hatch_counter = cells.at(12) != "" ? stoi(cells.at(12)): INT_MAX;
        tempemon->has_gender_differences = cells.at(13) != "" ? stoi(cells.at(13)): INT_MAX;
        tempemon->growth_rate_id = cells.at(14) != "" ? stoi(cells.at(14)): INT_MAX;
        tempemon->forms_switchable = cells.at(15) != "" ? stoi(cells.at(15)): INT_MAX;
        tempemon->is_legendary = cells.at(16) != "" ? stoi(cells.at(16)): INT_MAX;
        tempemon->is_mythical = cells.at(17) != "" ? stoi(cells.at(17)): INT_MAX;
        tempemon->order = cells.at(18) != "" ? stoi(cells.at(18)): INT_MAX;
        tempemon->conquest_order = cells.at(19) != "" ? stoi(cells.at(19)): INT_MAX;
        species_vec.push_back(tempemon);
    }
    file.close();
    return 0;
}

void print_pokemon_species_data(std::vector<pokemon_species*>& poke)
{
    pokemon_species* p;
    long unsigned int i;
    for(i = 0; i < poke.size(); i++)
    {
        p = poke.at(i);
        p->id == INT_MAX ? 
            cout << "" << ",": cout << p->id << ",";
        p->identifier == to_string(INT_MAX) ? 
            cout << "" << ",": cout << p->identifier << ",";
        p->generation_id == INT_MAX ? 
            cout << "" << ",": cout << p->generation_id << ",";
        p->evolves_from_species_id == INT_MAX ? 
            cout << "" << ",": cout << p->evolves_from_species_id << ",";
        p->evolution_chain_id == INT_MAX ? 
            cout << "" << ",": cout << p->evolution_chain_id << ",";
        p->color_id == INT_MAX ? 
            cout << "" << ",": cout << p->color_id << ",";
        p->shape_id == INT_MAX ? 
            cout << "" << ",": cout << p->shape_id << ",";
        p->habitat_id == INT_MAX ? 
            cout << "" << ",": cout << p->habitat_id << ",";
        p->gender_rate == INT_MAX ? 
            cout << "" << ",": cout << p->gender_rate << ",";
        p->capture_rate == INT_MAX ? 
            cout << "" << ",": cout << p->capture_rate << ",";
        p->base_happiness == INT_MAX ? 
            cout << "" << ",": cout << p->base_happiness << ",";
        p->is_baby == INT_MAX ? 
            cout << "" << ",": cout << p->is_baby << ",";
        p->hatch_counter == INT_MAX ? 
            cout << "" << ",": cout << p->hatch_counter << ",";
         p->has_gender_differences == INT_MAX ? 
            cout << "" << ",": cout << p->has_gender_differences << ",";
         p->growth_rate_id == INT_MAX ? 
            cout << "" << "," : cout << p->growth_rate_id << ",";
         p->forms_switchable == INT_MAX ? 
            cout << "" << ",": cout << p->forms_switchable << ",";
         p->is_legendary == INT_MAX ? 
            cout << "" << ",": cout << p->is_legendary << ",";
         p->is_mythical == INT_MAX ? 
            cout << "" << "," : cout << p->is_mythical << ",";
         p->order == INT_MAX ? 
            cout << "" << "," : cout << p->order << "," ;
          p->conquest_order == INT_MAX ? 
            cout << "" << endl: cout << p->conquest_order << endl;
      }
}


int get_exp_data(const std::string& name, std::vector<experience*>& poke)
{
ifstream file(name.c_str());
    if(!file.is_open())
    {
        cerr << "file could not be opened" << endl;
        exit(0);
    }
    string line;
    int is_first = 1;
    while(getline(file,line)) {
        if(is_first)
        {
            is_first = 0;
            continue;
        }
        vector<string> cells; 
        experience* tempemon = new experience();
        for(int i = 0; i < 2; i++)
        {
            string token = line.substr(0,line.find(","));
            line = line.substr(token.length()+1,line.length());
            cells.push_back(token); 
        }
        cells.push_back(line);
        tempemon->growth_rate_id = cells.at(0) != "" ? stoi(cells.at(0)) : INT_MAX;
        tempemon->level = cells.at(1) != "" ? stoi(cells.at(1)): INT_MAX;
        tempemon->experience = cells.at(2) != "" ? stoi(cells.at(2)): INT_MAX;
        poke.push_back(tempemon);
        
    }
    file.close();
    return 0;
}

void print_exp_data(std::vector<experience*>& poke)
{
    experience* p;
    long unsigned int i;
    for(i = 0; i < poke.size(); i++)
    {
        p = poke.at(i);
        p->growth_rate_id == INT_MAX ? 
            cout << "" << ",": cout << p->growth_rate_id << ",";
        p->level == INT_MAX ? 
            cout << "" << ",": cout << p->level << ",";
        p->experience == INT_MAX ? 
            cout << "" << endl: cout << p->experience << endl;
    }
}

int get_type_name_data(const std::string& name, std::vector<type_names*>& poke)
{
ifstream file(name.c_str());
    if(!file.is_open())
    {
        cerr << "file could not be opened" << endl;
        exit(0);
    }
    string line;
    int is_first = 1;
    while(getline(file,line)) {
        if(is_first)
        {
            is_first = 0;
            continue;
        }
        vector<string> cells; 
        type_names* tempemon = new type_names();
        for(int i = 0; i < 2; i++)
        {
            string token = line.substr(0,line.find(","));
            line = line.substr(token.length()+1,line.length());
            cells.push_back(token); 
        }
        cells.push_back(line);
        tempemon->type_id = cells.at(0) != "" ? stoi(cells.at(0)) : INT_MAX;
        tempemon->local_language_id = cells.at(1) != "" ? stoi(cells.at(1)): INT_MAX;
        tempemon->name = cells.at(2) != "" ? (cells.at(2)): to_string(INT_MAX);
        poke.push_back(tempemon);
        
    }
    file.close();
    return 0;
}

void print_type_name_data(std::vector<type_names*>& poke)
{
    type_names* p;
    long unsigned int i;
    for(i = 0; i < poke.size(); i++)
    {
        p = poke.at(i);
        p->type_id == INT_MAX ? 
            cout << "" << ",": cout << p->type_id << ",";
        p->local_language_id == INT_MAX ? 
            cout << "" << ",": cout << p->local_language_id << ",";
        p->name == to_string(INT_MAX) ? 
            cout << "" << endl: cout << p->name << endl;
    }
}



int get_pokemon_stats_data(const std::string& name, 
        std::vector<pokemon_stats*>& pokemon_stats_vec)
{
    ifstream file(name.c_str());
    if(!file.is_open())
    {
        cerr << "file could not be opened" << endl;
        exit(0);
    }
    string line;
    int is_first = 1;
    while(getline(file,line)) {
        if(is_first)
        {
            is_first = 0;
            continue;
        }
        vector<string> cells; 
        pokemon_stats* tempemon = new pokemon_stats();
        for(int i = 0; i < 3; i++)
        {
            string token = line.substr(0,line.find(","));
            line = line.substr(token.length()+1,line.length());
            cells.push_back(token);
        }
        cells.push_back(line);
        tempemon->pokemon_id = cells.at(0) != "" ? stoi(cells.at(0)) : INT_MAX;
        tempemon->stat_id = cells.at(1) != "" ? stoi(cells.at(1)): INT_MAX;
        tempemon->base_stat = cells.at(2) != "" ? stoi(cells.at(2)): INT_MAX;
        tempemon->effort = cells.at(3) != "" ? stoi(cells.at(3)): INT_MAX;
        pokemon_stats_vec.push_back(tempemon);
        
    }
    file.close();
    return 0;
}

void print_pokemon_stats_data(std::vector<pokemon_stats*>& poke)
{
    pokemon_stats* p;
    long unsigned int i;
    for(i = 0; i < poke.size(); i++)
    {
        p = poke.at(i);
        p->pokemon_id == INT_MAX ? 
            cout << "" << ",": cout << p->pokemon_id << ",";
        p->stat_id == INT_MAX ? 
            cout << "" << ",": cout << p->stat_id << ",";
        p->base_stat == INT_MAX ? 
            cout << "" << ",": cout << p->base_stat << ",";
        p->effort == INT_MAX ? 
            cout << "" << endl : cout << p->effort << endl;
    }
}


int get_stats_data(const std::string& name, std::vector<stats*>& stats_vec)
{
    ifstream file(name.c_str());
    if(!file.is_open())
    {
        cerr << "file could not be opened" << endl;
        exit(0);
    }
    string line;
    int is_first = 1;
    while(getline(file,line)) {
        if(is_first)
        {
            is_first = 0;
            continue;
        }
        vector<string> cells; 
        stats* tempemon = new stats();
        for(int i = 0; i < 4; i++)
        {
            string token = line.substr(0,line.find(","));
            line = line.substr(token.length()+1,line.length());
            cells.push_back(token);
        }
        cells.push_back(line);
        tempemon->id = cells.at(0) != "" ? stoi(cells.at(0)) : INT_MAX;
        tempemon->damage_class_id = cells.at(1) != "" ? stoi(cells.at(1)): INT_MAX;
        tempemon->identifier = cells.at(2) != "" ? cells.at(2): to_string(INT_MAX);
        tempemon->is_battle_only = cells.at(3) != "" ? stoi(cells.at(3)): INT_MAX;
        tempemon->game_index = cells.at(4) != "" ? stoi(cells.at(4)): INT_MAX;
        stats_vec.push_back(tempemon);
        
    }
    file.close();
    return 0;
}

void print_stats_data(std::vector<stats*>& poke)
{
    stats* p;
    long unsigned int i;
    for(i = 0; i < poke.size(); i++)
    {
        p = poke.at(i);
        p->id == INT_MAX ? 
            cout << "" << ",": cout << p->id << ",";
        p->damage_class_id == INT_MAX ? 
            cout << "" << ",": cout << p->damage_class_id << ",";
        p->identifier == to_string(INT_MAX) ? 
            cout << "" << ",": cout << p->identifier << ",";
        p->is_battle_only == INT_MAX ? 
            cout << "" << ",": cout << p->is_battle_only << "," ;
        p->game_index == INT_MAX ? 
            cout << ""<< endl : cout << p->game_index << endl;
    }
}


int get_pokemon_types_data(const std::string& name, 
        std::vector<pokemon_types*>& poke)
{
    ifstream file(name.c_str());
    if(!file.is_open())
    {
        cerr << "file could not be opened" << endl;
        exit(0);
    }
    string line;
    int is_first = 1;
    while(getline(file,line)) {
        if(is_first)
        {
            is_first = 0;
            continue;
        }
        vector<string> cells; 
        pokemon_types* tempemon = new pokemon_types();
        for(int i = 0; i < 2; i++)
        {
            string token = line.substr(0,line.find(","));
            line = line.substr(token.length()+1,line.length());
            cells.push_back(token); 
        }
        cells.push_back(line);
        tempemon->pokemon_id = cells.at(0) != "" ? stoi(cells.at(0)) : INT_MAX;
        tempemon->type_id = cells.at(1) != "" ? stoi(cells.at(1)): INT_MAX;
        tempemon->slot = cells.at(2) != "" ? stoi(cells.at(2)): INT_MAX;
        poke.push_back(tempemon);
        
    }
    file.close();
    return 0;
}

void print_pokemon_types_data(std::vector<pokemon_types*>& poke)
{
    pokemon_types* p;
    long unsigned int i;
    for(i = 0; i < poke.size(); i++)
    {
        p = poke.at(i);
        p->pokemon_id == INT_MAX ? 
            cout << "" << ",": cout << p->pokemon_id << ",";
        p->type_id == INT_MAX ? 
            cout << "" << ",": cout << p->type_id << ",";
        p->slot == INT_MAX ? 
            cout << "" << endl: cout << p->slot << endl;
    }
}


