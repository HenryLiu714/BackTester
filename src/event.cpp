#include <string>
#include <vector>
#include <iostream>

#include "datetime.h"
#include "event.h"

Event::Event() {
    type = "";
    datetime = new Datetime();
}

Event::Event(std::string type_, Datetime* datetime_) {
    type = type_;
    datetime = datetime_;
}

Event::Event(std::string type_, std::string datetime_) {
    type = type_;
    datetime = new Datetime(datetime_);
}

MarketEvent::MarketEvent(Datetime* datetime_) {
    type = "MARKET";
    datetime = datetime_;
}

SignalEvent::SignalEvent(std::string id_, std::string ticker_, Datetime* timestamp_, bool direction_, int strength_) {
    type = "SIGNAL";
    id = id_;
    ticker = ticker_;
    datetime = timestamp_;
    direction = direction_;
    strength = strength_;
}

OrderEvent::OrderEvent(std::string symbol_, bool order_type_, int quantity_, Datetime* timestamp, bool direction_) {
    type = "ORDER";
    symbol = symbol_;
    datetime = timestamp,
    order_type = order_type_;
    quantity = quantity_;
    direction = direction_;
}

void OrderEvent::print_order() {
    std::cout << "Order: Symbol=" << symbol << ", Type=" << order_type
    << ", Quantity=" << quantity << ", Direction=" << direction << ", Time=" << datetime->to_string(); 
}

FillEvent::FillEvent(std::string symbol_, int quantity_, bool direction_, double fill_cost_, Datetime* datetime_, double commission_=0) {
    type = "FILL";
    symbol = symbol_;
    datetime = datetime_;
    quantity = quantity_;
    direction = direction_;
    fill_cost = fill_cost_;
    commission = commission_;
}