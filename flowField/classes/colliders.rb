class CircleCollider
    attr_accessor :x, :y, :r, :x_vel, :y_vel
    def initialize(x, y, r)
        @x = x
        @y = y
        @r = r
    end

    def mouseInside(mouse)
        return ((@x - mouse.x) * (@x - mouse.x)) + ((@y - mouse.y) * (@y - mouse.y)) <= @r * @r
    end

    def serialize
        {x: @x, y: @y, r: @r}
    end

    def inspect
        serialize.to_s
    end

    def to_s
        return "CircleCollider: #{@x}, #{@y}, #{@r}"
    end
end