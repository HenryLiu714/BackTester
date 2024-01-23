#ifndef STRATEGY_H
#define STRATEGY_H

#include "event.h"

class Strategy {
    public:
        /**
         *  Should provide all necessary mechanisms for calculating signals
         */
        virtual SignalEvent* calculate_signals() = 0;
};

class SampleStrategy : public Strategy {
    SignalEvent* calculate_signals();
};
#endif