#ifndef BACKTEST_H
#define BACKTEST_H

#include <string>
#include <vector>
#include <deque>

#include "executionhandler.h"
#include "datahandler.h"
#include "datetime.h"
#include "portfolio.h"
#include "strategy.h"

class Backtest {
    std::vector<std::string> symbols_list;
    Portfolio* portfolio;
    Strategy* strategy;
    Datetime* datetime;
    DataHandler* data_handler;
    ExecutionHandler* execution_handler;
    int heartbeat;

    int signals;
    int orders;

    public:
        Backtest(
            const std::vector<std::string>& symbols_list_, Portfolio* portfolio_,
            Datetime* start_date_, DataHandler* data_handler_, ExecutionHandler* execution_handler_,
            Strategy* strategy_, double initial_capital = 100000, int heartbeat_ = 0
        );

        Backtest(const std::string& symbol, Datetime* start_date_,
            Strategy* strategy_, double initial_capital = 100000, int heartbeat_ = 1000,
            const std::string& csv_path = "./historical_data");

        void run_backtest();

        void output_performance();

        void simulate_trading();
};

#endif