"""
This class contains the logic 
for containment for the LAR 1
method of containment.

Author: Malik Ahmed
Author: Remo Cocco

"""

import sys
sys.path.append("../LARTestFramework/src/")

from Coordinate import Coordinate
from RequestZone import RequestZone
from LARData import LARData
from LARTest import LARTest
from Rectangle import Rectangle

class LAR1RequestZone(RequestZone):

    _larData = LARData()
    _expectedZoneRectangle = None
    _expectedZoneRadius = 5
    _boundingRectangle = None

    def __init__(self, larData, expectedZoneRadius = 5):
        self._larData = larData
        self._expectedZoneRadius = expectedZoneRadius

        self_expectedZoneRectangle = None

        self.calculateExpectedZoneRectangle()
        self.calculateBoundingRectangle()

    def calculateExpectedZoneRectangle(self):
        # this line is giving problsm
        # the interperter claims that _expectedZoneRectangle was never defined
        # if _expectedZoneRectangle is None:
        destination = self._larData.getDestinationCoordinate()

        bottomLeft = Coordinate(destination.getX() - self._expectedZoneRadius, destination.getY() - self._expectedZoneRadius)
        topLeft = Coordinate(destination.getX() - self._expectedZoneRadius, destination.getY() + self._expectedZoneRadius)
        topRight = Coordinate(destination.getX() + self._expectedZoneRadius, destination.getY() + self._expectedZoneRadius)
        bottomRight = Coordinate(destination.getX() + self._expectedZoneRadius, destination.getY() - self._expectedZoneRadius)

        self._expectedZoneRectangle = Rectangle(bottomLeft, topLeft, topRight, bottomRight)

    def calculateBoundingRectangle(self):
        # if _boundingRectangle is None:
        if (self.sourceIsInExpectedZone()):
            #print ("Is in expected rectangle")
            self.calculateRequestedZoneSourceInsideExpectedZone()
        else:
            #print ("Is not in expected rectangle")
            self.calculateRequestedZoneSourceOutsideExpectedZone()

    """
    Determine is the source node is in the
    expected rectangle.
    """
    def sourceIsInExpectedZone(self):
        return self._expectedZoneRectangle.containsCoordinate(self._larData.getSourceCoordinate())
        

    """
    Return the boudning rectangle if the source node 
    is inside the expected zone.
    """
    def calculateRequestedZoneSourceInsideExpectedZone(self):
        # If we are inside the expected zone, then
        # the expced zone and the requested zone are identical
        self._boundingRectangle = self._expectedZoneRectangle

    """
    Return the boudning rectangle if the source node 
    is outside the expected zone.
    """
    def calculateRequestedZoneSourceOutsideExpectedZone(self):
        source = self._larData.getSourceCoordinate()
        destination = self._larData.getDestinationCoordinate()

        bottomLeft = source
        topLeft = Coordinate(source.getX(), destination.getY() + self._expectedZoneRadius)
        topRight = Coordinate(destination.getX() + self._expectedZoneRadius, destination.getY() + self._expectedZoneRadius)
        bottomRight = Coordinate(destination.getX()  + self._expectedZoneRadius, source.getY())

        self._boundingRectangle = Rectangle(bottomLeft, topLeft, topRight, bottomRight)

    """
    RequestZone Functions
    """
    
    def getSourceCoordinate(self):
        return self._larData.getSourceCoordinate()

    def getDesintationCoordinate(self):
        return self._larData.getDestinationCoordinate()

    def isInRequestedZone(self, coordinate): 
        return self._boundingRectangle.containsCoordinate(coordinate)

    def getBoundingShapei(self):
        return self._boundingRectangle

    def __str__(self):
      return "%s Bounding Rectangle %s when destination expected zone has radius %d" % (self._larData,self._boundingRectangle, self._expectedZoneRadius)


