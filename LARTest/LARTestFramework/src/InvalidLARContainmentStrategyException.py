"""
This class should be thrown when an invalid
LARContainmentStrategy is supplied to a function

Author: Remo Cocco
"""


class InvalidLARContainmentStrategyException(Exception):
    def __init__(self, value):
        self.value = value
    def __str__(self):
        return repr(self.value)
