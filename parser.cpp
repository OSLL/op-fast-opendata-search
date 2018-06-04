#include <iostream>
#include <fstream>
#include "culturalobject.h"

/*
This function turns every straight line to the secondary array of values like name, address etc.
Array contains only sequence of "c-style strings", without any reference to CulturalObject
*/
void readLineToArray (char line[], char * array[], unsigned size) {
    int i = 0;
    while (*line++ && i < size) {
        if (*line == ',') {
            i++;
            continue;
        }
        *array[i] = *line;
        array[i]++;
    }
}
         
/*
return false if file has been read till the end
return true if file 
*/
bool parser(std::ifstream &ifstr, CulturalObject objects[], unsigned readFrom, unsigned readTo) {
    unsigned id_place = 0;
    unsigned name_place = 0;
    unsigned lat_place = 0;
    unsigned long_place = 0;
    unsigned address_place = 0;
    unsigned description_place = 0;
    unsigned histRef_place = 0;
    
    if (ifstr.is_open()) {
        /*lets read first line and assign each value
        as a type - id, name or whatever else
        */
        char firstLine [256];
        ifstr.getline(firstLine, 256);
        unsigned lineSize = 1;
        while (*firstLine++) {
            if (*firstLine = ',')
                lineSize++;
        }
        char arrayOfFields[lineSize][100];
        readLineToArray (firstLine, arrayOfFields, lineSize);
        for (unsigned i = 0; i < lineSize; i++) {
            if (*arrayOfFields[i] == "oid")
                id_place = i;
            else if (*arrayOfFields[i] == "name")
                name_place = i;          
            else if (*arrayOfFields[i] == "addressline")
                address_place = i; 
            else if (*arrayOfFields[i] == "metro_shirota")
                lat_place = i;  
            else if (*arrayOfFields[i] ==  "metro_dolgota")
                long_place = i;
            else if (*arrayOfFields[i] == "description")
                description_place = i;   
            else if (*arrayOfFields[i] == "obj_history")
                histRef_place = i;  
        }
        /*
        now we know indexes of all necessary values and can make
        deserealization of csv - file
        */
        char goalLine [5000];
        for (unsigned i = 0; i < readFrom; i++)
            ifstr.getline(goalLine); //skip unnecessary lines
        while (readFrom < readTo && *goalLine != EOF) {
            char goalArrayOfFields[lineSize][256];
            ifstr.getline(goalLine, 5000);
            if (*goalLine == EOF)
                return false;
            readLineToArray(goalLine, goalArrayOfFields, lineSize);
            objects[readFrom] = CulturalObject((unsigned)goalArrayOfFields[id_place],
                (double)goalArrayOfFields[lat_place],
                (double)goalArrayOfFields[long_place],
                goalArrayOfFields[name_place]); //call the constructor of CulturalObject
            objects[readFrom].setAddress(goalArrayOfFields[address_place]);
            objects[readFrom].setDescription(goalArrayOfFields[description_place]);
            objects[readFrom].setHistRef(goalArrayOfFields[histRef_place]);
            readFrom++;
        }
        if (*goalLine == EOF)
            return false;
        else
            return true;
    }
}
