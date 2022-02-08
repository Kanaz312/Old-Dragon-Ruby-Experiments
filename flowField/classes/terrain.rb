class Wall
    LINE_RADIUS = 2
    START_SIDE = 0
    END_SIDE = 1
    attr_accessor :r
    def initialize(start_x, start_y, end_x, end_y)
        @x1 = start_x
        @y1 = start_y
        @x2 = end_x
        @y2 = end_y
        @r = Wall::LINE_RADIUS
        @d = 2 * @r
        normalx = -(end_y - start_y)
        normaly = (end_x - start_x)
        dist = Math.sqrt(normalx * normalx + normaly * normaly)
        normalx = normalx / dist
        normaly = normaly / dist
        @p1_top = [@x1 + (normalx * @r), @y1 + (normaly * @r)]
        @p1_bot = [@x1 - (normalx * @r), @y1 - (normaly * @r)]
        @p2_top = [@x2 + (normalx * @r), @y2 + (normaly * @r)]
        @p2_bot = [@x2 - (normalx * @r), @y2 - (normaly * @r)]
        @selected_end = START_SIDE
        @length  = 0
        calculateLength()
        @bounding_box = boundingBox()
    end

    def mouseOnCircle?(x, y)
        if ((@x1 - x) * (@x1 - x)) + ((@y1 - y) * (@y1 - y)) < @r * @r - 0.001
            @selected_end = START_SIDE
            return true
        elsif ((@x2 - x) * (@x2 - x)) + ((@y2 - y) * (@y2 - y)) < @r * @r - 0.001
            @selected_end = END_SIDE
            return true
        end
        return false
    end

    def moveToMouse(x, y)
        if @selected_end == START_SIDE
            @x1 = x
            @y1 = y
        else
            @x2 = x
            @y2 = y
        end
        normalx = -(@y2 - @y1)
        normaly = (@x2 - @x1)
        dist = Math.sqrt(normalx * normalx + normaly * normaly)
        normalx = normalx / dist
        normaly = normaly / dist
        @p1_top = [@x1 + (normalx * @r), @y1 + (normaly * @r)]
        @p1_bot = [@x1 - (normalx * @r), @y1 - (normaly * @r)]
        @p2_top = [@x2 + (normalx * @r), @y2 + (normaly * @r)]
        @p2_bot = [@x2 - (normalx * @r), @y2 - (normaly * @r)]
        calculateLength()
        @bounding_box = boundingBox()
    end

    def boundingBox()
        if @x1 > @x2
            left = @x2
            right = @x1
        else
            left = @x1
            right = @x2
        end

        if @y1 > @y2
            bottom = @y2
            top = @y1
        else
            bottom = @y1
            top = @y2
        end
        width = right - left
        height = top - bottom
        # box = {left: left, bottom: bottom, right: right, top: top, width: width, height: height}
        # puts box.to_s
        return {left: left, bottom: bottom, right: right, top: top, width: width, height: height}
    end

    def calculateLength
        @length = (@x2 - @x1) * (@x2 - @x1) + (@y2 - @y1) * (@y2 - @y1)
    end

    def closestPointOnWallTo(x, y)
        # makes wall into line (starting with (@x1, @y1) as (0,0)...probably (I'm tired))
        relative_x1 = @x2 - @x1
        relative_y1 = @y2 - @y1
        relative_x2 = x - @x1
        relative_y2 = y - @y1

        t = [0, [@length, (relative_x1 * relative_x2 + relative_y1 * relative_y2)].min()].max() / @length
        closest_x = @x1 + t * relative_x1
        closest_y = @y1 + t * relative_y1
        return [closest_x, closest_y]
    end

    def draw_override(ffi_draw)
        ffi_draw.draw_sprite(@x1 - @r, @y1 - @r, @d, @d, "sprites/circle/black.png")
        ffi_draw.draw_sprite(@x2 - @r, @y2 - @r, @d, @d, "sprites/circle/black.png")
        ffi_draw.draw_line(@p1_top[0], @p1_top[1], @p2_top[0], @p2_top[1], 0, 0, 0, 255)
        ffi_draw.draw_line(@p1_bot[0], @p1_bot[1], @p2_bot[0], @p2_bot[1], 0, 0, 0, 255)
        # ffi_draw.draw_border(@bounding_box[:left], @bounding_box[:bottom], @bounding_box[:width], @bounding_box[:height], 0, 0, 0, 255)
    end
    
    def serialize
        {x1: @x1, y1: @y1, x2: @x2, y2: @y2}
    end

    def inspect
        serialize.to_s
    end

    def to_s
        return "Wall: (#{@x1}, #{@y1}) to (#{@x2}, #{@y2})"
    end
end
