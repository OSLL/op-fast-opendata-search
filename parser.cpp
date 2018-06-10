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
    for (int j = 0, i = 0; (line[j] != '\n') && j < line.size(); j++) {//here is the bug - cannot read last element (Tax ID or whatever)
        if (line[j] == '\"' && outline) { //it was {j < line.size() && i < size}
            outline = false;
            //std::cout << "I am outline now, j = " << j << "\n"; //debug
            continue;
        }
        if (line[j] == '\"' && !outline) {
            if (line[j + 1] == '\"') {//if we have 2 quotes symbol in a row
                temp.at(tempcounter) = line[j++];//move index to the right
                tempcounter++;
                std::cout << "founded 2 \" in a row, line[j++] = "<< line [j] << "\n";//debug
            }
            else {
                outline = true;//we must went off only if there aren't two quotes in a row
                //std::cout << "Back to the line \n";//debug
            }
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
    //write the last element
    if (outline)//debug
        std::cout << temp << "This is last line\n"; //debug
    std::cout << "Writing last element: " << temp << " , it's size before = " << temp.size();//dbg
    temp.resize(tempcounter);
    std::cout << "\ntempcounter = " <<tempcounter;//debug
    std::cout << "\nstill here, size after resizing = " << temp.size();//dbg
    array[size - 1] = temp;
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
        unsigned lineSize = 1;
        for (int i = 0; i < firstLine.size(); i++) {
            if (firstLine[i] == ',')
                lineSize++;
        }
        std::string * arrayOfFields;
        arrayOfFields = new std::string [lineSize];
        readLineToArray (firstLine, arrayOfFields, lineSize);
        std::cout << "size of first element = " << arrayOfFields[0].size() << '\n';//debug
        std::cout << "size of last element = " << arrayOfFields[lineSize].size();//debug
        for (unsigned i = 0; i < lineSize; i++) {
            std::string temp = arrayOfFields[i];
            std::cout <<"Iteration №"<<i<<", element ="<<arrayOfFields[i]<<'\n';//debug
            std::cout << i<<"-ый элемент массива строк = " <<arrayOfFields[i] << '\n';//debug
            if (temp.compare("oid") == 0) {
                id_place = i;
                std::cout << "id_place = " << id_place << '\n';//debug
            }
            else if (temp.compare("name") == 0) {
                name_place = i;
                std::cout << "name_place = " << name_place << '\n';//debug
            }
            else if (temp.compare("addressline") == 0) {
                address_place = i;
                std::cout << "address_place = " << address_place << '\n';//debug
            }
            else if (temp.compare("coord_shirota") == 0) {
                lat_place = i;
                std::cout << "coord_shirota = " << lat_place << '\n';//debug
            }
            else if (temp.compare("coord_dolgota") == 0) {
                long_place = i;
                std::cout << "coord_dolgota = " << long_place << '\n';//debug
            }
            else if (temp.compare("description") == 0) {
                description_place = i;
                std::cout << "description_place = " << description_place << '\n';//debug
            }
            else if (temp.compare("obj_history") == 0) {
                histRef_place = i;
                std::cout << "histRef_place = " << histRef_place << '\n';//debug
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

        std::string tempLine;
        for (unsigned i = 0; i < readFrom; i++) {
            ifstr.sync();
            getline(ifstr, tempLine); //skip unnecessary lines
        }
        std::string * goalArrayOfFields;
        goalArrayOfFields = new std::string[lineSize]; //Should I delete it later?
        while (readFrom < readTo && !ifstr.eof()) {
           ifstr.sync();
           getline(ifstr, tempLine);
           std::string goalLine = tempLine;
           /* if line readed patrially, add old line to backupLine and call
           read to array function with the full string 
           */
           while (!(readLineToArray(goalLine, goalArrayOfFields, lineSize))) { 
                ifstr.sync();
                getline(ifstr, tempLine);
                goalLine.append(tempLine);
           }   
           objects[readFrom] = CulturalObject(std::stoi(goalArrayOfFields[id_place]),
                    std::stod(goalArrayOfFields[lat_place]),
                    std::stod(goalArrayOfFields[long_place]),
                    goalArrayOfFields[name_place]); //call the constructor of CulturalObject
            objects[readFrom].setAddress(goalArrayOfFields[address_place]);
            objects[readFrom].setDescription(goalArrayOfFields[description_place]);
            objects[readFrom].setHistRef(goalArrayOfFields[histRef_place]);
            readFrom++;
        }
            delete [] goalArrayOfFields;
    }
}
