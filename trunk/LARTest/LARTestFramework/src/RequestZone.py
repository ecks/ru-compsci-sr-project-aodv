"""
This class defines the interface for 
a LAR containment strategy.

The idea here, is that clients
can supply a LARTest with their own 
custom strategy so that they can test
different ways o determinig if a
RREQ should or shouldn't be 
rebroadcast.

Author: Remo Cocco
"""

class LARContainmentStrategy:
    def getSourceCoordinate(self):
        pass

    def getDestinationCoordinate(self):
        pass

    def isInRequestedZone(self, coordinate):
        pass

    def __str__(self):
        pass
