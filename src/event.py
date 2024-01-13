# every.py

class Event(object):
    """
    Base class providing interface for all inherited classes
    """
    pass

class MarketEvent(Event):
    """
    Market event
    """

    def __init__(self):
        self.type = 'MARKET'

class SignalEvent(Event):
    """
    Handles a signal event
    """

    def __init__(self, strategy_id, symbol, datetime, signal_type, strength):
        """
        strategy_id - ID of the strategy to generate signals
        symbol - symbol of trade
        datetime - time of event creation
        signal_type - 'LONG' or 'SHORT'
        strength - strength of signal
        """

        self.type = 'SIGNAL'
        self.strategy_id = strategy_id
        self.symbol = symbol
        self.datetime = datetime
        self.signal_type = signal_type
        self.strength = strength

class OrderEvent(Event):
    """
    Handles the event of sending an order
    to the execution system
    """

    def __init__(self, symbol, order_type, quantity, direction):
        """
        symbol - symbol being traded
        order_type - 'MKT' for market or 'LMT' for limit
        quantity - non-negative integer for quantity
        direction - 'BUY' or 'SELL'
        """

        self.type = 'ORDER'
        self.symbol = symbol
        self.order_type = order_type
        self.quantity = quantity
        self.direction = direction

    def print_order(self):
        """
        Outputs values of the order
        """

        print(
            f'Order: Symbol={self.symbol}, Type={self.type}, Quantity={self.quantity}, Direction={self.direction}'
        )

class FillEvent(Event):
    """
    Event describing transaction caused by order, including fees and slippage and cost
    """

    def __init__(self, timeindex, symbol, exchange, quantity, direction, fill_cost, commission=0):
        """
        timeindex - the bar resolution when the order was filled
        symbol - the instrument being filled
        exchange - the exchange where the order was filled
        quantity - the filled quantity
        direction - the direction of fill ('BUY' or 'SELL')
        fill_cost - the holdings values in dollars
        commision - an optional commission
        """

        self.type = 'FILL'
        self.timeindex = timeindex
        self.symbol = symbol
        self.exchange = exchange
        self.quantity = quantity
        self.direction = direction
        self.fill_cost = fill_cost
        self.commission = commission
