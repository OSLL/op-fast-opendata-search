#include <iostream>
#include <fstream>
#include <string>
#include "culturalobject.h"
#include "parser.h"

/*
This function turns every straight line to the secondary array of values like name, address etc.
Array contains only sequence of "c-style strings", without any reference to CulturalObject
*/

/* in line below function receive first parameter as reference to string and 
the second as a reference to array of strings (at least I tried to do this)*/

void readLineToArray (std::string & line, std::string * array, unsigned size, unsigned maxSize) {
    std::string temp;
    temp.resize(maxSize);
    unsigned tempcounter = 0;
    //std::cout << "in read to array" << line << " Line.size() = " << line.size() <<'\n'; //debug
    for (int j = 0, i = 0; j < line.size() && i < size; j++) {
        if (line[j] == ',') {
            temp.resize(tempcounter);
            array[i] = temp;
            tempcounter = 0;
            temp.clear();
            temp.resize(maxSize);
            i++;
        }
        else {
            temp.at(tempcounter) = line[j];
            //if (j%10 == 0)//debug
                //std::cout << temp[tempcounter] << ' ' << line[j] << tempcounter << '\n';//debug 
            tempcounter++;
            //std::cout << temp << '\n'; //debug
        } 
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
        getline(ifstr, firstLine);
        //std::cout << firstLine << "\nfirstLine\n"; //debug
        unsigned lineSize = 1;
        for (int i = 0; i < firstLine.size(); i++) {
            if (firstLine[i] == ',')
                lineSize++;
        }
        std::cout << "lineSize = " << lineSize << '\n'; //debug
        std::string * arrayOfFields;
        arrayOfFields = new std::string [lineSize];
        readLineToArray (firstLine, arrayOfFields, lineSize, lineSize);
        for (unsigned i = 0; i < lineSize; i++) {
            //std::cout << arrayOfFields[i] << "\nin cycle \'for\', \n";//debug
            //std::cout << arrayOfFields[i].compare("oid") << '\n';
            if (arrayOfFields[i].compare("oid") == 0) {
                id_place = i;
            }
            else if (arrayOfFields[i].compare("name") == 0) {
                name_place = i;
            }
            else if (arrayOfFields[i].compare("addressline") == 0) {
                address_place = i;
            }
            else if (arrayOfFields[i].compare("coord_shirota") == 0) {
                lat_place = i;
                //std::cout << arrayOfFields[i] << "this is shirota\n";//debug
            }
            else if (arrayOfFields[i].compare("coord_dolgota") == 0) {
                long_place = i;
                //std::cout << arrayOfFields[i] << "this is dolgota\n";//debug
            }
            else if (arrayOfFields[i].compare("description") == 0) {
                description_place = i;
            }
            else if (arrayOfFields[i].compare("obj_history") == 0) {
                histRef_place = i;
            }
        }
        std::cout << (id_place && name_place && address_place && lat_place && long_place
            && description_place && histRef_place); //debug
        if (id_place && name_place && address_place && lat_place && long_place
            && description_place && histRef_place) {
            delete [] arrayOfFields;
            return; //receive file with incorrect fields, need flag or try/catch in this place
        }
        delete [] arrayOfFields;
        /*
        now we know indexes of all necessary values and can make
        deserealization of csv - file
        */
        std::string goalLine;
        for (unsigned i = 0; i < readFrom; i++)
            getline(ifstr, goalLine); //skip unnecessary lines
        while (readFrom < readTo) {
            std::string * goalArrayOfFields;
            goalArrayOfFields = new std::string[lineSize]; //Should I delete it later?
            while (!ifstr.eof())
            getline(ifstr, goalLine);
            std::cout << "\nReaded line is "<< goalLine << '\n'; //debug
            readLineToArray(goalLine, goalArrayOfFields, lineSize, 700);//maxsize hardcoded
            objects[readFrom] = CulturalObject(std::stoi(goalArrayOfFields[id_place]),
                std::stod(goalArrayOfFields[lat_place]),
                std::stod(goalArrayOfFields[long_place]),
                goalArrayOfFields[name_place]); //call the constructor of CulturalObject
            objects[readFrom].setAddress(goalArrayOfFields[address_place]);
            std::cout << goalArrayOfFields[address_place] << " test\n"; //debug 
            objects[readFrom].setDescription(goalArrayOfFields[description_place]);
            objects[readFrom].setHistRef(goalArrayOfFields[histRef_place]);
            readFrom++;
            delete [] goalArrayOfFields;
        }
    }
}
