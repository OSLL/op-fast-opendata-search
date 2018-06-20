#include <iostream>
#include <string>
#include <search.h>
#include "culturalobject.h"

/*
This function receive array of CulturalObjects and string toFind,
then analyze fields of each CulturalObject and if function find matches it print it
in standart output: name of object found and then field with matches (if matches
will be founded only in name field, only name of object will be printed).
*/

void search(CulturalObject objects[], std::string toFind, unsigned size) {
    bool nameMatch = false;
    bool descrMatch = false;
    bool histMatch = false;
    for (unsigned i = 0; i < size && objects[i].checkId(); i++) {
        //Firstable we will find in which fields we have matches
        if (objects[i].getName().find(toFind) != std::string::npos) {
            nameMatch = true;
        }
        if (objects[i].getDescription().find(toFind) != std::string::npos) {
            descrMatch = true;
        }
        if (objects[i].getHistRef().find(toFind) != std::string::npos) {
            histMatch = true;
        }

        //Then we'll print founded matches in std::out or just go forward if no matches found
        if (nameMatch || descrMatch || histMatch) {
            //print name in any case:
            std::cout << "Object, id #"<< objects[i].getId() << ": " << objects[i].getName();
            if (descrMatch)
                std::cout << '\n' << objects[i].getDescription();
            if (histMatch)
                std::cout << '\n' << objects[i].getHistRef();
            std::cout << std::endl;
        }
        nameMatch = descrMatch = histMatch = false;
    }
}


