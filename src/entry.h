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
        
        /**
         * Constructor for the Entry class
         * 
         * @param  symbol_id_ : Ticker symbol of the entry
         * @param  date_      : Date of the prices
         * @param  open       : Open price
         * @param  high       : High price
         * @param  low        : Low price
         * @param  close      : Closing price
         * @param  adj        : Adjusted closing price
         * @param  volume_    : Volume traded
         */
        Entry(std::string symbol_id_, Datetime* date_, double open, double high, double low, double close, double adj, long volume_);
        
        /**
         * String representation of Entry object
         * @return {std::string}  : String representation of Entry object
         */
        std::string to_string();
};

#endif