#!/usr/bin/env python


import sys
sys.path.append("../LARTestFramework/src/")

from Coordinate import Coordinate
from RequestZone import RequestZone
from LAR1RequestZone import LAR1RequestZone
from LARData import LARData
from LARTest import LARTest
from Rectangle import Rectangle

def main():
    source = Coordinate(1,3)
    destination = Coordinate(5, 3)
    larData = LARData(source, destination)
    lar1RequestZone = LAR1RequestZone(larData, expectedZoneRadius=2)
    larTest = LARTest(lar1RequestZone)
    print lar1RequestZone
    print larTest

if __name__ == "__main__":
    main()

