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
    string name;
    string address;
    string description;
    string histRef;
    public:
        CulturalObject (unsigned id_, double lat_, double long_, string name_);
        double getLatitude() const;
        double getLongitude() const;
        string getName() const;
        string getAddress() const;
        string getDescription() const;
        string getHistRef() const;
        void setAddress(string addr);
        void setDescription(string dscr);
        void setHistRef(string hstrf);
};
