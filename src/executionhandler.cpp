#include "executionhandler.h"

SimulationExecutionHandler::SimulationExecutionHandler(std::deque<Event*>* events_) {
    events = events;
}

void SimulationExecutionHandler::execute_order(Event* e) {
    if (e->type == "ORDER") {
        OrderEvent* o = (OrderEvent*) e;
        FillEvent* f = new FillEvent(o->symbol, o->quantity, o->direction, 0, o->datetime, 0);
        events->push_back(f);
        delete o;
    }
}