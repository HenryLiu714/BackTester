from abc import ABC, abstractmethod
from collections import deque
from events import *

# Interface for a Strategy object
class Strategy(ABC):

    # Method to update the event queue (i.e. create an order event) given the current event queue
    # Given an event and the current event queue, can add a SignalEvent to the event queue
    @abstractmethod
    def update(self, event: Event) -> Event | None:
        pass

