#pragma once
#include "culturalobject.h"
#include <vector>
#include <iostream> //debug
/*
░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░
░░██████████████████████████░░
░░██░░░░░░██░░░░░░██░░░░░░██░░
░░██░░10░░██░░11░░██░░12░░██░░
░░██░░░░░░██░░░░░░██░░░░░░██░░
░░██████████████████████████░░
░░██░░░░░░██░░░░░░██░░░░░░██░░
░░██░░00░░██░░01░░██░░02░░██░░
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
 * 
 * PLEASE PAY ATTENTION!
 * This class is specified for CUlturalObjects which are situated
 * in the Northwestern hemisphere!
 */
class GeoSquares {
    std::vector<std::vector<std::vector<CulturalObject *>>> squares;
    Point firstCoordinate;
    Point lastCoordinate;
    double squareSize;
    //std::vector<CulturalObject *> outOfRange;
    
public:
    /*
     * This constructor receive first left and last right coordinates
     * with desired size of each square, then construct 
     * 2d-vector, in which each value is square. Each value is vector of
     * pointers to CulturalObjects, which situated in this square
     */
    GeoSquares(Point leftUpper, Point rightLower, double size) : 
    firstCoordinate(leftUpper), lastCoordinate(rightLower), squareSize(size) {
        std::cout << "Inside constructor\n";//debug
        double width = leftUpper.getDistance(Point(rightLower.getLatitude(), leftUpper.getLongitude()));
        double height = leftUpper.getDistance(Point(leftUpper.getLatitude(), rightLower.getLongitude()));
        int widthNumber = (int)((width/size) + 0.99);//we need one more square to fill all the city
        int heightNumber = (int)((height/size) + 0.99);//we need one more square to fill all the city
        std::cout << "ширина: "<< width << " height: " << height << " wN " << widthNumber << " hN " << heightNumber;//debug
        squares.resize(widthNumber);//set the width of geosquare
        std::cout << '\n'<< squares.size() << '\n';//debug
        for (unsigned i = 0; i < widthNumber; i++) {
            squares.at(i).resize(heightNumber);//set the height of geosquare
        }
        std::cout << "Test of correct behavior in constructor of GeoSquare:";//debug
        std::cout << "\nWidth = " << width << ", width Number = " << widthNumber;//debug
        std::cout << "\nHeigth = " << height << ", number = " << heightNumber << '\n';//debug
    }
    
    /*
     * After constructing object must be filled with CulturalObjects,
     * but because Saint Petersburg located in North hemisphere, objects
     * will be filled from lower left coordinate to upper left and from 
     * left coordinate to right.
     */
    
    std::vector<CulturalObject *> & returnSquare(Point findInWhichSquare) {
        /*if (findInWhichSquare.getLatitude() > firstCoordinate.getLatitude() ||
                findInWhichSquare.getLatitude() < lastCoordinate.getLatitude() ||
                findInWhichSquare.getLongitude() < firstCoordinate.getLongitude() ||
                findInWhichSquare.getLongitude() > lastCoordinate.getLongitude() ) {
            return outOfRange;
        }*/
        //find quadrante by the latitude:
        double widthDistance = findInWhichSquare.getDistance(Point(firstCoordinate.getLatitude(),
                            findInWhichSquare.getLongitude()));
        int whichWidth = (int) (widthDistance / squareSize + 0.99) - 1;
        
        //find quadrante by the longitude:
        double heightDistance = findInWhichSquare.getDistance(Point(findInWhichSquare.getLatitude(),
                            firstCoordinate.getLongitude()));
        int whichHeigth = (int) (heightDistance / squareSize + 0.99) - 1;
        std::cout << "Finded object in the: " << whichWidth << " " << whichHeigth << '\n';//debug
        
        return squares.at(whichWidth).at(whichHeigth);
    }
    /*
     * this function returns redunant vector of squares
     */
    
    std::vector<std::vector<CulturalObject *>> returnSquares(Point center, double radius) {
        std::vector<std::vector<CulturalObject *>> toReturn;
        std::vector<CulturalObject *> central = this->returnSquare(center);
        toReturn.push_back(central);
        //add indexes for central quadrante:
        int WidthPosition = 0;
        int HeigthPosition = 0;
        //find indexes of central quadrante:
        for (unsigned i = 0; i < squares.size(); i++){
            for (unsigned j = 0; j < squares.at(i).size(); j++) {
                if (squares.at(i).at(j) == central) {
                    WidthPosition = j;
                    HeigthPosition = i;
                }
            }
        }
        
        //return vector of squares which are in the radius
        return toReturn;
    }
};