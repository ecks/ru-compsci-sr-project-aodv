#!/usr/bin/env python


import sys
sys.path.append("../LARTestFramework/src/")

from Coordinate import Coordinate
from LARContainmentStrategy import LARContainmentStrategy
from LAR1ContainmentStrategy import LAR1ContainmentStrategy
from LARData import LARData
from LARTest import LARTest
from Rectangle import Rectangle

def main():
    source = Coordinate(1,3)
    destination = Coordinate(5, 3)
    larData = LARData(source, destination)
    lar1ContainmentStrategy = LAR1ContainmentStrategy(larData, expectedZoneRadius=2)
    larTest = LARTest(lar1ContainmentStrategy)
    print lar1ContainmentStrategy
    print larTest

if __name__ == "__main__":
    main()

