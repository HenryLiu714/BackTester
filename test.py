from datahandler import *

filepath = './historical_data/EURUSD2022.csv'

data = HistoricalData(filepath)
print(data.get_next())
print(data.get_next())