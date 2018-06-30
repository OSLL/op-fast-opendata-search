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
    
public:
    /*
     * This constructor receive first left and last right coordinates
     * with desired size of each square, then construct 
     * 2d-vector, in which each value is square. Each value is vector of
     * pointers to CulturalObjects, which situated in this square
     */
    GeoSquares(Point leftUpper, Point rightLower, double size) : 
    firstCoordinate(leftUpper), lastCoordinate(rightLower), squareSize(size) {
        //std::cout << "Inside constructor\n";//debug
        double width = leftUpper.getDistance(Point(rightLower.getLatitude(), leftUpper.getLongitude()));
        double height = leftUpper.getDistance(Point(leftUpper.getLatitude(), rightLower.getLongitude()));
        int widthNumber = (int)((width/size) + 0.99);//we need one more square to fill all the city
        int heightNumber = (int)((height/size) + 0.99);//we need one more square to fill all the city
        //std::cout << "ширина: "<< width << " height: " << height << " wN " << widthNumber << " hN " << heightNumber;//debug
        squares.resize(heightNumber);//set the width of geosquare
        //std::cout << '\n'<< squares.size() << '\n';//debug
        for (unsigned i = 0; i < heightNumber; i++) {
            squares.at(i).resize(widthNumber);//set the height of geosquare
        }
        /*std::cout << "Test of correct behavior in constructor of GeoSquare:";//debug
        std::cout << "\nWidth = " << width << ", width Number = " << widthNumber;//debug
        std::cout << "\nHeigth = " << height << ", number = " << heightNumber << '\n';//debug*/
    }
    
    /*
     * After constructing object must be filled with CulturalObjects,
     * but because Saint Petersburg located in North hemisphere, objects
     * will be filled from lower left coordinate to upper left and from 
     * left coordinate to right.
     */
    
    std::vector<CulturalObject *> & returnSquare(Point findInWhichSquare) {
        if (findInWhichSquare.getLatitude() > firstCoordinate.getLatitude() ||
                findInWhichSquare.getLatitude() < lastCoordinate.getLatitude() ||
                findInWhichSquare.getLongitude() < firstCoordinate.getLongitude() ||
                findInWhichSquare.getLongitude() > lastCoordinate.getLongitude() ) {
            throw 1;
        }
        //find quadrante by the latitude:
        double widthDistance = findInWhichSquare.getDistance(Point(firstCoordinate.getLatitude(),
                            findInWhichSquare.getLongitude()));
        int whichWidth = (int) (widthDistance / squareSize + 0.99) - 1;
        
        //find quadrante by the longitude:
        double heightDistance = findInWhichSquare.getDistance(Point(findInWhichSquare.getLatitude(),
                            firstCoordinate.getLongitude()));
        int whichHeigth = (int) (heightDistance / squareSize + 0.99) - 1;
        return squares.at(whichHeigth).at(whichWidth);
    }
    
    /*
     * Sullpier function for arithmetic search
     * in which quadrante Point is situated.
     * Return vector with 2 values - first is latitude
     * and second is longitude.  
     */
    
    std::vector<int> findSquare(Point findInWhichSquare) {
        //find quadrante by the latitude:
        double widthDistance = findInWhichSquare.getDistance(Point(firstCoordinate.getLatitude(),
                            findInWhichSquare.getLongitude()));
        int whichWidth = (int) (widthDistance / squareSize + 0.99) - 1;
        
        //find quadrante by the longitude:
        double heightDistance = findInWhichSquare.getDistance(Point(findInWhichSquare.getLatitude(),
                            firstCoordinate.getLongitude()));
        int whichHeigth = (int) (heightDistance / squareSize + 0.99) - 1;
        std::vector<int> result;
        if (whichHeigth < 0 || whichHeigth > squares.size() || whichWidth < 0 || whichWidth > squares.size()){
            throw 1;

        }
        result.push_back(whichHeigth);//add latitude to vector
        result.push_back(whichWidth);//add longitude to vector
        return result;
    }
    /*
     * this function receive Point center 
     * returns redunant vector of squares
     * in certain 
     */
    
    std::vector<std::vector<CulturalObject *>> returnSquares(Point center, double radius) {
        std::vector<std::vector<CulturalObject *>> result;
        //find indexes for central quadrante:
        int widthPosition = 0;
        int heigthPosition = 0;
        try{
            std::vector<int> find = this->findSquare(center);
            if (find.size() == 2) {//check if vector contains exactly 2 values
                heigthPosition = find.at(0);
                widthPosition = find.at(1);
            }
        }
        catch (int a) {
            std::cout << "You give wrong coordinates: " << center.getLatitude() << ' ';
            std::cout << center.getLongitude() << '\n';
            return result;
        }
        int offset = (int) (radius / squareSize + 0.99);
        int hghtIter = 0;
        int wdthIter = 0;
        for ((offset > heigthPosition)? hghtIter = 0 : hghtIter = (heigthPosition - offset);
                hghtIter <= (heigthPosition + offset) && hghtIter < squares.size(); hghtIter++) {
            for ((offset > widthPosition)? wdthIter = 0 : wdthIter = (widthPosition - offset);
                    wdthIter <= (widthPosition + offset) && wdthIter < squares.at(hghtIter).size(); wdthIter++) {
                result.push_back(squares.at(hghtIter).at(wdthIter));
            }
        }
        //return vector of squares which are in the radius
        return result;
    }
};