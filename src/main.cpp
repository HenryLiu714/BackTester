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
    Backtest b = Backtest("GOOG", d, s, 10000, 0, 100000, 0.000);
    b.simulate_trading();
}

int main() {
    // runTests();
    std::vector<std::string> tickers = {"TSLA", "SPY", "AAPL", "RIVN", "JPM"};
    HistoricalCSVHandler::update_data(tickers);
    
    runBacktest();
    return 0;
}