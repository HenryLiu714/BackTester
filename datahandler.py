from abc import ABC, abstractmethod
import csv
from collections import deque
import pandas as pd

from events import *


# Abstract class to handle data from a stream
class DataHandler(ABC):
    pass

# HistoricalDataHandler
# Holds a list of HistoricalData objects, has method to return MarketEvents at each step
class HistoricalDataHandler(DataHandler):
    def __init__(self, start_datetime, end_datetime, data_symbols):
        self.datetime = start_datetime
        self.end_datetime = end_datetime
        self.data = {}

        for symbol in data_symbols:
            historical_data = HistoricalData(symbol, start_datetime)
            self.data[symbol] = historical_data

    # Adds one to the date
    # If using intraday data, can be modified accordingly
    def next_date(self):
        self.datetime = (pd.Timestamp(self.datetime) + pd.DateOffset(days=1)).strftime('%Y-%m-%d')

    # Adds Market Events into event_queue
    def get_market_events(event_queue: deque[Event]):
        # Stop once end date time is reached
        if self.datetime > self.end_datetime:
            return

        for sym, val in self.data:
            if (val.curr()['datetime'] < date):
                while (val.curr()['datetime'] < date):
                    val.get_next()
            if (val.curr()['datetime'] == date):
                event_queue.push(MarketEvent(date, sym, val))

        
class HistoricalData(object):
    # Constructor for HistoricalData object, which keeps track OHLC data
    # for data from a csv file
    # Parameters:
    # filepath - file path to csv file with historical data
    # start_datetime - datetime to start reading the file from, if unspecified will start from 0
    def __init__(self, symbol, start_datetime='0'):
        # Read input historical data file as csv
        filepath = f'./historical_data/{symbol}.csv' 
        with open(filepath, 'r') as data_file:
            # Sets delimiter to ',' by default
            data_reader = csv.reader(data_file, delimiter = ',')
            next(data_reader)

            self.current = 0
            for line in data_reader:
                if line[0] < start_datetime:
                    next(data_reader)
                else:
                    break

            self.data = pd.DataFrame(list(data_reader), columns=['datetime', 'open', 'high', 'low', 'close', 'adj_close', 'volume'])

    # Returns next item from data queue
    def get_next(self):
        res = self.data.iloc[self.current]
        self.current+= 1
        return res

    # Returns current item without incrementing
    def curr(self):
        return self.data.iloc[self.current]


