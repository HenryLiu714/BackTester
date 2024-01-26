#include "backtest.h"

#include <iostream>
#include <thread>
#include <chrono>

Backtest::Backtest(
            const std::vector<std::string>& symbols_list_, Portfolio* portfolio_,
            Datetime* start_date_, DataHandler* data_handler_, ExecutionHandler* execution_handler_,
            Strategy* strategy_, double initial_capital_, int heartbeat_, int max_trading_periods_, double commission_) {
                symbols_list = symbols_list_;
                strategy = strategy_;
                datetime = start_date_;
                data_handler = data_handler_;
                execution_handler = execution_handler_;
                heartbeat = heartbeat_;
                max_trading_periods = max_trading_periods_;
                initial_capital = initial_capital_;
                portfolio = portfolio_;
                commission = commission_;

                signals = 0;
                orders = 0;
        }

Backtest::Backtest(
            const std::string& symbol, Datetime* start_date_,
            Strategy* strategy_, double initial_capital_, int heartbeat_, int max_trading_periods_, double commission_,
            const std::string& csv_path) {
                symbols_list = {symbol};
                datetime = start_date_;
                heartbeat = heartbeat_;
                initial_capital = initial_capital_;
                max_trading_periods = max_trading_periods_;
                strategy = strategy_;
                commission = commission_;

                std::deque<Event*>* events = new std::deque<Event*>();
                
                data_handler = new HistoricalCSVHandler(symbol, csv_path, events);
                execution_handler = new SimulationExecutionHandler(events, commission);
                portfolio = new Portfolio(data_handler, events, start_date_, initial_capital);
        
                signals = 0;
                orders = 0;
        }

void Backtest::run_backtest() {
    int counter = 0;
    std::deque<Event*>* events = portfolio->events;

    for (auto s : data_handler->symbols_list) {
        data_handler->update_bars(s);
        while (datetime->is_after(data_handler->get_latest_datetime(s)))
            data_handler->update_bars(s);
    }

    while (counter < max_trading_periods && data_handler->continue_backtest) {

        while (!events->empty()) {
            Event* event = events->front();
            events->pop_front();

            if (event == NULL) {

            }

            else if (event->type == "MARKET") {
                events->push_back(strategy->calculate_signals(data_handler));
                portfolio->update_time_index();
            }

            else if (event->type == "SIGNAL") {
                signals++;
                
                portfolio->update_signal(event);
            }

            else if (event->type == "ORDER") {
                orders++;
                execution_handler->execute_order(event);
            }

            else if (event->type  == "FILL") {
                portfolio->update_fill(event);
            }
        }

        counter++;
        std::this_thread::sleep_for(std::chrono::milliseconds(heartbeat));

        for (auto s : data_handler->symbols_list) {
            data_handler->update_bars(s);
        }
    }
}

void Backtest::output_performance() {
    std::cout << "Trading Strategy Overview" << std::endl;
    std::cout << "-------------------------------" << std::endl << std::endl;
    std::cout << "Starting Balance: \t" << initial_capital << std::endl;
    std::cout << "Final Balance: \t" << portfolio->value << std::endl;
    std::cout << "Overall Performance: \t" << ((portfolio->value - initial_capital) / initial_capital) * 100 << "% change" << std::endl << std::endl;
    std::cout << portfolio->date->to_string();
}

void Backtest::simulate_trading () {
    run_backtest();
    output_performance();
}