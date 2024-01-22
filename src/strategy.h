#ifndef STRATEGY_H
#define STRATEGY_H

#include "event.h"

class Strategy {
    
    /**
     *  Should provide all necessary mechanisms for calculating signals
     */
    virtual SignalEvent* calculate_signals();
};

#endif