import csv
import yfinance as yf
import sys
import os
import pandas as pd
import datetime

def update_data(ticker: str):
    csv_file = "historical_data/" + ticker + ".csv"

    if not os.path.isfile(csv_file):
        data = yf.download(ticker, start="2009-01-01").round(6) # Start gathering data from 2009
        data.to_csv(csv_file, index=True)

    else:
        with open(csv_file, "r") as f:
            dates = f.readlines()
            for i in reversed(dates):
                if i != "\n":
                    latest_date = i.split(",")[0]
                    break

            if datetime.datetime.strptime(latest_date, "%Y-%m-%d").date() == datetime.datetime.today().date():
                return
        
        with open(csv_file, "a") as f:
            start_date = datetime.datetime.strptime(latest_date, "%Y-%m-%d") + datetime.timedelta(days=1)
            data = yf.download(ticker, start=start_date.strftime("%Y-%m-%d")).round(6)
            
            if not data.empty:
                if data.iloc[0].name.date()== datetime.datetime.strptime(latest_date,"%Y-%m-%d").date():
                    return

            data.to_csv(csv_file, mode='a', index=True, header=False)

if __name__ == "__main__":
    tickers = sys.argv[1:]
    
    for ticker in tickers:
        update_data(ticker)