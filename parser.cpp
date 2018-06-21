#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <iterator>
#include "culturalobject.h"
#include "parser.h"

#define LOCALE_EN "_en"
#define LOCALE_RU "" //this is default locale for this program
#define ID "oid"
#define NAME "name"
#define ADDRESS "addressline"
#define LAT "coord_shirota"
#define LONG "coord_dolgota"
#define DESCRIPTION "description"
#define HISTREF "obj_history"
#define EMPTY ""

inline void fillMultimap (std::vector<std::string> splitted, std::map<std::string, std::vector<CulturalObject *>> & field, CulturalObject * ptrToObject) {
    std::map<std::string, std::vector<CulturalObject *>>::iterator fielditer = field.begin();
    for (unsigned i = 0; i < splitted.size(); i++) {
        fielditer = field.find(splitted[i]);//find if there is key with this word
        if (fielditer != field.end()) {//if it is here 
            fielditer->second.push_back(ptrToObject);//add pointer to the current object
            //std::cout << "Key is " << fielditer->first << ", Value is " << ptrToObject << std::endl;//debug
        }
        else {//if not
            std::vector<CulturalObject *> temp;//we need to construct new vector
            temp.push_back(ptrToObject);//and then add to it pointer to our CulturalObject
            field.insert(make_pair(splitted[i], temp));//make a new key and add a word in the object as key and vector as value
        }
    }
}

/*
This secondary function receive line as a string and read it in the vector of strings,
each line separates by delimiter, default delimiter is comma.
Using: readLineToArray(string NeedToTurnIntoTheVector, vector GoalVector).
*Be careful! GoalVector must be clean, because function append elements to it!
Parameters are received by the reference.
Function return true if reading was succesfull and end of csv-line has reached and false if not.
Also used to split field with specified delimiter e.g. space symbol
*/

bool readLineToArray (std::string & line, std::vector<std::string> & array, char delim = ',') {
    std::string temp;
    bool outline = true;
    for (int i = 0; (line[i] != '\n') && i < line.size(); i++) {
        if (line[i] == '\"' && outline) {
            outline = false;
            continue;
        }
        if (line[i] == '\"' && !outline) {
            if (line[i + 1] == '\"') {//for correct search of double quotes
                temp += '\"';
                i++;
            }
            else {
                outline = true;//we must went off only if there aren't two quotes in a row
            }
            continue;
        }
        if (line[i] == delim && outline) {
            array.push_back(temp);
            temp.clear();
        }
        else {
            temp += line[i];
        } 
    }
    temp.pop_back(); //remove last symbol from the last element
    array.push_back(temp); //write the last element
    return outline; //if outline, string readed successfully, or we need to add information in it
}

/*
This function receive array of CulturalObjects and fill it with the text lines,
readed from csv-file.
Using:
    parser(ifstream FileToRead, CulturalObject[] objectsToWrite, int MustRead)
    parser(ifstream FileToRead, CulturalObject[] objectsToWrite, int MustRead, int skip).
Function skip unnecessary lines in file (until skip index), default parameter for skipping = 0.
and then rewrite received array with new objects from index 0 to MustRead.

*/

void parser(std::ifstream &ifstr, CulturalObject objects[],
             unsigned needToRead, unsigned skip) {
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
        std::string firstLine;//receive the first line of csv-file,
        getline(ifstr, firstLine);// which contains list of headers
        std::vector<std::string> sequenceOfElements;
        readLineToArray (firstLine, sequenceOfElements);
        for (unsigned i = 0; i < sequenceOfElements.size(); i++) {
            std::string temp = sequenceOfElements[i];
            if (temp.compare(ID) == 0) {
                id_place = i;
            }
            else if (temp.compare(NAME) == 0) {
                name_place = i;
            }
            else if (temp.compare(ADDRESS) == 0) {
                address_place = i;
            }
            else if (temp.compare(LAT) == 0) {
                lat_place = i;
            }
            else if (temp.compare(LONG) == 0) {
                long_place = i;
            }
            else if (temp.compare(DESCRIPTION) == 0) {
                description_place = i;
            }
            else if (temp.compare(HISTREF) == 0) {
                histRef_place = i;
            }
        }
        if (!(name_place && address_place && lat_place && long_place
            && description_place && histRef_place)) {
            return; //receive file with incorrect fields, need flag or try/catch in this place
        } //this is unnecessary and bad block please replace it with 'try/catch' 
        //delete sequenceOfElements;
        
        /*
        now we know indexes of all necessary values and can make
        deserialization of csv-file
        */

        std::string tempLine;
        for (unsigned i = 0; i < skip; i++) {
            ifstr.sync();
            getline(ifstr, tempLine);
            std::string unnecessaryLine = tempLine;
            for (std::vector<std::string> temp;
                 !(readLineToArray(unnecessaryLine, temp));) {
                ifstr.sync();
                getline(ifstr, tempLine);
                unnecessaryLine.append(tempLine);
            }//skip unnecessary lines
        }
        std::vector<std::string> goalVector;
        for (unsigned i = 0; i < needToRead && !ifstr.eof(); i++) {
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
                goalVector.clear();//clean vector to rewrite it
           }
           if ((goalVector[lat_place] == "") || (goalVector[long_place] == "")) {
               objects[i] = CulturalObject(std::stoi(goalVector[id_place]),
                    goalVector[name_place]); //call the constructor without coordinates
           }
           else {
               objects[i] = CulturalObject(std::stoi(goalVector[id_place]),
                    std::stod(goalVector[lat_place]),
                    std::stod(goalVector[long_place]),
                    goalVector[name_place]); //call the common constructor
           }
           objects[i].setAddress(goalVector[address_place]);
           objects[i].setDescription(goalVector[description_place]);
           objects[i].setHistRef(goalVector[histRef_place]);
           goalVector.clear();
        }
    }
}

/*
This function receive array of CulturalObjects and std::vector of map collections.
Then it fills map collections with pairs of key and value, when
key is a word of CulturalObject field (words, contained in name, description,
adress and historical reference)
and value is a vector of pointers to the CulturalObject, which contain this word.
Each collection in this vector respond to the certain field of CulturalObject
*/

void objectsToMap (CulturalObject objects[], unsigned size, std::vector<std::map<std::string, std::vector<CulturalObject *>>> & Fields) {
    //std::cout << "We are in objects to map\n";//debug
    for (unsigned i = 0; i < size; i++) {
        std::string temp;
        std::vector<std::string> splittedFields;
        temp = objects[i].getName();
        splittedFields.clear();
        if (temp != EMPTY) {
            readLineToArray(temp, splittedFields, ' ');
            fillMultimap(splittedFields, Fields[0], &objects[i]);
        }
        temp = objects[i].getAddress();
        splittedFields.clear();
        if (temp != EMPTY) {
            readLineToArray(temp, splittedFields, ' ');
            fillMultimap(splittedFields, Fields[1], &objects[i]);
        }
        temp = objects[i].getDescription();
        splittedFields.clear();
        if (temp != EMPTY) {
            readLineToArray(temp, splittedFields, ' ');
            fillMultimap(splittedFields, Fields[2], &objects[i]);
        }
        temp = objects[i].getHistRef();
        splittedFields.clear();
        if (temp != EMPTY) {
            readLineToArray(temp, splittedFields, ' ');
            fillMultimap(splittedFields, Fields[3], &objects[i]);
        }
   }
}
