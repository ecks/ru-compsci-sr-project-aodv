"""
This class defines the interface for
a LARTest view.

View's are simple. They need to be
able to 
    1) Display themselves on demand
    2) Add requests
    3) Update on demand

The interface relfects these duties,
and leave it up to the implementer of
the view to decide of to perform
these operations

Author: Remo Cocco
"""

class LARTestView:
    def display(self):
        pass

    def addResult(self, result):
        pass

    def update(self):
        pass

    def __str__(self):
        pass

