#ifndef DATETIME_h
#define DATETIME_h

#include <string>

class Datetime {
    public:
        int hr;
        int min;
        int sec;
        int day;
        int month;
        int year;

        Datetime();
        Datetime(int day_, int month_, int year_);
        Datetime(int sec_, int min_, int hr_, int day_, int month_, int year_);
        Datetime(const std::string& date);
        
        std::string to_string();
};

#endif