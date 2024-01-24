#include "strategy.h"

#include <stdlib.h>
#include <iostream>
#include <time.h>

SignalEvent* SampleStrategy::calculate_signals() {
    srand(time(NULL));
    int i = rand() % 2;

    if (i == 1) {
        return new SignalEvent("TSLA", "TSLA", new Datetime("10-10-2020"), LONG, 0);
    }

    else {
        return new SignalEvent("TSLA", "TSLA", new Datetime("10-10-2020"), EXIT, 0);
    }
}