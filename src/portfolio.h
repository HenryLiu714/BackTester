#ifndef PORTFOLIO_H
#define PORTFOLIO_H

#include <vector>
#include <deque>

#include "datahandler.h"

/**
 * The portfolio management system should keep track of all positions
 * in a given portfolio, as well as generate orders of a quantity of stock
 * based on signals.
 * 
 * Improvements include risk management and position sizing tools
*/

/**
 * A portfolio object must be able to 
 * 1. Handle SignalEvent objects
 * 2. Generate OrderEvent objects
 * 3. Interpret FillEvent objects to update positions
*/
class Portfolio {
    private:
        void update_positions(FillEvent* f);
        void update_holdings(FillEvent* f);
        OrderEvent* generate_naive_order(SignalEvent* e);

    public:
        DataHandler* bars;
        std::deque<Event*>* events;
        Datetime* date;
        double value;
        double balance;

        std::unordered_map<std::string, double> positions;
        std::unordered_map<std::string, double> holdings;
        /**
         * Portfolio constructor
         * 
         * @param  bars_                   : DataHandler object 
         * @param  events_                 : Event queue to add or remove events from
         * @param  start_date_             : Starting date of the trades
         * @param  initial_capital_        : Starting capital, default 100000 
         */
        Portfolio(DataHandler* bars_, std::deque<Event*>* events_, Datetime* start_date_, double initial_capital_=100000);
        
        /**
         * Updates the time index by checking the current prices and changing portfolio balance and value
         */
        void update_time_index();
        
        /**
         * Updates the portfolio from a given FillEvent
         * @param  e : FillEvent object indicating a fill
         */
        void update_fill(Event* e);
        
        /**
         * Checks a signal and updates the portfolio correspondingly by possibly making an order
         * @param  e : SignalEvent pointer indicating a signal from a strategy
         */
        void update_signal(Event* e);
        
        /**
         * Prints the current holdings of the portfolio
         */
        void print_holdings();
        
};

#endif