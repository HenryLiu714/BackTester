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

/**
 * Sample strategy class for tests
*/
class SampleStrategy : public Strategy {
    /**
     * Sample strategy for use in tests
     * @return {SignalEvent*}  : SignalEvent pointer indicating to buy or sell securities
     */
    SignalEvent* calculate_signals();
};
#endif