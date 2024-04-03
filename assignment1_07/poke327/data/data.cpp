//this is the impletation of data manipulation
#include <iostream>
#include <fstream>
#include <limits.h>
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


int get_data(const std::string& name, std::vector<std::any> vector_arr,
        int i)
{
    ifstream file(name.c_str());

    string line;

    while (getline(file,line)) {
        cout << line << endl;
    }

    file.close();

    return 0;
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
           cout << "" : cout << p->pokemon_id << ",";
        p->version_group_id == INT_MAX ? 
           cout << "" : cout << p->version_group_id << ",";
        p->move_id == INT_MAX ?
           cout << "" : cout << p->move_id << ",";
        p->pokemon_move_method_id == INT_MAX ?
           cout << "" : cout << p->pokemon_move_method_id << ",";
        p->level == INT_MAX ?
           cout << "" : cout << p->level << ",";
        p->order == INT_MAX ?
            cout << "" << endl: cout << p->order << endl;

    }
}



int get_pokemon_stats_data(const std::string& name, std::vector<pokemon_stats*> pokemon_stats_vec)
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
        for(int i = 0; i < 7; i++)
        {
            string token = line.substr(0,line.find(","));
            line = line.substr(token.length()+1,line.length());
            cells.push_back(token); 
        }
        cells.push_back(line);
        tempemon->pokemon_id = stoi(cells.at(0));
        tempemon->stat_id = stoi(cells.at(1));
        tempemon->base_stat = stoi(cells.at(2));
        tempemon->effort = stoi(cells.at(3));
    }
    file.close();
    return 0;
}
//int get_pokemon_types_data(const std::string& name, std::vector<pokemon_types*> pokemon_types)
//
//int get_move_data(const std::string& name, std::vector<moves*> moves)
//int get_species_data(const std::string& name, std::vector<pokemon_species*> species_vec)
//int get_type_name_data(const std::string& name, std::vector<type_names*> types_vec)
//int get_types_data(const std::string& name, std::vector<pokemon_types*> pokemon_types_vec)
//int get_stats_data(const std::string& name, std::vector<stats*> pokemon_stats_vec)
//int get_exp_data(const std::string& name, std::vector<experience*> exp_vec)
//


