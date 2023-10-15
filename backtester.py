
# Main module to execute to run a backtest
class BackTester(object):
    # BackTester object to perform a backtest
    def __init__(self, strategy, startDateTime, endDateTime):
        self.strategy = strategy
        self.startDateTime = startDateTime
        self.endDateTime = endDateTime