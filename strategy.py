from abc import ABC, abstractmethod
from collections import deque
from events import *

# Interface for a Strategy object
class Strategy(ABC):

    # Method to update the event queue (i.e. create an order event) given the current event queue
    # Given an event (from the Event queue), can return either an order it would like to make or none
    @abstractmethod
    def update(self, event: Event) -> Event | None:
        pass

