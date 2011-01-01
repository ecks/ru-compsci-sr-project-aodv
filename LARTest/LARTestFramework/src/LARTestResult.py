"""
This class encapsulates 
all of the data associated with
the results generated by a LARTest.

Author: Remo Cocco
"""

class LARTestResult:
    """
    The LARRequestZone that this contains 
    results for.
    """
    _requestZone = None


    """
    Stores all of the coordinates contained by the bounding area
    i.e The coordinates that will rebroadcast
    """
    _containedCoordinates = []


    """
    Stores all of the coordinate not contained by the bounding area
    i.e The coordinates that will not rebroadcast
    """
    _uncontainedCoordinates = []

    def __init__(self, requestZone, containedCoordinate, uncontainedCoordinate):
        self._requestZone = requestZone
        self._containedCoordinates = containedCoordinate
        self._uncontainedCoordinates = uncontainedCoordinate

    def getRequestZone(self):
        return self._requestZone

    def getContainedCoordinate(self):
        return self._containedCoordinates

    def getUncontainedCoordinate(self):
        return self._uncontainedCoordinates