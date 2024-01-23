This program is an event-driven backtesting environment meant to simulate the trading environment for the development of algorithmic trading strategies. The program is implemented in C++ and offers portfolio tracking and custom strategy implementation.
This implementation is based off of the approach offered in Michael Halls-Moore's book *Successful Algorithmic Trading*. 

## Getting Started
#### Defining a Strategy
The user's algorthmic trading strategy can be defined by implementing a child of the strategy class found in **strategy.h**, or the sample trading strategy can be used.
#### Choosing Securities
The securities used for the backtester are located in the **./historical_data** folder as csv files, and any additional securities wanted by the user can be added to that folder for automatic inclusion. Additionally, the user can implement an instance of the **DataHandler** 
class found in **datahandler.h**, and doing so will allow the user to use different forms of data, whether that be alternative historical data (ex. MySQL database) or live trading data. 
#### Backtesting a Strategy
Calling `make` in the terminal will generate the necessary **backtester.exe** program, which can be run to demonstrate the strategy.

