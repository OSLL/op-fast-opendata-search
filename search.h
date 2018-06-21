#pragma once

#include <iostream>
#include <string>
#include <search.h>
#include "culturalobject.h"

void search(CulturalObject objects[], std::string toFind, unsigned size);

void complexSearch(std::vector<std::map<std::string, std::vector<CulturalObject *>>> fields, std::vector<std::string> toFind);
