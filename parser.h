#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "culturalobject.h"
bool readLineToArray (std::string & line, std::string * array, unsigned size, unsigned maxSize);

void parser(std::ifstream &ifstr, CulturalObject objects[], unsigned readFrom, unsigned readTo);
