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

bool readLineToArray (std::string & line, std::string * array, unsigned size) {
    std::string temp;
    temp.resize(line.size());
    unsigned tempcounter = 0;
    bool outline = true;
    for (int j = 0, i = 0; j < line.size() && i < size; j++) {//here is the bug - cannot read last element (Tax ID)
        if (line[j] == '\"' && outline) {
            outline = false;
            //std::cout << "I am outline now\n"; //debug
            continue;
        }
        if (line[j] == '\"' && !outline) {
            //std::cout << "Back to line\n"; //debug
            outline = true;
            continue;
        }
        if (line[j] == ',' && outline) {
            //std::cout << temp << " this is readed line\n"; //debug
            temp.resize(tempcounter);
            array[i] = temp;
            tempcounter = 0;
            temp.clear();
            temp.resize(line.size());
            i++;
        }
        else {
            temp.at(tempcounter) = line[j];
            tempcounter++;
        } 
    }
    //std::cout << "exit from function, return to the parser\n";//debug
    return outline; //if outline, string readed successfully, or we need to add information in it
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
        unsigned lineSize = 1;
        for (int i = 0; i < firstLine.size(); i++) {
            if (firstLine[i] == ',')
                lineSize++;
        }
        std::string * arrayOfFields;
        arrayOfFields = new std::string [lineSize];
        readLineToArray (firstLine, arrayOfFields, lineSize);
        for (unsigned i = 0; i < lineSize; i++) {
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
            }
            else if (arrayOfFields[i].compare("coord_dolgota") == 0) {
                long_place = i;
            }
            else if (arrayOfFields[i].compare("description") == 0) {
                description_place = i;
            }
            else if (arrayOfFields[i].compare("obj_history") == 0) {
                histRef_place = i;
            }
        }
        if (!(name_place && address_place && lat_place && long_place
            && description_place && histRef_place)) {
            delete [] arrayOfFields;
            return; //receive file with incorrect fields, need flag or try/catch in this place
        } //this is unnecessary and bad block please replace it with 'try/catch' 
        delete [] arrayOfFields;
        
        /*
        now we know indexes of all necessary values and can make
        deserialization of csv-file
        */

        std::string goalLine;
        for (unsigned i = 0; i < readFrom; i++) {
            ifstr.sync();
            getline(ifstr, goalLine); //skip unnecessary lines
        }
        //std::cout << "\nReaded unnecessary line is "<< goalLine << '\n'; //debug
        while (readFrom <= readTo) {
            std::string * goalArrayOfFields;
            goalArrayOfFields = new std::string[lineSize]; //Should I delete it later?
            while (!ifstr.eof()) {
                ifstr.sync();
                getline(ifstr, goalLine);
                //std::cout << "\nReaded line is "<< goalLine << '\n'; //debug
                std::string backupLine = goalLine;
                //std::cout << "backupLine is " << backupLine << '\n'; //debug
                /* if line readed patrially, add old line to backupLine and call
                read to array function with the full string 
                */
                //int reservedSize = 3000;
                while (!(readLineToArray(backupLine, goalArrayOfFields,//maxSize will be 10 times
                      lineSize))) {//greater than avrg line size 
                    ifstr.sync();
                    getline(ifstr, goalLine);
                    //std::cout << goalLine << " goalLine\n";//debug
                    //backupLine.resize(reservedSize);
                    backupLine.append(goalLine);
                    //std::cout << backupLine << " backupLine\n";//debug
                    //reservedline hardcoded higher, please fix it
                }   
                //std::cout << goalArrayOfFields[lat_place] << ": This is latitude\n";//debug
                objects[readFrom] = CulturalObject(std::stoi(goalArrayOfFields[id_place]),
                    std::stod(goalArrayOfFields[lat_place]),
                    std::stod(goalArrayOfFields[long_place]),
                    goalArrayOfFields[name_place]); //call the constructor of CulturalObject
                objects[readFrom].setAddress(goalArrayOfFields[address_place]);
                //std::cout << goalArrayOfFields[address_place] << " test\n"; //debug 
                objects[readFrom].setDescription(goalArrayOfFields[description_place]);
                objects[readFrom].setHistRef(goalArrayOfFields[histRef_place]);
                readFrom++;
            }
            delete [] goalArrayOfFields;
        }
    }
}
