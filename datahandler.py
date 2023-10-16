from abc import ABC, abstractmethod
import csv
from collections import deque
from events import *

# Abstract class to handle data from a stream
class DataHandler(ABC):
    pass

# HistoricalDataHandler
# Holds a list of HistoricalData objects, has method to return MarketEvents at each step
class HistoricalDataHandler(DataHandler):
    def __init__(self, start_datetime, end_datetime):
        self.datetime = start_datetime
        self.end_datetime = end_datetime

    # Adds Market Events into 
    def get_market_events(event_queue: deque[Event]):
        pass
        
class HistoricalData(object):
    # Constructor for HistoricalData object, which keeps track OHLC data
    # for data from a csv file
    # Parameters:
    # filepath - file path to csv file with historical data
    # start_datetime - datetime to start reading the file from, if unspecified will start from 0
    def __init__(self, filepath, start_datetime='0'):
        # Read input historical data file as csv
        with open(filepath, 'r') as data_file:
            data_reader = csv.reader(data_file, delimiter = ';')

            self.current = 0
            for line in data_reader:
                if line[0] < start_datetime:
                    next(data_reader)
                else:
                    break

            self.data = list(data_reader)
            print(len(self.data))
    
    # Returns next item from data queue
    def get_next(self):
        current_data = self.data[self.current]
        self.current += 1
        return current_data



