#include "executionhandler.h"

#include <iostream>

SimulationExecutionHandler::SimulationExecutionHandler(std::deque<Event*>* events_, double commission_) {
    events = events_;
    commission = commission_;
}

void SimulationExecutionHandler::execute_order(Event* e) {
    if (e->type == "ORDER") {
        OrderEvent* o = (OrderEvent*) e;
        FillEvent* f = new FillEvent(o->symbol, o->quantity, o->direction, 0, o->datetime, commission);
        events->push_back(f);
    }
}