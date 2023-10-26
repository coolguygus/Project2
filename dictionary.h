#ifndef _DICTIONARY_H
#define _DICTIONARY_H

#include <cstdint>
#include <stdexcept>
#include <string>
#include <iostream>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include "fraction.h"

using namespace std;

const uint32_t TABLE_SIZE = 101;

class Dictionary {
public:
    Dictionary() { clear(); } 
    ~Dictionary() = default;

    bool isEmpty() { 
        return nItems == 0; 
    }
    uint32_t size() { 
        return nItems; 
    }

    void clear();
    void add(const string,const Fraction);
    Fraction search(const string);
    void remove(const string &);

private:
    string
        keys[TABLE_SIZE];
    Fraction
        values[TABLE_SIZE];
    uint32_t
        nItems;

};


#endif //_DICTIONARY_H
