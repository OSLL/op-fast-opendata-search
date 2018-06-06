/*It is a simple application,
that receive file name as a parameter
and return information about consist
this file or not
*/
#define EXPECTED 2 //Expected number of arguments is 2 because the first is the function name
#include <iostream>
#include <fstream>
#include "culturalobject.h"

void doLogic(std::ifstream & in) {}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL,"Russian");
    char* filename = argv[1];
    std::ifstream in(filename);
    if (in.is_open()) {
        doLogic(in);
        return 0;
    }
    else {
        std::cout << "File " << filename << " is NOT exist\n";
        return 0;
    }
}
    

