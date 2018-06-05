#include <iostream>
#include <fstream>
#include <string>
#include "culturalobject.h"

/*
This function turns every straight line to the secondary array of values like name, address etc.
Array contains only sequence of "c-style strings", without any reference to CulturalObject
*/

/* in line below function receive first parameter as reference to string and 
the second as a reference to array of strings (at least I tried to do this)*/

void readLineToArray (std::string & line, std::string * array, unsigned size) {
    std::string temp;
    for (int j = 0, i = 0, tempcounter = 0; j < line.size() && i < size; j++) {
        if (line[j] == ',') {
            array[i] = temp;
            tempcounter = 0;
            temp.clear();
            i++;
        }
        else
            temp[tempcounter] = line[j]; 
    }
}
         

void parser(std::ifstream &ifstr, CulturalObject objects[], unsigned readFrom, unsigned readTo) {
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
        std::string firstLine;
        ifstr.getline(firstLine);
        unsigned lineSize = 1;
        for (int i = 0; i < firstLine.size(); i++) {
            if (firstLine[i] = ',')
                lineSize++;
        }
        std::string arrayOfFields[lineSize];
        readLineToArray (firstLine, arrayOfFields, lineSize);
        for (unsigned i = 0; i < lineSize; i++) {
            if (arrayOfFields[i] == "oid")
                id_place = i;
            else if (arrayOfFields[i] == "name")
                name_place = i;          
            else if (arrayOfFields[i] == "addressline")
                address_place = i; 
            else if (arrayOfFields[i] == "metro_shirota")
                lat_place = i;  
            else if (arrayOfFields[i] ==  "metro_dolgota")
                long_place = i;
            else if (arrayOfFields[i] == "description")
                description_place = i;   
            else if (arrayOfFields[i] == "obj_history")
                histRef_place = i;  
        }
        /*
        now we know indexes of all necessary values and can make
        deserealization of csv - file
        */
        std::string goalLine;
        for (unsigned i = 0; i < readFrom; i++)
            ifstr.getline(goalLine); //skip unnecessary lines
        while (readFrom < readTo && goalLine != EOF) {
            std::string goalArrayOfFields[lineSize];
            while (!ifstr.eof())
            ifstr.getline(goalLine);
            readLineToArray(goalLine, goalArrayOfFields, lineSize);
            objects[readFrom] = CulturalObject(std::stoi(goalArrayOfFields[id_place]),
                std::stod(goalArrayOfFields[lat_place]),
                std::stod(goalArrayOfFields[long_place]),
                goalArrayOfFields[name_place]); //call the constructor of CulturalObject
            objects[readFrom].setAddress(goalArrayOfFields[address_place]);
            objects[readFrom].setDescription(goalArrayOfFields[description_place]);
            objects[readFrom].setHistRef(goalArrayOfFields[histRef_place]);
            readFrom++;
        }
    }
}
