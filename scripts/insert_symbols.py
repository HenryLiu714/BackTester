import datetime
from math import ceil
import bs4
import MySQLdb as mdb
import requests

import mysql_key

def obtain_parse_wiki_snp500():
    """
    Download and parse the Wikipedia list
    of SnP500 using requests and beautifulsoup
    
    Returns a list of tuples to add the sql database
    """

    now = datetime.datetime.utcnow()

    response = requests.get("http://en.wikipedia.org/wiki/List_of_S%26P_500_companies")
    soup = bs4.BeautifulSoup(response.text, features="html.parser")

    # Selects the first table and ignores the header row
    symbols_list = soup.select('table')[0].select('tr')[1:]

    symbols = []
    for i, symbol in enumerate(symbols_list):
        tds = symbol.select('td')

        symbols.append(
            (
                tds[0].select('a')[0].text, # Ticker
                'stock',
                tds[1].select('a')[0].text, # Name
                tds[3].text, # Sector
                'USD', now, now
            )
        )

    return symbols

def insert_symbols_into_table(symbols):
    """
    Insert the symbols into SQL table
    """

    # Connect to SQL
    db_host = 'localhost'
    db_user = 'sec_user'
    db_pass = 'gettysburg714'
    db_name = 'securities_master'
    con = mdb.connect(
        host = db_host, user = db_user, passwd = db_pass, db = db_name
    )

    # Create insert strings
    final_str = "INSERT INTO symbol (ticker, instrument, name, sector, currency, created_date, last_updated_date) VALUES (%s, %s, %s, %s, %s, %s, %s)"
    print(symbols)
    with con:
        cur = con.cursor()
        cur.executemany(final_str, symbols)
        # con.commit()
        # cur.close()
    

if __name__ == "__main__":
    symbols = obtain_parse_wiki_snp500()
    insert_symbols_into_table(symbols)
