#include <iostream>
#include <string>
#include "culturalobject.h"
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
             std::cout << "Object #" << (i + 1) << "without coordinates! Name = ";
             std::cout << objects[i].getName() << std::endl;
         }
         else if (double distance = objects[i].getPoint().getDistance(location) <= radius) {
             std::cout << "Object id #" << objects[i].getId() << " near.\nName = ";
             std::cout << objects[i].getName() << "\nAddress is: " << objects[i].getAddress();
             //std::cout << ",\nlongitude = " << objects[i].getLongitude();
             //std::cout << ",\nlatitude = " << objects[i].getLatitude();
             std::cout << "\nDistance to the object is ";
             std::cout << distance << " meters\n"; 
         }
     }
}
    
