//this is the impletation of data manipulation
#include <iostream>
#include <fstream>


using namespace std;


int check_file(const std::string& name){
    ifstream file(name);
   
    if(!file.is_open()){
        
        return 0;
    }
    file.close();
    return 1;
}


int get_data(const std::string& name){
    ifstream file(name.c_str());

    string line;

    while (getline(file,line)) {
        cout << line << endl;
    }

    file.close();

    return 0;
}
