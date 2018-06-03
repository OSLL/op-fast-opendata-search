#include <string>
#define string std::string

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
    string name;
    string address;
    string description;
    string histRef;
    public:
        CulturalObject (unsigned id_, double lat_, double long_, string name_) : 
            name(name_), id(id_) {
                coordinates = Point(lat_, long_);
                address = "";
                description = "";
                histRef = "";
            }
        double getLatitude() const {return coordinates.getLatitude();}
        double getLongitude() const {return coordinates.getLongitude();}
        string getName() const {return name;}
        string getAddress() const {return address;}
        string getDescription() const {return description;}
        string getHistRef() const {return histRef;}
        void setAddress(string addr) {address = addr;}
        void setDescription(string dscr) {description = dscr;}
        void setHistRef(string hstrf) {histRef = hstrf;}
};
