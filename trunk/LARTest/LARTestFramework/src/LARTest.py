"""
Class for testing LAR calculations

Author: Remo Cocco
"""


from Coordinate import Coordinate
from InvalidLARContainmentStrategyException import InvalidLARContainmentStrategyException
from LARContainmentStrategy import LARContainmentStrategy

# TODO Implement random coordinate generation for testing (Shouldn't be too hard)

class LARTest:
    """
    The current LARContainmentStrategy
    """
    _larContainmentStrategy = None


    """
    Stores the coordinates of all of the nodes in the network
    """
    _coordinates = []

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

    def __init__(self, larContainmentStrategy, *coordinates):
        if not isinstance(larContainmentStrategy, LARContainmentStrategy):
            raise InvalidLARContainmentStrategyException()

        self._larContainmentStrategy = larContainmentStrategy
        for coordinate in coordinates:
            self.addNode(coordinate)
        
    def addNode(self, coordinate):
        self._coordinates.append(coordinate)

    def run(self):
        for coordinate in self._coordinates:
            if self._larContainmentStrategy.isInRequestedZone(coordinates):
                self._containedCoordinates.append(coordinate)
            else:
                self._uncontainedCoordinates.append(coordinate)

    def getContainedCoordinates(self):
        return self._containedCoordinates

    def getUncontainedCoordinates(self):
        return self._uncontainedCoordinates

    def __str__(self):
        return "Source: %s\nDestination: %s\nContained: %s\nUncontained %s" % (self._larContainmentStrategy.getSourceCoordinate(), self._larContainmentStrategy.getDestinationCoordinate(), self._containedCoordinates, self._uncontainedCoordinates)
        
