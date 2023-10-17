from datahandler import *
from collections import deque

symbols = ['TSLA', 'RIVN']

start_date = '2023-09-20'
data_handler = HistoricalDataHandler(start_date, start_date, symbols)
print(data_handler.data['TSLA'].curr()['high'])

test = deque()

for i in range(15):
	data_handler.next_date()
print(data_handler.datetime)
