/*It is a simple application,
that receive file name as a parameter
and return information about consist
this file or not
*/
#define EXPECTED 2 //Expected number of arguments is 2 because the first is the function name
#include <iostream>
#include <fstream>
#include "culturalobject.h"
#include "parser.h" 

void doTest(std::ifstream & in) {
    CulturalObject * array;
    array = new CulturalObject [5];
    parser(in, array, 0, 2);
    std::cout << array[1].getDescription() << ' ' << array[1].getAddress();
    delete[] array;
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL,"Russian");
    char* filename = argv[1];
    std::ifstream in(filename);
    if (in.is_open()) {
        doTest(in);
        in.close();
        return 0;
    }
    else {
        std::cout << "File " << filename << " is NOT exist\n";
        return 0;
    }
}
    

