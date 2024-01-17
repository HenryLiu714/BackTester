#include <iostream>

#include "event.h"
#include "datetime.h"
#include "datahandler.h"

int main() {
    std::vector<std::string> symbols = {"RIVN", "TSLA"};
    HistoricalCSVHandler h = HistoricalCSVHandler(symbols, "./historical_data");

    Entry* e = h.add_new_bar("TSLA");

    std::cout << e->to_string();
    return 0;
}