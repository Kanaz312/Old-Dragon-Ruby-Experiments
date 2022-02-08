class SpatialHash

    def initialize(w, h)
        @cell_size = 100
        cols = (w / @cell_size).ceil
        rows = (h / @cell_size).ceil
        @cols = cols
        @rows = rows
        @contents = []
        rows.times do |row|
            row = []
            cols.times do |col|
                row << Hash.new
            end
            @contents << row
        end
    end

    def primitive_marker
        return :line
    end

    def outputRanges(left, bottom, right, top, args)
        args.outputs.labels << [100, 80, "x: #{(left / @cell_size).floor..(right / @cell_size).floor} y: #{(bottom / @cell_size).floor..(top / @cell_size).floor}"]
    end

    def insertPoint(x, y, object)
        @contents[(y / @cell_size).floor][(x / @cell_size).floor] << object
    end

    def insertBoundingBox(left, bottom, right, top, object)
        x = (left / @cell_size).floor
        y_start_value = (bottom / @cell_size).floor
        max_x = (right / @cell_size).floor
        max_y = (top / @cell_size).floor
        while x <= max_x
            y = y_start_value
            while y <= max_y
                (@contents[y][x]).store(object, object)
                y += 1
            end
            x += 1
        end
    end

    def queryBox(left, bottom, right, top, objects)
        x = (left / @cell_size).floor
        y_start_value = (bottom / @cell_size).floor
        max_x = (right / @cell_size).floor
        max_y = (top / @cell_size).floor
        while x <= max_x
            y = y_start_value
            while y <= max_y
                (@contents[y][x]).each_value {|object| objects << object}
                y += 1
            end
            x += 1
        end
    end

    def deletePoint(x, y, object)
        (@contents[y][x]).delete(object)
    end

    def deleteBoundingBox(left, bottom, right, top, object)
        x = (left / @cell_size).floor
        y_start_value = (bottom / @cell_size).floor
        max_x = (right / @cell_size).floor
        max_y = (top / @cell_size).floor
        while x <= max_x
            y = y_start_value
            while y <= max_y
                (@contents[y][x]).delete(object)
                y += 1
            end
            x += 1
        end
    end
    
    def serialize
        {cell_size: @cell_size}
    end

    def inspect
        serialize.to_s
    end

    def to_s
        return "Spatial Hash: #{@cell_size}"
    end

    def draw_override(ffi_draw)
        @contents.length.times do |row|
            @contents[row].length.times do |col|
                if @contents[row][col].length != 0
                    ffi_draw.draw_border(col * @cell_size, row * @cell_size, @cell_size, @cell_size, 0, 255, 0, 255)
                else
                    ffi_draw.draw_border(col * @cell_size, row * @cell_size, @cell_size, @cell_size, 255, 0, 0, 255)
                end
            end
        end
    end
end

