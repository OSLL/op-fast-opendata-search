#pragma once
#include <string>

class Point {
    double latitude;
    double longitude;
    public:
        Point(double lat_ = 0.0, double long_ = 0.0) : latitude(lat_), longitude (long_) {}
        double getLatitude() const {return latitude;}
        double getLongitude() const {return longitude;}
};

class CulturalObject {
    unsigned id;
    Point coordinates;
    std::string name;
    std::string address;
    std::string description;
    std::string histRef;
    public:
        CulturalObject (unsigned id_, double lat_, double long_, std::string name_) : 
            name(name_), id(id_) {
                coordinates = Point(lat_, long_);
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
        void setAddress(std::string addr) {address = addr;}
        void setDescription(std::string dscr) {description = dscr;}
        void setHistRef(std::string hstrf) {histRef = hstrf;}
};
