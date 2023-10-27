#ifndef _DICTIONARY_H
#define _DICTIONARY_H


#include "fraction.h"
#include "stack.h"
#include <cstdint>
#include <stdexcept>
#include <string>

enum DictionaryStatus {
    UNUSED, IN_USE, DELETED
};

const int TABLE_SIZE = 127;


class Dictionary{
public:
    Dictionary() { clear(); }
    ~Dictionary() = default;

    bool isEmpty() { return index == 0; }
    uint32_t size() { return index; }

    void clear();

    void add(const std::string &, const Fraction);

    Fraction search(const std::string &);

private:
    int index;
    std::string keys[TABLE_SIZE];
    Fraction values[TABLE_SIZE];
    DictionaryStatus status[TABLE_SIZE];
};

#endif
