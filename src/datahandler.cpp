#include <vector>
#include <string>
#include <stdexcept>
#include <iostream>
#include <fstream>

#include "datahandler.h"
#include "datetime.h"
#include "entry.h"

HistoricalCSVHandler::HistoricalCSVHandler(std::string symbol, std::string filepath) {
    data[symbol].open(filepath);

    if (data[symbol].fail()) {
        std::cerr << "Unable to open file " << filepath << std::endl;
    }

    if (data[symbol].peek() > '9') {
        std::string a;
        std::getline(data[symbol], a);
    }
}

HistoricalCSVHandler::HistoricalCSVHandler(std::vector<std::string> symbols, std::vector<std::string> filepaths) {
    for (int i = 0; i < symbols.size(); i++) {
        data[symbols[i]].open(filepaths[i]);

        if (data[symbols[i]].fail()) {
            std::cerr << "Unable to open file " << filepaths[i] << std::endl;
        }

        if (data[symbols[i]].peek() > '9') {
            std::string a;
            std::getline(data[symbols[i]], a);
        }
    }
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
        std::cerr << "Symbol not in data" << std::endl;
        return NULL;
    }

    if (data[symbol].peek() == EOF) {
        return NULL;
    }

    std::string new_entry;
    getline(data[symbol], new_entry);
    std::vector<std::string> values = split_string(new_entry, ",");

    Entry* e = new Entry(symbol, Datetime(values[0]), std::stod(values[1]), std::stod(values[2]), std::stod(values[3]), std::stod(values[4]), std::stod(values[5]), std::stol(values[6]));

    entries[symbol].push_back(e);
    return e;
}