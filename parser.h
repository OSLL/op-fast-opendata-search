#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "culturalobject.h"
void readLineToArray (std::string & line, std::string * array, unsigned size);

void parser(std::ifstream &ifstr, CulturalObject objects[], unsigned readFrom, unsigned readTo);
