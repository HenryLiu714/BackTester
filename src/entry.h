#ifndef ENTRY_H
#define ENTRY_H

#include <string>

#include "datetime.h"

class Entry {
    public:
        std::string symbol;
        Datetime* date;

        double open_price;
        double high_price;
        double low_price;
        double close_price;
        double adj_close_price;

        long volume;

        Entry(std::string symbol_id_, Datetime* date_, double open, double high, double low, double close, double adj, long volume_);

        std::string to_string();
};

#endif