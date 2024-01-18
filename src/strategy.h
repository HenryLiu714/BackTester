#ifndef STRATEGY_H
#define STRATEGY_H

class Strategy {
    
    /**
     *  Should provide all necessary mechanisms for calculating signals
     */
    virtual void calculate_signals();
};

#endif