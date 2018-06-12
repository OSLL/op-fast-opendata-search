#pragma once
#include <string>
#include <fstream>

/*
This is a small function which receive csv-file and counts
number of objects in it.
If received file isn't open, function returns -1.
*/

int ObjectCounter(std::ifstream & file) {
    std::string readedLine;
    int counter = 0;
    bool outline = true;
    if (!file.is_open())
        return -1;
    do {
        file.sync();
        if (file.eof()) {
            return counter;
        }
        getline(file, readedLine);
        for (int i = 0; i < readedLine.size(); i++) {
            if ((readedLine.at(i) == '\"') && outline) {
                outline = false;
                continue;
            }
            if ((readedLine.at(i) == '\"') && !outline) {
                outline = true;
                continue;
            }
        }
        if (outline)
            counter++;
    }
    while (!file.eof());
    return counter - 1;//first string isn't an object!
}
