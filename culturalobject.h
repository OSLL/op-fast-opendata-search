#pragma once
#include <string>
#include <cmath>

class Point {
    double latitude;
    double longitude;
    public:
        Point(double lat_ = 0.0, double long_ = 0.0) : latitude(lat_), longitude (long_) {}
        double getLatitude() const {return latitude;}
        double getLongitude() const {return longitude;}
        double getDistance(Point other) {
            double x1 = this->latitude * M_PI / 180.0;
            double x2 = other.latitude * M_PI / 180.0;
            double y1 = this->longitude * M_PI / 180.0;
            double y2 = other.longitude * M_PI / 180.0;
            double const EarthRad = 6371302.0;//radius in meters
            double distance = EarthRad * acos(sin(x1) * sin(x2) + cos(x1) * cos(x2) * cos (y2 - y1));
            return distance;
        }
};

class CulturalObject {
    unsigned id;
    Point coordinates;
    std::string name;
    std::string address;
    std::string description;
    std::string histRef;
    public:
        CulturalObject() {}
        CulturalObject (unsigned id_, double lat_, double long_, std::string name_) : 
            name(name_), id(id_) {
                coordinates = Point(lat_, long_);
                address = "";
                description = "";
                histRef = "";
            }
        CulturalObject (unsigned id_, std::string name_) : 
            name(name_), id(id_) {
                coordinates = Point(0.0, 0.0);//this object haven't got coordinates
                address = "";
                description = "";
                histRef = "";
            }
        double getLatitude() const {return coordinates.getLatitude();}
        double getLongitude() const {return coordinates.getLongitude();}
        std::string getName() const {return name;}
        std::string getAddress() const {return address;}
        std::string getDescription() const {return description;}
        std::string getHistRef() const {return histRef;}
        Point getPoint() const {return coordinates;}
        int getId() const {return id;}
        bool checkId() const {return id;}//check object is existing or not
        bool haveCoordinates() {return (this->getLatitude() > 0)? (this->getLongitude() > 0): false;}
        void setAddress(std::string addr) {address = addr;}
        void setDescription(std::string dscr) {description = dscr;}
        void setHistRef(std::string hstrf) {histRef = hstrf;}

};
