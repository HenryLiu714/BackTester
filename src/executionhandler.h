#ifndef EXECUTIONHANDLER_H
#define EXECUTIONHANDLER_H

#include <deque>

#include "event.h"

/**
 * Abstract base class for ExecutionHandler objects
*/
class ExecutionHandler {
    public:
        virtual void execute_order(Event* e) = 0;
};

/**
 * SimulationExecutionHandler in which all OrderEvents are filled at the same price with no commission
*/
class SimulationExecutionHandler : public ExecutionHandler {
    public:
        std::deque<Event*>* events;
        
        /**
         * SimulationExecutionHandler constructor
         * 
         * @param events_ : Event queue to add FillEvent into
         */
        SimulationExecutionHandler(std::deque<Event*>* events_);
        
        /**
         * Executes an OrderEvent by adding the corresponding FillEvent
         * @param  e : Event being filled, should be OrderEvent*
         */
        void execute_order(Event* e);
};

#endif