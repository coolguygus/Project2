#include "dictionary.h"

using namespace std;

void Dictionary::clear() {
    for(uint32_t i = 0; i < TABLE_SIZE; i++) {
        keys[i] = "";
        values[i] = -1;
    }
    nItems = 0;
}

void Dictionary::add(const string key, const Fraction value) {
    int pos = nItems;
	for (int i = 0; i < TABLE_SIZE; i++){
		if (keys[i] == key){
			values[i] = value;
			return;
		}
	}
    keys[pos] = key;
    values[pos] = value;

    nItems ++;
}

Fraction Dictionary::search(const string search_string) {
    for (int x = 0; x < nItems; x++) {
        if (keys[x] == search_string) {
            return values[x];
        }
    }
    return Fraction();}
