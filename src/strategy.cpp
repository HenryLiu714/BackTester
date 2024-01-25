#include "strategy.h"
#include "helper.h"

#include <stdlib.h>
#include <vector>
#include <iostream>
#include <time.h>

SignalEvent* SampleStrategy::calculate_signals(DataHandler* bars) {
    srand(time(NULL));
    int i = rand() % 2;

    if (i == 1) {
        return new SignalEvent("TSLA", "TSLA", new Datetime("10-10-2020"), LONG, 0);
    }

    else {
        return new SignalEvent("TSLA", "TSLA", new Datetime("10-10-2020"), EXIT, 0);
    }
}

MovingAverageCrossover::MovingAverageCrossover(int n1_, int n2_) {
    n1 = n1_;
    n2 = n2_;
    over = 0;
}

SignalEvent* MovingAverageCrossover::calculate_signals(DataHandler* bars) {
    int avg1 = arithmetic_mean(bars->get_latest_bar_vals("TSLA", "ADJ", n1));
    int avg2 = arithmetic_mean(bars->get_latest_bar_vals("TSLA", "ADJ", n2));

    if (over && (avg1 < avg2)) {
        over = 0;
        return new SignalEvent("TSLA", "TSLA", bars->get_latest_datetime("TSLA"), EXIT, 1);
    }

    else if (!over && (avg1 > avg2)) {
        over = 1;
        return new SignalEvent("TSLA", "TSLA", bars->get_latest_datetime("TSLA"), LONG, 1);
    }

    return NULL;
}