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

MovingAverageCrossover::MovingAverageCrossover(int n1_, int n2_, std::string symbol_) {
    n1 = n1_;
    n2 = n2_;
    symbol = symbol_;
    over = 0;
}

SignalEvent* MovingAverageCrossover::calculate_signals(DataHandler* bars) {
    double avg1 = arithmetic_mean(bars->get_latest_bar_vals(symbol, "ADJ", n1));
    double avg2 = arithmetic_mean(bars->get_latest_bar_vals(symbol, "ADJ", n2));

    if (bars->get_latest_bar_vals(symbol, "ADJ", n1).size() < n1 || bars->get_latest_bar_vals(symbol, "ADJ", n2).size() < n2) {
        return NULL;
    }

    if (over && (avg1 < avg2)) {
        over = 0;
        return new SignalEvent(symbol, symbol, bars->get_latest_datetime(symbol), EXIT, 1);
    }

    else if (!over && (avg1 > avg2)) {
        over = 1;
        return new SignalEvent(symbol, symbol, bars->get_latest_datetime(symbol), LONG, 1);
    }

    return NULL;
}