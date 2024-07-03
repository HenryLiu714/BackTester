#include <vector>
#include <string>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <deque>

#include "datahandler.h"
#include "datetime.h"
#include "entry.h"

HistoricalCSVHandler::HistoricalCSVHandler(std::string symbol, std::string file_dir, std::deque<Event*>* events_) {
    std::string filepath = file_dir + "/" + symbol + ".csv";
    
    data[symbol].open(filepath);

    if (data[symbol].fail()) {
        std::cerr << "Unable to open file " << filepath << std::endl;
        throw std::invalid_argument("Invalid filepath");
    }

    else {
        symbols_list.push_back(symbol);
        entries[symbol] = {};

        if (data[symbol].peek() > '9') {
            std::string a;
            std::getline(data[symbol], a);
        }
    }

    events = events_;
    continue_backtest = 1;
}

HistoricalCSVHandler::HistoricalCSVHandler(std::vector<std::string> symbols, std::string file_dir, std::deque<Event*>* events_) {
    for (int i = 0; i < symbols.size(); i++) {
        std::string filepath = file_dir + "/" + symbols[i] + ".csv";
        data[symbols[i]].open(filepath);

        if (data[symbols[i]].fail()) {
            std::cerr << "Unable to open file " << filepath << std::endl;
            throw std::invalid_argument("Invalid filepath");
        }

        else {
            symbols_list.push_back(symbols[i]);
            entries[symbols[i]] = {};
            if (data[symbols[i]].peek() > '9') {
                std::string a;
                std::getline(data[symbols[i]], a);
            }
        }
    }

    events = events_;
    continue_backtest = 1;
} 

std::vector<std::string> split_string(std::string s, std::string delim) {
    int pos = 0;
    std::vector<std::string> v;

    pos = s.find(delim);
    while (pos != std::string::npos) {
        v.push_back(s.substr(0, pos));
        s = s.substr(pos + delim.size());
        pos = s.find(delim);
    }

    v.push_back(s);
    return v;
}

Entry* HistoricalCSVHandler::add_new_bar(std::string symbol) {
    if (data.find(symbol) == data.end()) {
        throw std::invalid_argument("Symbol not in symbols list: " + symbol);
    }

    if (data[symbol].peek() == EOF) {
        return NULL;
    }

    std::string new_entry;
    getline(data[symbol], new_entry);
    std::vector<std::string> values = split_string(new_entry, ",");

    Entry* e = new Entry(symbol, new Datetime(values[0]), std::stod(values[1]), std::stod(values[2]), std::stod(values[3]), std::stod(values[4]), std::stod(values[5]), std::stol(values[6]));

    entries[symbol].push_back(e);
    return e;
}

Entry* HistoricalCSVHandler::get_latest_bar(std::string symbol) {
    if (entries.find(symbol) == entries.end()) {
        throw std::invalid_argument("Symbol not in symbols list: " + symbol);
        return NULL;
    }

    if (entries[symbol].size() == 0) {
        throw std::invalid_argument("Symbol has no entries yet: " + symbol);
        return NULL;
    } 

    return entries[symbol].back();
}

std::vector<Entry*> HistoricalCSVHandler::get_latest_bars(std::string symbol, int N) {
   if (entries.find(symbol) == entries.end()) {
        throw std::invalid_argument("Symbol not in symbols list: " + symbol);
        return std::vector<Entry*>();
    }

    N = std::min((int) entries[symbol].size(), N+1);

    if (N == 0) {
        throw std::invalid_argument("Symbol has no entries yet: " + symbol);
    }

    std::vector<Entry*> v;
    for (int i = entries[symbol].size() - N; i < entries[symbol].size() - 1; i++) {
        v.push_back(entries[symbol][i]);
    }
    
    return v;
}

Datetime* HistoricalCSVHandler::get_latest_datetime(std::string symbol) {
    if (entries.find(symbol) == entries.end()) {
        throw std::invalid_argument("Symbol not in symbols list: " + symbol);
        return NULL;
    }
    
    return entries[symbol].back()->date;
}

double get_bar_val(Entry* e, std::string val) {
    if (val == "OPEN") return e->open_price;
    if (val == "HIGH") return e->high_price;
    if (val == "LOW") return e->low_price;
    if (val == "CLOSE") return e->close_price;
    if (val == "ADJ") return e->adj_close_price;
    if (val == "VOLUME") return e->volume;
    throw std::invalid_argument("Invalid argument val");
}

double HistoricalCSVHandler::get_latest_bar_val(std::string symbol, std::string val) {
    Entry* e = this->get_latest_bar(symbol);

    if (e == NULL) {
        throw std::logic_error("Invalid Entry");
    }

    return get_bar_val(e, val);
}

std::vector<double> HistoricalCSVHandler::get_latest_bar_vals(std::string symbol, std::string val, int N) {
    std::vector<Entry*> v = this->get_latest_bars(symbol, N);
    
    std::vector<double> vals;

    for (auto e : v) {
        if (e == NULL) throw std::logic_error("Invalid Entry");
        vals.push_back(get_bar_val(e, val));
    }

    return vals;
}

void HistoricalCSVHandler::update_bars(std::string symbol) {
    if (continue_backtest) {
        Entry* e = add_new_bar(symbol);

        if (e == NULL) {
            continue_backtest = 0;
            return;
        }

        events->push_back(new MarketEvent(e->date));
    }
}

void HistoricalCSVHandler::update_data(std::string symbol) {
    std::string command = "python3 scripts/add_data.py " + symbol;
    std::system(command.c_str());
}

void HistoricalCSVHandler::update_data(std::vector<std::string> symbols) {
    std::string command = "python3 scripts/add_data.py";

    for (std::string symbol : symbols) {
        command += " " + symbol;
    }

    std::system(command.c_str());
}