#define EXPECTED 3 //Expected number of arguments is 3 because we need at least one key and one key value
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cstdlib>
#include "culturalobject.h"
#include "parser.h"
#include "objectcounter.h"
#include "search.h"
#include "geosearch.h"

#define MUSEUMS "./data/data-museums.csv"
#define SIGHTS "./data/data-sights.csv"
#define NO_FILE_NAME ""
#define NUM_OF_FIELDS 4 //name, address, description and histref

struct Arguments {
    std::string Filename;
    bool search;
    bool geosearch;
    bool complexsearch;
    std::string toFind;
    unsigned limit;
    Point coordinates;
    double radius;
    Arguments() {
        Filename = toFind = NO_FILE_NAME;
        search = geosearch = complexsearch = false;
        limit = 0U;
        radius = 0.0;
    }
};

void FunctionChoice (Arguments &args) {
    std::ifstream in(args.Filename);
    if (in.is_open()) {
        int numberOfObjects = ObjectCounter(in);
        in.clear();//nulling "eof" flag
        if (numberOfObjects > 0) {
            in.seekg(0, std::ios::beg);
            CulturalObject * objects;
            if (args.limit == 0) {
                objects = new CulturalObject[numberOfObjects];
                parser(in, objects, numberOfObjects);//fill array of objects
                if (args.complexsearch) {
                    std::vector<std::map<std::string, std::vector<CulturalObject *>>> fields(NUM_OF_FIELDS);
                    objectsToMap(objects, numberOfObjects, fields);
                    std::vector<std::string> toFind;
                    //std::cout << "In complexsearch\nReaded arg is: " << args.toFind << '\n';//debug
                    readLineToArray(args.toFind, toFind, ' ');
                    //for (unsigned i; i < toFind.size(); i++)//debug
                        //std::cout << "readed line "<< i+1 << "in arg is " << toFind[i] << '\n';//debug 
                    complexSearch(fields, toFind);
                }
                if (args.search) {
                    search(objects, args.toFind, numberOfObjects);
                }
                if (args.geosearch) {
                    geosearch(objects, numberOfObjects, args.coordinates, args.radius);
                }
                delete [] objects;     
            }
            else {
                unsigned size = args.limit;
                unsigned skip = 0;
                while (numberOfObjects > 0) {
                    in.seekg(0, std::ios::beg);
                    objects = new CulturalObject[size];
                    parser(in, objects, size, skip);
                    if (args.search) {
                        search(objects, args.toFind, size);
                    }
                    if (args.geosearch) {
                        geosearch(objects, size, args.coordinates, args.radius);
                    }
                    delete [] objects;
                    numberOfObjects -= size;
                    skip += size;
                    if (numberOfObjects < args.limit) {
                        size = numberOfObjects;
                    }
                }
            }
        }
        if (in.is_open()) {
            in.close();
        }
    }
    else {
        std::cerr << "File " << args.Filename << " is NOT exist\nPlease choose correct file\n";
        std::cerr << "Using: ./opendata_search.out -file <filename>\n";
    }

}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL,"Russian");
    if (argc < EXPECTED) {
        std::cerr << "No key found. Please call the program with correct file\n";
        std::cerr << "Using: ./opendata_search.out -keyname <keyvalue>\n";
        std::cerr << "Example: ./opendata_search.out -file test-data.csv -search \"test\"\n";
        return 1;
    }
    //Lets parse command line arguments to the object arg
    Arguments args;
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        if (arg == "-file") {
            args.Filename = (std::string) argv [++i];
        }
        if (arg == "-search") {
            args.search = true;
            args.toFind = (std::string) argv[++i];
        }
        if (arg == "-geosearch") {
            args.geosearch = true;
            std::string query = (std::string) argv[++i];
            std::vector<std::string> coordsWithRadius;
            std::string temp;
            for (int i = 0; i < query.length(); i++) {
                if (query.at(i) == ',') {
                    coordsWithRadius.push_back(temp);
                    temp.clear();
                }
                else {
                    temp += query.at(i);
                }
            }
            coordsWithRadius.push_back(temp);
            temp.clear();
            if (coordsWithRadius.size() != 3) {
                args.geosearch = false;
                std::cout << "Something wrong with geosearch query.\n";
                std::cout << "Using: ./opendata_search.out -geosearch xx.xxxx,yy.yyyy,radius(in meters)\n";
            }
            else {
                try {
                    args.coordinates = Point(std::stod(coordsWithRadius[0]),
                                             std::stod(coordsWithRadius[1]));  
                args.radius = std::stod(coordsWithRadius[2]);
                }
                catch (std::exception& ia) {
                    args.geosearch = false;
                    std::cout << "Cannot recognize coordinates or radius!\n";
                    std::cout << "Using: ./opendata_search.out"; 
                    std::cout << "-geosearch xx.xxxx,yy.yyyy,radius(in meters)\n";
                }
            }
        }
        if ((arg == "-limit") && !args.complexsearch) {
            args.limit = atoi(argv[++i]);
            if (args.limit < 0) {
                args.limit = 0;
                std::cout << "Cannot recognize limit.\n";
                std::cout << "Using: ./opendata_search.out -limit <integer value of limit>\n";
                std::cout << "!App will now work without limit, use system shortcuts to stop it!\n";
            }
        }
        if (arg == "-complexsearch") {
            args.complexsearch = true;
            args.search = false;
            args.limit = 0;
            args.toFind = (std::string) argv[++i];
        }
    }
    //Now we are moving to the main logic:
    if (args.Filename == NO_FILE_NAME) {
        args.Filename = MUSEUMS;
        FunctionChoice(args);
        args.Filename = SIGHTS;
        FunctionChoice(args);
    }
    else {
        FunctionChoice(args);
    }
    return 0;
}
