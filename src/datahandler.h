#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>
#include <deque>

#include "datetime.h"
#include "entry.h"
#include "event.h"

#include <unordered_map>

/**
 * An abstract class meant to manage data for simulation or execution. Bars of data can be accessed for use by a 
 * Strategy or Portfolio object, and information on the data can be retrieved as well. The program also adds
 * MarketEvent objects to a provided Event queue for use by other classes.
 */
class DataHandler {
    public:
        std::vector<std::string> symbols_list;

        /**
         * Generates the latest bar of data for a given symbol
         * @param  symbol    : The symbol or key representing the data wanted
         * @return {Entry*}  : A pointer to an Entry object containing the data of the last bar added
         */
        virtual Entry* get_latest_bar(std::string symbol) = 0;
        
        /**
         * Generates the most recent bars of data for a given symbol
         * @param  symbol                 : The symbol or key representing the data wanted
         * @param  N                      : The number of entries wanted, defaults to 1
         * @return {std::vector<Entry>*}  : A vector containing the entries, with the most recent at the end
         */
        virtual std::vector<Entry*> get_latest_bars(std::string symbol, int N=1) = 0;
        
        /**
         * Generates the datetime of the most recently added data
         * @param  symbol       : The symbol that we want the latest datetime of
         * @return {Datetime*}  : The latest datetime for the given symbol
         */
        virtual Datetime* get_latest_datetime(std::string symbol) = 0;

        /**
         * Generates the latest data for a given value of a symbol
         * @param  symbol    : The symbol whose data we are looking for
         * @param  val       : One of "OPEN", "CLOSE", "HIGH", "LOW", "ADJ", "VOLUME"
         * @return {double}  : The value of the latest bar
         */
        virtual double get_latest_bar_val(std::string symbol, std::string val) = 0;
        
        /**
         * Generates the latest values in a given range
         * @param  symbol                 : The symbol of the data we are looking for  
         * @param  val                    : One of "OPEN", "CLOSE", "HIGH", "LOW", "ADJ", "VOLUME"
         * @param  N                      : The number of values we need, defaults to 1
         * @return {std::vector<double>}  : 
         */
        virtual std::vector<double> get_latest_bar_vals(std::string symbol, std::string val, int N=1) = 0;

        /**
         * Pushes the latest bars to the bars_queue for the symbol in a 
         * tuple format (vector) of (symbol, datetime, open, high, low, close, volume)
        */
        virtual void update_bars(std::string symbol) = 0;
};

class HistoricalCSVHandler : public DataHandler {
    private: 
        std::unordered_map<std::string, std::ifstream> data;
        std::unordered_map<std::string, std::vector<Entry*>> entries;
        std::deque<Event*>* events;

    public:
        bool continue_backtest;
        HistoricalCSVHandler(std::string symbol, std::string file_dir, std::deque<Event*>* events_);
        HistoricalCSVHandler(std::vector<std::string> symbols, std::string file_dir, std::deque<Event*>* events_);

        /**
         * Adds a new bar to the Handler, unless the end of csv file is reached
         * @param symbol - The symbol of the new bar being added
         * @return The entry that was just added, or NULL if no entry
        */
        Entry* add_new_bar(std::string symbol);

        /**
         * Generates the latest bar of data for a given symbol
         * @param  symbol    : The symbol or key representing the data wanted
         * @return {Entry*}  : A pointer to an Entry object containing the data of the last bar added
         */
        Entry* get_latest_bar(std::string symbol);
        /**
         * Generates the most recent bars of data for a given symbol
         * @param  symbol                 : The symbol or key representing the data wanted
         * @param  N                      : The number of entries wanted, defaults to 1
         * @return {std::vector<Entry>*}  : A vector containing the entries, with the most recent at the end
         */
        std::vector<Entry*> get_latest_bars(std::string symbol, int N=1);

        /**
         * Generates the datetime of the most recently added data
         * @param  symbol       : The symbol that we want the latest datetime of
         * @return {Datetime*}  : The latest datetime for the given symbol
         */
        Datetime* get_latest_datetime(std::string symbol);

        /**
         * Generates the latest values in a given range
         * @param  symbol                 : The symbol of the data we are looking for  
         * @param  val                    : One of "OPEN", "CLOSE", "HIGH", "LOW", "ADJ", "VOLUME"
         * @param  N                      : The number of values we need, defaults to 1
         * @return {std::vector<double>}  : 
         */
        double get_latest_bar_val(std::string symbol, std::string val);

        /**
         * Generates the latest values in a given range
         * @param  symbol                 : The symbol of the data we are looking for  
         * @param  val                    : One of "OPEN", "CLOSE", "HIGH", "LOW", "ADJ", "VOLUME"
         * @param  N                      : The number of values we need, defaults to 1
         * @return {std::vector<double>}  : 
         */
        std::vector<double> get_latest_bar_vals(std::string symbol, std::string val, int N=1);

        /**
         * Pushes the latest bars to the bars_queue for the symbol in a 
         * tuple format (vector) of (symbol, datetime, open, high, low, close, volume)
        */
        void update_bars(std::string symbol);
};

#endif