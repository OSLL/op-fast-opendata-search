#pragma once
#include "culturalobject.h"
#include <vector>
#include <iostream> //debug
/*
░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░
░░██████████████████████████░░
░░██░░░░░░██░░░░░░██░░░░░░██░░
░░██░░00░░██░░01░░██░░02░░██░░
░░██░░░░░░██░░░░░░██░░░░░░██░░
░░██████████████████████████░░
░░██░░░░░░██░░░░░░██░░░░░░██░░
░░██░░10░░██░░11░░██░░12░░██░░
░░██░░░░░░██░░░░░░██░░░░░░██░░
░░██████████████████████████░░
░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░
 * This is a class to represent city territorry as a square(rectangle)
 * which consist of squares with same size sides.
 * <----Width----> of this rectangle match to longitude coordinates,
 * and the
 *  / \
 *   |
 *   |
 * Height
 *   |
 *   |
 *  \ /
 * match to latitude coordinates.
 * As representation is 2d-vector so each square 
 */
class GeoSquares {
    std::vector<std::vector<std::vector<CulturalObject *>>> squares;
    Point firstCoordinate;
    Point lastCoordinate;
    double squareSize;
public:
    /*
     * This constructor receive first left and last right coordinates
     * with desired size of each square, then construct 
     * 2d-vector, in which each value is square. Each value is vector of
     * pointers to CulturalObjects, which situated in this square
     */
    GeoSquares(Point leftUpper, Point rightLower, double size) : 
    firstCoordinate(leftUpper), lastCoordinate(rightLower), squareSize(size) {
        double width = leftUpper.getDistance(Point(rightLower.getLatitude(), leftUpper.getLongitude()));
        double height = leftUpper.getDistance(Point(leftUpper.getLatitude(), rightLower.getLongitude()));
        int widthNumber = (int)((width/size) + 0.99);//we need one more square to fill all the city
        int heightNumber = (int)((height/size) + 0.99);//we need one more square to fill all the city
        squares.reserve(widthNumber);//set the width of geosquare
        for (unsigned i = 0; i < heightNumber; i++) {
            squares.at(i).reserve(heightNumber);//set the height of geosquare
        }
        std::cout << "Test of correct behavior in constructor of GeoSquare:";//debug
        std::cout << "\nWidth = " << width << ", width Number = " << widthNumber;//debug
        std::cout << "heigth = " << height << ", number = " << heightNumber << '\n';//debug
    }
    std::vector<CulturalObject *> returnSquare(Point findInWhichSquare) {
        //if not in range return null else count right square and return it
        //calling function may fill vector with objects
    }
    std::vector<std::vector<CulturalObject *>> returnSquares(Point center, double radius) {
        //return vector of squares which are in the radius
    }
};