#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "culturalobject.h"
bool readLineToArray (std::string & line, std::vector<std::string> & array);

void parser(std::ifstream &ifstr, CulturalObject objects[],
            unsigned needToRead, unsigned skip = 0);
