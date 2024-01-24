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
    double initial_capital;
    int heartbeat;
    int max_trading_periods;

    int signals;
    int orders;

    public:
        /**
         * Constructor for Backtest object
         * 
         * @param  symbols_list_        : List of all symbols used
         * @param  portfolio_           : Portfolio object
         * @param  start_date_          : Starting date for trading
         * @param  data_handler_        : Pointer to DataHandler object
         * @param  execution_handler_   : Pointer to Executionhandler object
         * @param  strategy_            : Pointer to Strategy object
         * @param  initial_capital_     : Starting capital for backtest, default 100,000
         * @param  heartbeat_           : Length of heartbeat (i.e. one trading period) in milliseconds
         * @param  max_trading_periods_ : Maximum number of trading periods 
         */
        Backtest(
            const std::vector<std::string>& symbols_list_, Portfolio* portfolio_,
            Datetime* start_date_, DataHandler* data_handler_, ExecutionHandler* execution_handler_,
            Strategy* strategy_, double initial_capital_ = 100000, int heartbeat_ = 0, int max_trading_periods_ = 1000
        );

        /**
         * Constructor for Backtest object using the historical data folder and default ExecutionHandler
         * 
         * @param  symbols_list_        : List of all symbols used
         * @param  start_date_          : Starting date for trading
         * @param  strategy_            : Pointer to Strategy object
         * @param  initial_capital_     : Starting capital for backtest, default 100,000
         * @param  heartbeat_           : Length of heartbeat (i.e. one trading period) in milliseconds
         * @param  max_trading_periods_ : Maximum number of trading periods 
         */
        Backtest(const std::string& symbol, Datetime* start_date_,
            Strategy* strategy_, double initial_capital_ = 100000, int heartbeat_ = 1000, int max_trading_periods_ = 1000,
            const std::string& csv_path = "./historical_data");
        
        /**
         * Function to run the backtest
         */
        void run_backtest();
        
        /**
         * Outputs the performance of the backtest 
         */
        void output_performance();
        
        /**
         * Calls the previous two functions to run backtest, then output performance analytics
         */
        void simulate_trading();
};

#endif