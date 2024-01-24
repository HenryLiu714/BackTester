#ifndef EVENT_H
#define EVENT_H 

#include <string>

#include "datetime.h"

enum Direction {LONG, SHORT, EXIT};
enum Order {MKT, LMT}; // Market or limit order

/**
 * Abstract base class for events
*/
class Event {
    public:
        std::string type;
        Datetime* datetime;

        // Constructor
        Event();
        Event(std::string type_, Datetime* datetime_);
        Event(std::string type_, std::string datetime_);
};

/**
 * MarketEvent objects are at each 'heartbeat' of the backtester,
 * effectively notifying the Strategy to generate Signal for
 * that iteration
*/
class MarketEvent : public Event {
    public:
        /**
         * MarketEvent constructor
         * 
         * @param  datetime_ : Datetime of the MarketEvent
         */
        MarketEvent(Datetime* datetime_);
};

/**
 * SignalEvent objects are created by the Strategy
 * from market data, contains a strategy ID, ticker, timestamp,
 * direction, and strength
*/
class SignalEvent : public Event {
    public:
        std::string id;
        std::string ticker;
        int direction;
        int strength;

        /**
         * SignalEvent constructor
         * 
         * @param  id_        : Symbol ID in case of use with SQL database
         * @param  ticker_    : Ticker symbol of the security
         * @param  timestamp_ : Datetime pointer of time signal was generated
         * @param  direction_ : Direction of signal, either LONG, SHORT, EXIT (0, 1, 2)
         * @param  strength_  : Strength of signal
         */
        SignalEvent(std::string id_, std::string ticker_, Datetime* timestamp_, int direction_, int strength_);
};

class OrderEvent : public Event {
    public:
        std::string symbol;
        bool order_type;
        int quantity;
        bool direction;
        
        /**
         * OrderEvent constructor
         * 
         * @param  symbol_     : Ticker symbol of the security
         * @param  order_type_ : Type of order, either MKT or LMT (0, 1)
         * @param  quantity_   : Quantity of security being ordered
         * @param  timestamp   : Datetime of the transaction
         * @param  direction_  : Direction of order, LONG or SHORT (0, 1) 
         */
        OrderEvent(std::string symbol_, bool order_type_, int quantity_, Datetime* timestamp, bool direction_);
        
        /**
         * Prints a string representation of the order to the terminal
         */
        void print_order();
};

class FillEvent : public Event {
    public:
        std::string symbol;
        int quantity;
        bool direction;
        double fill_cost;
        double commission;
        
        /**
         * FillEvent constructor
         * 
         * @param  symbol_     : Symbol being filled
         * @param  quantity_   : Quantity of security being filled
         * @param  direction_  : Direction of fill, either LONG or SHORT
         * @param  fill_cost_  : Cost of fill
         * @param  datetime_   : Datetime of transaction
         * @param  commission_ : Fill commission in percent of total fill cost
         */
        FillEvent(std::string symbol_, int quantity_, bool direction_, double fill_cost_, Datetime* datetime_, double commission_);
};

#endif
