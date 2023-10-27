#include "dictionary.h"

void Dictionary::add(const std::string &key, const Fraction value){
    uint32_t x = index;
        while(status[x] != UNUSED){
            if (x == TABLE_SIZE){
                std::cout <<"Tabl is Full"<< std::endl;
            }
        x++;
        }
        keys[x] = key;
        values[x] = value;
        //x = (x+1) % TABLE_SIZE;
        index++;
}

Fraction Dictionary::search(const std::string &s){
    int x = 0;
    for (int x = 0; x < index; x++){
        if (keys[x] == s){
            return values[x];
        }
    }
    return Fraction();
}

void Dictionary::clear(){
    for (uint32_t x = 0; x < TABLE_SIZE; x++){
        status[x] = UNUSED;
        values[x] = -1;
        keys[x] = "";
    }
    index = 0;
}
