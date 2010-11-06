"""
Class for keeping track of data for LAR Routing protocol

This class has been deemed deprecated,
since it is just two coordinates.

Author: Remo Cocco
Date: Tue Oct 19 2010
"""

# from Coordinate import *
from Coordinate import Coordinate

class LARData:
    _source = Coordinate()
    _destination = Coordinate()

    def __init__(self, source = Coordinate(), destination = Coordinate()):
        self._source = source
        self._destination = destination

    def getSourceCoordinate(self):
        return self._source

    def getDestinationCoordinate(self):
        return self._destination

    def __str__(self):
        return "{source: %s, destination %s}" % (self._source, self._destination)

"""
some testing
"""
def main():
    ld = LARData(source = Coordinate(x=3), destination = Coordinate(y=5))
    c = ld.getSourceCoordinate()
    print c
    print ld

if __name__ == "__main__":
    main()

