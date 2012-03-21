class Coordinate
    attr_accessor :x, :y

    def initialize(x = 0,  y = 0)
        @x, @y = x.to_i, y.to_i
    end

    def distance(coordinate) 
        return Math.sqrt((coordinate.x - @x)**2 + (coordinate.y - @y)**2)
    end

    def to_s()
        "(#{@x}, #{@y})"
    end
end
