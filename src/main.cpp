#include <iostream>

#include "event.h"
#include "datetime.h"
#include "datahandler.h"
#include "performance.h"
#include "portfolio.h"
#include "strategy.h"
#include "backtest.h"

void HistoricalCSVHandlerTests() {
    std::deque<Event*> event_queue;
    std::vector<std::string> symbols = {"RIVN", "TSLA"};
    HistoricalCSVHandler h = HistoricalCSVHandler(symbols, "./historical_data", &event_queue);

    for (int i = 0; i < 10; i++) {
        h.update_bars("TSLA");
    }

    Entry* e = h.get_latest_bar("TSLA");
    std::vector v = h.get_latest_bars("TSLA", 3);

    std::cout << h.get_latest_datetime("TSLA")->to_string();
    std::cout << e->to_string();
    
    for (auto a : v) {
        std::cout << a->to_string();
    }

    std::cout << event_queue.size() << "\n";
    std::cout << event_queue[0]->type;

    std::cout << "\n\n";
}

void EventTests() {
    Datetime* d = new Datetime("2021-11-16 12:01:07");
    MarketEvent* m = new MarketEvent(d);
    SignalEvent* s = new SignalEvent("as", "abc", d, SHORT, 10);
    OrderEvent* o = new OrderEvent("as", MKT, 10, d, LONG);
    FillEvent* f = new FillEvent("ga", 25, LONG, 20, d, 11);

    std::cout << f->type << "\n";
    std::cout << o->datetime->to_string();

    std::cout << "\n\n";
}

void BarValTests() {
    std::deque<Event*> event_queue;
    std::vector<std::string> symbols = {"RIVN", "TSLA"};
    HistoricalCSVHandler h = HistoricalCSVHandler(symbols, "./historical_data", &event_queue);

    for (int i = 0; i < 10; i++) {
        h.add_new_bar("TSLA");
    }

    std::cout << h.get_latest_bar_val("TSLA", "OPEN") << "\n";
    
    std::vector<double> v = h.get_latest_bar_vals("TSLA", "CLOSE", 3);
    for (auto a : v) {
        std::cout << a << " ";
    }

    std::cout << "\n\n";
}

void PerformanceTests() {
    std::vector<double> v = {1, 2, 3};

    std::cout << create_sharpe_ratio(v, 3);
}

void PortfolioConstrTests() {
    std::deque<Event*> event_queue;
    std::vector<std::string> symbols = {"RIVN", "TSLA"};
    HistoricalCSVHandler h = HistoricalCSVHandler(symbols, "./historical_data", &event_queue);
    Datetime d = Datetime("2024-01-20 10:12:55");
    Portfolio p = Portfolio(&h, &event_queue, &d);

    h.update_bars("TSLA");
    h.update_bars("RIVN");

    FillEvent* f = new FillEvent("TSLA", 25, LONG, 20, &d, 11);
    p.update_fill(f);
    p.print_holdings();

    h.update_bars("TSLA");
    p.update_time_index();
    p.print_holdings();

    std::cout <<"\n\n";
}

void BacktestTests() {
    MovingAverageCrossover* s = new MovingAverageCrossover(20, 40, "GOOG");
    Datetime* d = new Datetime("2004-12-16");
    Backtest b = Backtest("GOOG", d, s, 100000, 0, 10000, 0.02);
    b.simulate_trading();
}

int main() {

    BacktestTests();
    return 0;
}