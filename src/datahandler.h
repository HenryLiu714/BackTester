#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>

#include "datetime.h"
#include "entry.h"
#include "event.h"

#include <unordered_map>

class DataHandler {
    public:
        virtual Entry* get_latest_bar(std::string symbol) = 0;
        
        /**
         * Returns the last N bars of a particular symbol
        */
        virtual std::vector<Entry*> get_latest_bars(std::string symbol, int N=1) = 0;

        virtual Datetime get_latest_datetime(std::string symbol) = 0;

        /**
         * @param val - One of "OPEN", "CLOSE", "HIGH", "LOW", "ADJ"
        */
        virtual double get_latest_bar_val(std::string symbol, std::string val) = 0;

        /**
         * Returns the given val of the last N bars
        */
        virtual std::vector<double> get_latest_bar_vals(std::string symbol, std::string val, int N=1) = 0;

        /**
         * Pushes the latest bars to the bars_queue for the symbol in a 
         * tuple format (vector) of (symbol, datetime, open, high, low, close, volume)
        */
        virtual void update_bars() = 0;
};

class HistoricalCSVHandler {
    private: 
        std::unordered_map<std::string, std::ifstream> data;
        std::unordered_map<std::string, std::vector<Entry*>> entries;
        std::vector<Event> events;

    public:
        HistoricalCSVHandler(std::string symbol, std::string file_dir);
        HistoricalCSVHandler(std::vector<std::string> symbols, std::string file_dir);

        /**
         * Adds a new bar to the Handler, unless the end of csv file is reached
         * @param symbol - The symbol of the new bar being added
         * @return The entry that was just added, or NULL if no entry
        */
        Entry* add_new_bar(std::string symbol);

        Entry* get_latest_bar(std::string symbol);

        std::vector<Entry*> get_latest_bars(std::string symbol, int N=1);

        Datetime get_latest_datetime(std::string symbol);

        double get_latest_bar_val(std::string symbol, std::string val);

        std::vector<double> get_latest_bar_vals(std::string symbol, std::string val, int N=1);

        void update_bars(std::string symbol);
};

#endif