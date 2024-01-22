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

        std::unordered_map<std::string, int> positions;
        std::unordered_map<std::string, double> holdings;

        Portfolio(DataHandler* bars_, std::deque<Event*>* events_, Datetime* start_date_, double initial_capital_=100000);

        void update_time_index();

        void update_fill(Event* e);

        void update_signal(Event* e);

        void print_holdings();
};

#endif