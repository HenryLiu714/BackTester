#include "backtest.h"
#include "performance.h"

#include <iostream>
#include <thread>
#include <chrono>
#include <fstream>
#include <cmath>


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
                equities = std::vector<std::pair<std::string, double>>();

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
                equities = std::vector<std::pair<std::string, double>>();

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

    HistoricalCSVHandler::update_data(symbols_list);

    for (auto s : data_handler->symbols_list) {
        data_handler->update_bars(s);
        while (datetime->is_after(data_handler->get_latest_datetime(s))) {
            data_handler->update_bars(s);
        }     
    }

    datetime = data_handler->get_latest_datetime(data_handler->symbols_list[0]);

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
        equities.push_back(std::pair<std::string, double>(portfolio->date->to_string_day(), portfolio->value));
        std::this_thread::sleep_for(std::chrono::milliseconds(heartbeat));

        for (auto s : data_handler->symbols_list) {
            data_handler->update_bars(s);
            if (counter % 100 == 0) std::cout << "Currently trading on: " << data_handler->get_latest_datetime(s)->to_string() << std::endl;
        }
    }

    std::cout << "Done backtesting trades" << "\n" << "-------------------------------" << "\n\n";
}

void Backtest::write_equity_curve() {
    std::cout << "Writing output files..." << "\n";
    std::ofstream myFile("./output/equity_curve.csv");
    
    myFile << "Date,Equity" << std::endl;
    for (std::pair<std::string, double> p : equities) {
        myFile << p.first << "," << p.second << std::endl;
    }

    myFile.close();
    std::cout << "Exporting equity curve..." << "\n";
    std::system("python ./scripts/generate_equity_curve.py");
}

std::vector<double> get_metrics(const std::vector<std::pair<std::string, double>>& equities) {
    double max_drawdown = 0;
    double max_drawdown_length = 0;
    double curr_length = 0;

    if (equities.size() == 0) return {};
    double max = equities[0].second;
    double min = max;
    std::vector<double> returns;

    for (const std::pair<std::string, double>& p : equities) {
        if (p.second > max) {
            max = p.second;
            max_drawdown_length = std::max(curr_length, max_drawdown_length);
            curr_length = 0;
        }

        max_drawdown = std::min(max_drawdown, (p.second - max)/max);

        min = std::min(min, p.second);
        curr_length++;

        returns.push_back(p.second);
    }
    max_drawdown_length = std::max(curr_length, max_drawdown_length);

    double sharpe_ratio = create_sharpe_ratio(returns, returns.size());

    return {max, min, max_drawdown * 100, max_drawdown_length, sharpe_ratio};
}

double annual_return(int days, double total_return) {
    return (std::pow(total_return, 1/((double)days/365)) - 1) * 100;
}

void Backtest::output_performance() {
    write_equity_curve();

    std::cout << "Loading backtest results..." << "\n" << "-------------------------------" << "\n\n";
    
    std::vector<double> drawdowns = get_metrics(equities);
    double annual = annual_return(equities.size(), portfolio->value / initial_capital);

    std::ofstream output_file("./output/performance_metrics.txt");

    std::cout << "Trading Strategy Overview" << std::endl;
    std::cout << "-------------------------------" << std::endl << std::endl;
    std::cout << "Start Date:                 " << datetime->to_string_day() << std::endl;
    std::cout << "End Date:                   " << portfolio->date->to_string_day() << std::endl;
    std::cout << "Starting Balance:           " << initial_capital << std::endl;
    std::cout << "Final Balance:              " << portfolio->value << std::endl;
    std::cout << "Overall Performance [%]:    " << ((portfolio->value - initial_capital) / initial_capital) * 100 << std::endl;
    std::cout << "Equity Initial [$]:         " << initial_capital << std::endl;
    std::cout << "Equity Final [$]:           " << portfolio->value << std::endl;
    std::cout << "Equity Change [$]:          " << portfolio->value - initial_capital << std::endl;
    std::cout << "Maximum Equity [$]:         " << drawdowns[0] << std::endl;
    std::cout << "Minimum Equity [$]:         " << drawdowns[1] << std::endl;
    std::cout << "Maximum Drawdown [%]:       " << drawdowns[2] << std::endl;
    std::cout << "Maximum Drawdown Duration:  " << drawdowns[3] << " days" << std::endl;
    std::cout << "Average Annual Return [%]:  " << annual << std::endl;
    std::cout << "Sharpe Ratio:               " << drawdowns[4] << std::endl;

    output_file << "Trading Strategy Overview" << std::endl;
    output_file << "-------------------------------" << std::endl << std::endl;
    output_file << "Start Date:                 " << datetime->to_string_day() << std::endl;
    output_file << "End Date:                   " << portfolio->date->to_string_day() << std::endl;
    output_file << "Starting Balance:           " << initial_capital << std::endl;
    output_file << "Final Balance:              " << portfolio->value << std::endl;
    output_file << "Overall Performance [%]:    " << ((portfolio->value - initial_capital) / initial_capital) * 100 << std::endl;
    output_file << "Equity Initial [$]:         " << initial_capital << std::endl;
    output_file << "Equity Final [$]:           " << portfolio->value << std::endl;
    output_file << "Equity Change [$]:          " << portfolio->value - initial_capital << std::endl;
    output_file << "Maximum Equity [$]:         " << drawdowns[0] << std::endl;
    output_file << "Minimum Equity [$]:         " << drawdowns[1] << std::endl;
    output_file << "Maximum Drawdown [%]:       " << drawdowns[2] << std::endl;
    output_file << "Maximum Drawdown Duration:  " << drawdowns[3] << " days" << std::endl;
    output_file << "Average Annual Return [%]:  " << annual << std::endl;
    output_file << "Sharpe Ratio:               " << drawdowns[4] << std::endl;
    
    output_file.close();
}

void Backtest::simulate_trading () {
    run_backtest();
    output_performance();
}