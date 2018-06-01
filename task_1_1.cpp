/*It is a simple application,
that receive file name as a parameter
and return information about consist
this file or not
*/
#define EXPECTED 2 //Expected number of arguments is 2 because the first is the function name
#include <iostream>
#include <fstream>

int main(int argc, char* argv[]) {
    if (argc < EXPECTED || argc > EXPECTED) {
        std::cerr << "Error. Using: ./task_1_1.out name_of_file\n";
        return 1;
    }
    char* filename = argv[1];
    std::ifstream in(filename);
    if (in.is_open()) {
        std::cout << "File " << filename << " is exist\n";
        return 0;
    }
    else {
        std::cout << "File " << filename << " is NOT exist\n";
        return 0;
    }
}
    

