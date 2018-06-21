#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include "culturalobject.h"
bool readLineToArray (std::string & line, std::vector<std::string> & array, char delim);

void parser(std::ifstream &ifstr, CulturalObject objects[],
            unsigned needToRead, unsigned skip = 0);
            
void objectsToMap (CulturalObject objects[], unsigned size, std::vector<std::map<std::string, std::vector<CulturalObject *>>> & Fields);
