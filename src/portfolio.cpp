#include "portfolio.h"

#include <iostream>
std::unordered_map<std::string, int> construct_all_positions(const std::vector<std::string>& symbols_list) {
        std::unordered_map<std::string, int> u;
        for (auto symbol : symbols_list) {
                u[symbol] = 0;
        }

        return u;
}

std::unordered_map<std::string, double> construct_all_holdings(const std::vector<std::string>& symbol_list) {
        std::unordered_map<std::string, double> u;
        for (auto symbol : symbol_list) {
                u[symbol] = 0;
        }

        return u;
}

Portfolio::Portfolio(DataHandler* bars_, std::deque<Event*>* events_, Datetime* start_date_, double initial_capital_) {
        bars = bars_;
        events = events_;
        date = start_date_;
        value = initial_capital_;
        balance = initial_capital_;

        positions = construct_all_positions(bars->symbols_list);
        holdings = construct_all_holdings(bars->symbols_list);
}

void Portfolio::update_time_index() {
        Datetime* latest_datetime = bars->get_latest_datetime(bars->symbols_list[0]);
        
        // Update holdings
        double total_value = 0;

        for (const std::string& s : bars->symbols_list) {
                // Approximation for market value
                double market_value = bars->get_latest_bar_val(s, "ADJ");

                holdings[s] = (double) positions[s] * market_value;
                total_value += holdings[s];
        }

        value = total_value + balance;
}

void Portfolio::update_positions(FillEvent* f) {
        int fill_dir = f->direction ? -1 : 1;

        positions[f->symbol] += fill_dir * f->quantity;
}

void Portfolio::update_holdings(FillEvent* f) {
        update_positions(f);

        // Update holdings
        double total_value = 0;

        for (const std::string& s : bars->symbols_list) {
                // Approximation for market value
                double market_value = bars->get_latest_bar_val(s, "ADJ");
                
                holdings[s] = positions[s] * market_value;
                total_value += holdings[s];
        }

        balance -= total_value;
        value = total_value + balance;
}

void Portfolio::update_fill(Event* e) {
        if (e->type == "FILL") {
                update_holdings((FillEvent*) e);
        }
}

OrderEvent* Portfolio::generate_naive_order(SignalEvent* e) {
        int mkt_quantity = 100;
        int cur_quantity = positions[e->ticker];
        bool order_type = MKT;

        if (e->direction == LONG && cur_quantity == 0) return new OrderEvent(e->ticker, order_type, mkt_quantity, date, LONG);
        if (e->direction == SHORT && cur_quantity == 0) return new OrderEvent(e->ticker, order_type, mkt_quantity, date, SHORT);

        if (e->direction == EXIT && cur_quantity > 0) return new OrderEvent(e->ticker, order_type, abs(cur_quantity), date, SHORT);
        if (e->direction == EXIT && cur_quantity < 0) return new OrderEvent(e->ticker, order_type, abs(cur_quantity), date, LONG);

        return NULL;
} 

void Portfolio::update_signal(Event* e) {
        if (e->type == "SIGNAL") {
                OrderEvent* o = generate_naive_order((SignalEvent*) e);
                if (o != NULL) {
                        events->push_back(o);
                }
        }
}

void Portfolio::print_holdings() {
        for (auto s : bars->symbols_list) {
                std::cout << s << ": " << positions[s] << " shares, value: " << holdings[s] << std::endl;
        }

        std::cout << "Balance: " << balance << std::endl;
        std::cout << "Total account value: " << value << std::endl << std::endl;
}

