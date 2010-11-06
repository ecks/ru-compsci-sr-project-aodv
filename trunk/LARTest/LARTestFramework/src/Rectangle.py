"""
Class to encapsulate a rectangle

Author: Remo Cocco
Date: Tue Oct 2010
"""

from Coordinate import Coordinate

class Rectangle:
    _bottomLeftCoordinate = Coordinate()
    _topLeftCoordinate = Coordinate()
    _topRightCoordinate = Coordinate()
    _bottomRightCoordinate = Coordinate()

    def __init__(self, bottomLeftCoordinate, topLeftCoordinate, topRightCoordinate, bottomRightCoordinate):
        if Rectangle.ensureConsitency(bottomLeftCoordinate, topLeftCoordinate, topRightCoordinate, bottomRightCoordinate):
            self._bottomLeftCoordinate = bottomLeftCoordinate
            self._topLeftCoordinate = topLeftCoordinate
            self._topRightCoordinate = topRightCoordinate
            self._bottomRightCoordinate = bottomRightCoordinate
        else:
            raise InvalidRectangleException("Invalid Rectangle")

    @staticmethod
    def ensureConsitency(bottomLeftCoordinate, topLeftCoordinate, topRightCoordinate, bottomRightCoordinate): 
        return bottomLeftCoordinate.getX() == topLeftCoordinate.getX() and \
               bottomLeftCoordinate.getY() == bottomRightCoordinate.getY() and \
               topRightCoordinate.getX() == bottomRightCoordinate.getX() and \
               topRightCoordinate.getY() == topLeftCoordinate.getY()

    def getBottomLeftCoordinate(self):
        return self._bottomLeftCoordinate

    def getTopLeftCoordinate(self):
        return self._topLeftCoordinate

    def getTopRightCoordinate(self):
        return self._topRightCoordinate

    def getBottomRightCoordinate(self):
        return self._bottomRightCoordinate

    def getWidth(self):
        return self._bottomRightCoordinate.getX() - self._bottomLeftCoordinate.getX()

    def getHeight(self):
        return self._topLeftCoordinate.getY() - self._bottomLeftCoordinate.getY()

    def containsCoordinate(self, coordinate):
        # assumes that all sides of the 
        # rectangle are parallel to their respective axes

        # left of rectangle
        if coordinate.getX() < self._topLeftCoordinate.getX():
            return False
        
        # above the rectangle
        if coordinate.getY() > self._topLeftCoordinate.getY():
            return False

        # right of the rectangle
        if coordinate.getX() > self._topRightCoordinate.getX():
            return False

        # below rectangle
        if coordinate.getY() < self._bottomRightCoordinate.getY():
            return False

        # Otherwise, it's in the rectangle.
        return True

    def __str__(self):
        return "{%s, %s, %s, %s}" % (self._bottomLeftCoordinate, self._topLeftCoordinate, self._topRightCoordinate, self._bottomRightCoordinate)


class InvalidRectangleException(Exception):
    def __init__ (self, value):
        self.value = value

    def __str__(self):
        return repr(self.value)



def main():
    r = Rectangle(Coordinate(0, 0), Coordinate(0, 2), Coordinate(2, 2), Coordinate(2, 0))
    print r 
    print r.getWidth()
    print r.getHeight()
    print r.containsCoordinate(Coordinate(0, 0))
    print r.containsCoordinate(Coordinate(1, 1))
    print r.containsCoordinate(Coordinate(2, 2))
    print r.containsCoordinate(Coordinate(3, 3))
    print r.containsCoordinate(Coordinate(1, 4))
    print r.containsCoordinate(Coordinate(-1, 4))
    print r.containsCoordinate(Coordinate(-1, 2))
    print r.containsCoordinate(Coordinate(1, -4))


if __name__ == "__main__":
    main()
