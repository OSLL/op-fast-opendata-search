#include <iostream>
#include <string>
#include "culturalobject.h"
#include "geosquare.h"
#include "geosearch.h"


/*
This function receive array of CulturalObjects, Point (which consist from latitude and longitude),
and radius in meters.
Function analyze coordinates of each CulturalObject and if it near to the location point, function
return it in standart output: name of object found and on the next lines address
and distance to object will be showned.
*/

void geosearch(CulturalObject objects[], unsigned size, Point location, double radius) {
     for (unsigned i = 0; i < size; i++) {
         if (!(objects[i].checkId())) {
             continue;
         }
         if (!objects[i].haveCoordinates()) {
             //std::cout << "Object #" << (i + 1) << "without coordinates! Name = ";
             //std::cout << objects[i].getName() << std::endl;
         }
         else if (objects[i].getPoint().getDistance(location) <= radius) {
             std::cout << "Object id #" << objects[i].getId() << " near.\nName = ";
             std::cout << objects[i].getName() << "\nAddress is: " << objects[i].getAddress();
             //std::cout << ",\nlongitude = " << objects[i].getLongitude();
             //std::cout << ",\nlatitude = " << objects[i].getLatitude();
             std::cout << "\nDistance to the object is ";
             std::cout << objects[i].getPoint().getDistance(location) << " meters\n"; 
         }
     }
}


void complexgeosearch(CulturalObject objects[], unsigned size, Point location, double radius) {
    //First part of this function must be in another initializing function
    //firstable we need to make map of Saint-Petersburg
    Point LeftUpper = Point(60.098284, 29.614316);//Пересечение границ Парголово(север) и Кронштадта(запад)
    Point RightLower = Point(59.712012, 30.67999);//Пушкин (юг) и Колпино (восток)
    GeoSquares SaintPetersburg = GeoSquares(LeftUpper, RightLower, 1000);//территория разбита на квадраты по 150 метров
    for (unsigned i = 0; i < size; i++) {
        if (!(objects[i].checkId())) {
            continue;
        }
        if (!objects[i].haveCoordinates()) {
            //std::cout << "Object #" << (i + 1) << "without coordinates! Name = ";
            //std::cout << objects[i].getName() << std::endl;
        }
        else {
            try {
                std::vector<CulturalObject *> & searchObject = SaintPetersburg.returnSquare(objects[i].getPoint());
                searchObject.push_back(&(objects[i]));
            }
            catch (int a) {
                //std::cout << "Object " << objects[i].getName() << ", which address is " << objects[i].getAddress();
                //std::cout << " is out of Saint-Petersburg borders!\n";
            }
        }
    }
    
    //Now when we have map of Saint-Petesburg we can receive objects that we need
    std::vector<std::vector<CulturalObject *>> whatWeNeed = SaintPetersburg.returnSquares(location, radius);
    std::cout << "going next to the search\n";//debug
    for (unsigned i = 0; i < whatWeNeed.size(); i++) {
        for (unsigned j = 0; j < whatWeNeed.at(i).size(); j++) {
            if (whatWeNeed.at(i).at(j)->getPoint().getDistance(location) <= radius) {
                std::cout << "Object id #" << whatWeNeed.at(i).at(j)->getId() << " near.\nName = ";
                std::cout << whatWeNeed.at(i).at(j)->getName() << "\nAddress is: " << whatWeNeed.at(i).at(j)->getAddress();
                std::cout << "\nDistance to the object is ";
                std::cout << whatWeNeed.at(i).at(j)->getPoint().getDistance(location) << " meters\n";
            }
        }
    }
    
}