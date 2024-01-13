import datetime
import warnings

import MySQLdb as mdb
import requests

import yfinance as yf
import matplotlib.pyplot as plt

# Connect to SQL
db_host = 'localhost'
db_user = 'sec_user'
db_pass = 'gettysburg714'
db_name = 'securities_master'
con = mdb.connect(db_host, db_user, db_pass, db_name)

def obtain_list_of_tickers():
    """
    Obtains list of tickers from database
    """

    with con:
        cur = con.cursor()
        cur.execute("SELECT id, ticker FROM symbol")
        data = cur.fetchall()
        return[(d[0], d[1]) for d in data]

def get_historic_data(ticker, start_date=(2000,1,1), end_date=datetime.date.today().timetuple()[0:3]):
    """
    Obtains data from Yahoo finance
    """

    start_date = datetime.datetime(start_date[0], start_date[1], start_date[2])
    end_date = datetime.datetime(end_date[0], end_date[1], end_date[2])
    yf_data = yf.download(ticker, start=start_date, end=end_date)
    yf_data = yf_data.reset_index()
    yf_data = yf_data.astype({'Date':'str'})

    return yf_data.values.tolist()

def insert_into_db(data_vendor_id, symbol_id, daily_data):
    """
    Makes a list of daily data and adds to MySQL database
    """
    now = datetime.datetime.utcnow()

    daily_data = [
        (data_vendor_id, symbol_id, d[0], now, now,
         d[1], d[2], d[3], d[4], d[5], d[6]) for d in daily_data
    ]

    column_str = "data_vendor_id, symbol_id, price_date, created_date,last_updated_date, open_price, high_price, low_price, close_price, adj_close_price, volume"
    insert_str = ("%s, " * 11)[:-2]
    final_str = f"INSERT INTO daily_price ({column_str}) VALUES ({insert_str})"
    
    
    con = mdb.connect(db_host, db_user, db_pass, db_name)

    with con:
        cur = con.cursor()
        cur.executemany(final_str, daily_data)
        con.commit()
        cur.close()        


tickers = obtain_list_of_tickers()

for i,t in enumerate(tickers):
    print(f'Adding data for {t[1]}')
    yf_data = get_historic_data(t[1])
    insert_into_db('1',t[0], yf_data)

print('Data successfully added to database')