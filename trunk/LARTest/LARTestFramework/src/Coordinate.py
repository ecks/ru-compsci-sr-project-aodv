"""
Class to encapsulate coordinates in a 
two dimensional plane

Author: Remo Cocco
Date: Tue Oct 19 2010
"""

class Coordinate:
    _x = 0
    _y = 0

    def __init__(self, x = 0, y = 0):
        self._x = x
        self._y = y

    def getX(self):
        return self._x

    def getY(self):
        return self._y

    def getCoordinates(self):
        return self._x, self._y

    def __str__(self):
        return "{%d, %d}" % (self._x, self._y)


def main():
    c = Coordinate()
    print c
    c = Coordinate(y = 4)
    print c
    c = Coordinate(4,8)
    print c

if __name__ == "__main__":
    main()
