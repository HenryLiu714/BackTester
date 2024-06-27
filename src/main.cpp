#include <iostream>

#include "event.h"
#include "datetime.h"
#include "datahandler.h"
#include "performance.h"
#include "portfolio.h"
#include "strategy.h"
#include "backtest.h"
#include "tests.h"

void runTests() {
    Tests::run_tests();
}

void runBacktest() {
    MovingAverageCrossover* s = new MovingAverageCrossover(10, 20, "GOOG");
    Datetime* d = new Datetime("2004-08-19");
    Backtest b = Backtest("GOOG", d, s, 10000, 0, 2140, 0.002);
    b.simulate_trading();
}

int main() {
    // runTests();
    runBacktest();
    return 0;
}