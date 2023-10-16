from collections import deque

class Event(object):
    # An interface for subsequent Event classes
    pass

class MarketEvent(Event):
    # Handles event of receiving a new market update

    def __init__(self):
        self.type = 'market'

class SignalEvent(Event):
    # Handles event of type signal

    # Parameters:
    # datetime - YYYYMMDD HHMMSS format, date and time the order is made
    # symbol - symbol being traded
    # signal = 'long' or 'short'Ppac
    # strength = strength of the signal
    def __init__(self, datetime, symbol, signal, strength):
        self.type = 'signal'

        self.datetime =  datetime
        self.symbol = symbol
        self.signal = signal
        self.strength = strength

class OrderEvent(Event):
    # Handles an order 

    # Parameters:
    # symbol - symbol being traded
    # quantity - non-negative integer, the quantity being traded in this order
    # direction - "buy" or "sell"
    def __init__(self, symbol, quantity, direction):
        self.type = 'order'

        self.symbol = symbol
        self.quantity = quantity
        self.direction = direction

    # Displays values involved with the order
    def print_order(self):
        print(f"Order: Symbol = {self.symbol}, Quantity = {self.quantity}, Direction = {self.direction}")

class FillEvent(Event):
    # Event returned whenever order is placed, showing the order was filled

    # Parameters:
    # datetime - YYYYMMDD HHMMSS format, date and time the order is filled
    # symbol - symbol being traded
    # quantity - non-negative integer, the quantity being traded in this order
    # direction - "buy" or "sell"
    # commission - total commission cost for order, default is 0
    def __init__(self, datetime, symbol, quantity, direction, commission=0):
        self.datetime = datetime
        self.symbol = symbol
        self.quantity = quantity
        self.direction = direction
        self.commission = commission