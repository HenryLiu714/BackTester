#ifndef EXECUTIONHANDLER_H
#define EXECUTIONHANDLER_H

#include <deque>

#include "event.h"

class ExecutionHandler {
    public:
        virtual void execute_order(Event* e) = 0;
};

class SimulationExecutionHandler : public ExecutionHandler {
    public:
        std::deque<Event*>* events;

        SimulationExecutionHandler(std::deque<Event*>* events_);
        void execute_order(Event* e);
};

#endif