#define EXPECTED 2 //Expected number of arguments is 2 because the first is the function name
#include <iostream>
#include <fstream>
#include "culturalobject.h"
#include "parser.h"
#include "objectcounter.h"

/*
*/

void doTest(std::ifstream & in) {
    CulturalObject * array;
    array = new CulturalObject [10];
    parser(in, array, 10);
    for (int i = 0; i < 10; i++) {
        std::cout << "Object #" << (i+1) << "\nName = " << array[i].getName();
        std::cout << "\nAddress = " << array[i].getAddress();
        std::cout << "\nDescription = " << array[i].getDescription();
        std::cout << "\nHistRef = " << array[i].getHistRef();
        std::cout << "\nLatitude = " << array[i].getLatitude();
        std::cout << "\nLongitude = " << array[i].getLongitude() <<"\n\n";
}
    
    delete[] array;
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL,"Russian");
    if (argc < EXPECTED) {
        std::cerr << "No <filename> found. Please call the program with correct file\n";
        std::cerr << "Using: ./opendata_search.out <filename>\n";
        std::cerr << "Example: ./opendata_search.out test-data.csv\n";
        return 1;
    }
    char* filename = argv[1];
    std::ifstream in(filename);
    if (in.is_open()) {
        int numberOfObjects = ObjectCounter(in);//test
        std::cout << "Number of objects founded: " << numberOfObjects << '\n';//test
        doTest(in);
        in.close();
        return 0;
    }
    else {
        std::cerr << "File " << filename << " is NOT exist\nPlease choose correct file\n";
        std::cerr << "Using: ./opendata_search.out <filename>\n";
        return 1;
    }
}
    

