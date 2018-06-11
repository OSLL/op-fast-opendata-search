#include <iostream>
#include <string>
#include <search.h>

/*
This function receive array of CulturalObjects and string toFind,
then analyze fields of each CulturalObject and if function find matches it print it
in standart output: name of object found and then field with matches.
*/

void search(CulturalObject (&objects)[], std::string toFind, unsigned size) {
    for (unsigned i = 0; i < size && objects[i].checkId(); i++) {
        //logic of search and print
    }
}


