#include "entry.h"
#include "datetime.h"

Entry::Entry(std::string symbol_id_, Datetime* date_, double open, double high, double low, double close, double adj, long volume_) {
    symbol = symbol_id_;
    date = date_;
    open_price = open;
    high_price = high;
    low_price = low;
    close_price = close;
    adj_close_price = adj;
    volume = volume_;
}

std::string Entry::to_string() {
            return "Symbol: " + symbol + "\n"
            "Datetime: " + date->to_string() + "\n"
            "Open: " + std::to_string(open_price) +  "\n"
            "High: " + std::to_string(high_price) +  "\n"
            "Low: " + std::to_string(low_price) +  "\n"
            "Close: " + std::to_string(close_price) +  "\n"
            "Adjusted Price: " + std::to_string(adj_close_price) +  "\n"
            "Volume: " + std::to_string(volume) + "\n";
        }