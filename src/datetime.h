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
        
        /**
         * Default DateTime constructor, sets everything to 0 or 1 
         */
        Datetime();
        
        /**
         * Datetime constructor with day, month, and year, sets time to 00:00:00
         * 
         * @param  day_   : Day of DateTime
         * @param  month_ : Month of DateTime 
         * @param  year_  : Year of DateTime
         */
        Datetime(int day_, int month_, int year_);
        
        /**
         * Datetime constructor with all parameters
         * 
         * @param  sec_   : Seconds
         * @param  min_   : Minutes
         * @param  hr_    : Hours
         * @param  day_   : Days
         * @param  month_ : Months
         * @param  year_  : Years
         */
        Datetime(int sec_, int min_, int hr_, int day_, int month_, int year_);
        
        /**
         * Datetime constructor with string parameter
         * 
         * @param  date : String formatted date, formatted "YYYY-MM-DD hh:mm:ss" with hours, minutes, seconds optional
         */
        Datetime(const std::string& date);
        
        /**
         * Returns a string formatted version of the current Datetime
         * @return {std::string}  : The string
         */
        std::string to_string();
        
        /**
         * Returns a string formatted version of the current Datetime without hours, minutes, or seconds
         * @return {std::string}  : The string
         */
        std::string to_string_day();
        
        /**
         * Compares with another Datetime 
         * @param  d       : The other Datetime
         * @return {bool}  : True if after, false if not
         */
        bool is_after(Datetime* d);
};

#endif