#include "backtest.h"

#include <iostream>
#include <thread>
#include <chrono>

Backtest::Backtest(
            const std::vector<std::string>& symbols_list_, Portfolio* portfolio_,
            Datetime* start_date_, DataHandler* data_handler_, ExecutionHandler* execution_handler_,
            Strategy* strategy_, double initial_capital, int heartbeat_) {
                symbols_list = symbols_list_;
                strategy = strategy_;
                datetime = start_date_;
                data_handler = data_handler_;
                execution_handler = execution_handler_;
                heartbeat = heartbeat_;
                portfolio = portfolio_;

                signals = 0;
                orders = 0;
        }

Backtest::Backtest(
            const std::string& symbol, Datetime* start_date_,
            Strategy* strategy_, double initial_capital, int heartbeat_,
            const std::string& csv_path) {
                symbols_list = {symbol};
                datetime = start_date_;
                heartbeat = heartbeat_;
                strategy = strategy_;

                std::deque<Event*>* events = new std::deque<Event*>();
                
                data_handler = new HistoricalCSVHandler(symbol, csv_path, events);
                execution_handler = new SimulationExecutionHandler(events);
                portfolio = new Portfolio(data_handler, events, start_date_, initial_capital);
        
                signals = 0;
                orders = 0;
        }

void Backtest::run_backtest() {
    int counter = 0;
    std::deque<Event*>* events = portfolio->events;

    while (data_handler->continue_backtest) {
        std::cout << "Day " << counter << std::endl;
        data_handler->update_bars("TSLA");

        while (!events->empty()) {
            Event* event = events->front();
            events->pop_front();

            if (event == NULL) {

            }

            else if (event->type == "MARKET") {
                events->push_back(strategy->calculate_signals());
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

        portfolio->print_holdings();
        counter++;
        std::this_thread::sleep_for(std::chrono::milliseconds(heartbeat));
    }
}