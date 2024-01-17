#ifndef EVENT_H
#define EVENT_H 

#include <string>

#include "datetime.h"

enum Direction {LONG, SHORT};
enum Order {MKT, LMT}; // Market or limit order

class Event {
    public:
        std::string type;
        Datetime datetime;

        // Constructor
        Event();
        Event(std::string type_, Datetime datetime_);
        Event(std::string type_, std::string datetime_);
};

/**
 * MarketEvent objects are at each 'heartbeat' of the backtester,
 * effectively notifying the Strategy to generate Signal for
 * that iteration
*/
class MarketEvent : public Event {
    public:
        // Constructor
        MarketEvent(Datetime datetime_);
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
        bool direction;
        int strength;

        // Constructor
        SignalEvent(std::string id_, std::string ticker_, Datetime timestamp_, bool direction_, int strength_);
};

class OrderEvent : public Event {
    public:
        std::string symbol;
        bool order_type;
        int quantity;
        bool direction;

        OrderEvent(std::string symbol_, bool order_type_, int quantity_, Datetime timestamp, bool direction_);
        void print_order();
};

class FillEvent : public Event {
    public:
        std::string symbol;
        int quantity;
        bool direction;
        double fill_cost;
        double commission;

        FillEvent(std::string symbol_, int quantity_, bool direction_, double fill_cost_, Datetime datetime_, double commission_);
};

#endif
