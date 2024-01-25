#ifndef STRATEGY_H
#define STRATEGY_H

#include "event.h"
#include "datahandler.h"

class Strategy {
    public:
        /**
         *  Should provide all necessary mechanisms for calculating signals
         */
        virtual SignalEvent* calculate_signals(DataHandler* bars) = 0;
};

/**
 * Sample strategy class for tests
*/
class SampleStrategy : public Strategy {
    public:
        /**
         * Sample strategy for use in tests
         * @return {SignalEvent*}  : SignalEvent pointer indicating to buy or sell securities
         */
        SignalEvent* calculate_signals(DataHandler* bars);
};

/**
 * Basic crossover strategy with two moving averages
*/
class MovingAverageCrossover : public Strategy {
    private:
        int n1;
        int n2;
        bool over;
    public:
        /**
         * MovingAverageCrossover 
         * 
         * @param  n1 : First period
         * @param  n2 : Second period (typically longer than first)
         */
        MovingAverageCrossover(int n1_, int n2_);
        
        /**
         * Calculate signals with the given moving crossover periods,
         * where if the moving average of the past n1 crosses over the moving average
         * of past n2, then buy, or if crosses under than sell
         * @param  bars            : DataHandler object providing bar data
         * @return {SignalEvent*}  : Corresponding signal to buy or sell or NULL
         */
        SignalEvent* calculate_signals(DataHandler* bars);
};

#endif

