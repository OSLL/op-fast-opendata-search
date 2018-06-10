#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "culturalobject.h"
#include "parser.h"

/*
This function turns every straight line to the secondary array of values like name, address etc.
Array contains only sequence of "c-style strings", without any reference to CulturalObject
*/

/* in line below function receive first parameter as reference to string and 
the second as a reference to array of strings (at least I tried to do this)*/

bool readLineToArray (std::string & line, std::vector<std::string> & array) {
    std::string temp;
    bool outline = true;
    for (int j = 0, i = 0; (line[j] != '\n') && j < line.size(); j++) {//i for debug
        if (line[j] == '\"' && outline) {
            outline = false;
            continue;
        }
        if (line[j] == '\"' && !outline) {
            if (line[j + 1] == '\"') {
                temp += '\n';
                j++;
                std::cout << "founded 2 \" in a row, line[j++] = "<< line [j] << "\n";//debug
            }
            else {
                outline = true;//we must went off only if there aren't two quotes in a row
            }
            continue;
        }
        if (line[j] == ',' && outline) {
            std::cout << temp << " this is readed line\n"; //debug
            array.push_back(temp);
            temp.clear();
            std::cout << "readed line is " << array[i] << "; size is " << array[i].size();//debug
            i++;//debug
        }
        else {
            temp += line[j];
        } 
    }
    //write the last element
    std::cout << "Writing last element: " << temp << " , it's size of it = " << temp.size();//dbg
    temp.pop_back();//remove last symbol from the last element
    array.push_back(temp);
    std::cout << "exit from function, return to the parser\n";//debug
    std::cout << "outline = " << outline << '\n';//debug
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
        std::vector<std::string> sequenceOfElements;
        readLineToArray (firstLine, sequenceOfElements);
        std::cout << "size of first element = " << sequenceOfElements[0].size() << '\n';//debug
        std::cout << "size of last element = ";//debug
        std::cout <<sequenceOfElements[sequenceOfElements.size()-1].size() <<'\n';//dbg
        for (unsigned i = 0; i < sequenceOfElements.size(); i++) {
            std::string temp = sequenceOfElements[i];
            std::cout <<"Iteration №"<<i<<", element ="<<sequenceOfElements[i]<<'\n';//debug
            std::cout << i<<"-ый элемент массива строк = " <<sequenceOfElements[i] << '\n';//debug
            std::cout << "размер этого элмента = " << sequenceOfElements[i].size() << '\n';//debug
            if (temp.compare("﻿oid") == 0) {
                id_place = i;
                std::cout << "id_place = " << id_place << '\n';//debug
                std:: cout <<"size =" <<sequenceOfElements[i].size() << '\n';//debug
            }
            else if (temp.compare("name") == 0) {
                name_place = i;
                std::cout << "name_place = " << name_place;//debug
                std:: cout <<"\nsize =" <<sequenceOfElements[i].size() << '\n';//debug
            }
            else if (temp.compare("addressline") == 0) {
                address_place = i;
                std::cout << "address_place = " << address_place << '\n';//debug
                std:: cout <<"size =" <<sequenceOfElements[i].size() << '\n';//debug
            }
            else if (temp.compare("coord_shirota") == 0) {
                lat_place = i;
                std::cout << "coord_shirota = " << lat_place << '\n';//debug
            }
            else if (temp.compare("coord_dolgota") == 0) {
                long_place = i;
                std::cout << "coord_dolgota = " << long_place << '\n';//debug
                std:: cout <<"size =" <<sequenceOfElements[i].size() << '\n';//debug
            }
            else if (temp.compare("description") == 0) {
                description_place = i;
                std::cout << "description_place = " << description_place << '\n';//debug
                std:: cout <<"size =" <<sequenceOfElements[i].size() << '\n';//debug
            }
            else if (temp.compare("obj_history") == 0) {
                histRef_place = i;
                std::cout << "histRef_place = " << histRef_place << '\n';//debug
                std:: cout <<"size =" <<sequenceOfElements[i].size() << '\n';//debug
            }
        }
        if (!(name_place && address_place && lat_place && long_place
            && description_place && histRef_place)) {
            //delete sequenceOfElements;
            return; //receive file with incorrect fields, need flag or try/catch in this place
        } //this is unnecessary and bad block please replace it with 'try/catch' 
        //delete sequenceOfElements;
        
        /*
        now we know indexes of all necessary values and can make
        deserialization of csv-file
        */

        std::string tempLine;
        for (unsigned i = 0; i < readFrom; i++) {
            ifstr.sync();
            getline(ifstr, tempLine); //skip unnecessary lines
        }
        std::vector<std::string> goalVector;
        while (readFrom < readTo && !ifstr.eof()) {
           ifstr.sync();
           getline(ifstr, tempLine);
           std::string goalLine = tempLine;
           /* if line readed patrially, add old line to backupLine and call
           read to vector function with the full string 
           */
           while (!(readLineToArray(goalLine, goalVector))) { 
                ifstr.sync();
                getline(ifstr, tempLine);
                goalLine.append(tempLine);
                goalVector.clear();
           }   
           objects[readFrom] = CulturalObject(std::stoi(goalVector[id_place]),
                    std::stod(goalVector[lat_place]),
                    std::stod(goalVector[long_place]),
                    goalVector[name_place]); //call the constructor of CulturalObject
            objects[readFrom].setAddress(goalVector[address_place]);
            objects[readFrom].setDescription(goalVector[description_place]);
            objects[readFrom].setHistRef(goalVector[histRef_place]);
            readFrom++;
            goalVector.clear();
        }
            //delete goalVector;
    }
}
