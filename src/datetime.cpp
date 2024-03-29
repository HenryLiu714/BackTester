#include "datetime.h"

#include <string>

Datetime::Datetime() {
    hr = 0;
    min = 0;
    sec = 0;
    day = 1;
    month = 1;
    year = 1000;
}

Datetime::Datetime(int day_, int month_, int year_) {
    hr = 0;
    min = 0;
    sec = 0;
    day = day_;
    month = month_;
    year = year_;
}

Datetime::Datetime(int sec_, int min_, int hr_, int day_, int month_, int year_) {
    hr = hr_;
    min = min_;
    sec = sec_;
    day = day_;
    month = month_;
    year = year_;
}

/**
 * @param date Date in standard format YYYY-MM-DD hh:mm:ss, with hms optional
*/
Datetime::Datetime(const std::string& date) {
    year = stoi(date.substr(0, 4));
    month = stoi(date.substr(5, 2));
    day = stoi(date.substr(8, 2));

    if (date.size() <= 11) {
        hr = 0;
        min = 0;
        sec = 0;
    }

    else {
        hr = stoi(date.substr(11, 2));
        min = stoi(date.substr(14, 2));
        sec = stoi(date.substr(17, 2));
    }
}

std::string Datetime::to_string() {
    return std::to_string(year) + "-" + 
    std::to_string(month) + "-" +
    std::to_string(day) + " " +
    std::to_string(hr) + ":" +
    std::to_string(min) + ":" +
    std::to_string(sec);
}

std::string Datetime::to_string_day() {
    if (month < 10 && day > 9) {
        return std::to_string(year) + "-0" + 
        std::to_string(month) + "-" +
        std::to_string(day);
    }

    else if (month > 9 && day < 10) {
        return std::to_string(year) + "-" + 
        std::to_string(month) + "-0" +
        std::to_string(day);
    }

    else if (month < 10 && day < 10) {
        return std::to_string(year) + "-0" + 
        std::to_string(month) + "-0" +
        std::to_string(day);
    }
    return std::to_string(year) + "-" + 
    std::to_string(month) + "-" +
    std::to_string(day);
}

bool Datetime::is_after(Datetime* d) {
    if (year > d->year) return 1;
    if (year < d->year) return 0;
    if (month > d->month) return 1;
    if (month < d->month) return 0;
    if (day > d->day) return 1;
    if (day < d->day) return 0;
    if (hr > d->hr) return 1;
    if (hr < d->hr) return 0;
    if (min > d->min) return 1;
    if (min < d->min) return 0;
    if (sec > d->sec) return 1;
    if (sec < d->sec) return 0;
    return 0;
}