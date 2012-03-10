class Coordinate
    def initialize(x = 0,  y = 0)
        @x, @y = x, y
    end

    def to_s()
        "(#{@x}, #{@y})"
    end
end

