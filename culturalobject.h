#pragma once

class Point {
    double latitude;
    double longitude;
    public:
        Point(double lat_, double long_);
        double getLatitude() const;
        double getLongitude() const;
};

class CulturalObject {
    unsigned id;
    Point coordinates;
    std::string name;
    std::string address;
    std::string description;
    std::string histRef;
    public:
        CulturalObject (unsigned id_, double lat_, double long_, std::string name_);
        double getLatitude() const;
        double getLongitude() const;
        std::string getName() const;
        std::string getAddress() const;
        std::string getDescription() const;
        std::string getHistRef() const;
        void setAddress(std::string addr);
        void setDescription(std::string dscr);
        void setHistRef(std::string hstrf);
};
