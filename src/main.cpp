#include <iostream>

#include "event.h"
#include "datetime.h"
#include "datahandler.h"

int main() {
    HistoricalCSVHandler h = HistoricalCSVHandler("TSLA", "./historical_data/TSLA.csv");
    Entry* e = h.add_new_bar("TSLA");

    std::cout << e->to_string();
    return 0;
}