class Perlin
    def initialize()
        arr = Array.new(256) {|i| i}
        arr.shuffle!
        @perm = Array.new(512) {|i| arr[i % 256]} # double the permutation array
    end

    def noise3d(x, y, z)
        # get unit cube for the points (cube x, y, z)
        cubex = x.floor & 255
        cubey = y.floor & 255
        cubez = z.floor & 255

        # change to local position relative to unit cube
        x -= cubex
        y -= cubey
        z -= cubez

        # compute fade curves for each of x, y, z (possibly just replace?)
        u = fade(x)
        v = fade(y)
        w = fade(z)

        # get the random values for the corners of the cube
        corn1 = @perm[cubex] + cubey # A
        corn2 = @perm[corn1] + cubez # AA
        corn3 = @perm[corn1 + 1] + cubez # AB
        corn4 = @perm[cubex + 1] + cubey # B
        corn5 = @perm[corn4] + cubez # BA
        corn6 = @perm[corn4 + 1] + cubez# BB

        # add blended results from 8 corners of the cube
        return lerp(w,
            lerp(v, 
                lerp(u, grad3d(@perm[corn2], x, y, z), grad3d(@perm[corn5], x - 1, y, z)),
                lerp(u, grad3d(@perm[corn3], x, y - 1, z), grad3d(@perm[corn6], x - 1, y - 1, z))),
            lerp(v,
                lerp(u, grad3d(@perm[corn2 + 1], x, y, z - 1), grad3d(@perm[corn5 + 1], x - 1, y, z - 1)),
                lerp(u, grad3d(@perm[corn3 + 1], x, y - 1, z - 1), grad3d(@perm[corn6 + 1], x - 1, y - 1 , z - 1)))
            )
    end

    def grad3d(hash, x, y, z)
        # convert lowest order 4 bits of hash code into 12 gradient directions
        h = hash & 15
        u = h < 8 ? x : y
        v = h < 4 ? y : (h == 12 || h == 14 ? x : z)
        return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v)
    end 

    def noise2d(x, y)
        # get unit square for the points (grid x, y)
        gridx = x.floor & 255
        gridy = y.floor & 255

        # change to local position relative to unit cube
        x -= gridx
        y -= gridy

        # compute fade curves for each of x, y
        u = fade(x)
        v = fade(y)

        # get the random values for the corners of the square
        corn1 = @perm[gridx] + gridy # A
        corn2 = @perm[corn1] + gridy # AA
        corn3 = @perm[gridx + 1] + gridy # B
        corn4 = @perm[corn3 + 1] + gridy # BA

        # add blended results from 4 corners of the square
        return lerp(v, 
            lerp(u, grad2d(@perm[corn1], x, y), grad2d(@perm[corn2], x - 1, y)),
            lerp(u, grad2d(@perm[corn3], x, y - 1), grad2d(@perm[corn4], x - 1, y - 1)))
    end

    def grad2d(hash, x, y)
        # convert lowest order 2 bits of hash code into 12 gradient directions
        h = hash & 3
        u = h & 2 == 0 ? x : -x # maps hash to either (1, 0) or (-1, 0)
        v = h & 1 == 0 ? y : -y # detmines signedness e.x. (0, 1) vs (0, -1)
        return u + v
    end 

    def fade(t)
        return t * t * t * (t * (t * 6 - 15) + 10) # 6t^5 - 15t^4 + 10t^3
    end

    def lerp(t, a, b)
        return a + t * (b - a)
    end

    def serialize
        instance_variables.map do |key|
          [key.to_s[1..-1].to_sym, instance_variable_get(key)]
        end.to_h
    end
    
    def inspect
        serialize.to_s
    end
    
    def to_s
        serialize.to_s
    end
end

class Flow
    def initialize (x, y, w, h, cell_size)
        @x = x
        @y = y
        @w = w
        @h = h
        @path = "sprites/arrow30.png"
        @cell_size = cell_size
        initializeFlow
    end

    def initializeFlow
        @perlin = Perlin.new
        @flow = Array.new(@w * @h)
        @zt = 50.6
        @xt = 40.3
        @yt = 60.7
        @h.times do |y|
            @w.times do |x|
                hash = Hash.new()
                angle = @perlin.noise3d(x / @w, y / @h, @zt)
                # angle = -Math::PI
                hash[:angle] = angle * 180
                angle = angle * Math::PI
                hash[:x] = Math.cos(angle)
                hash[:y] = Math.sin(angle)
                @flow[x + y * @h] = hash
            end
        end
        @t = 0
        @frequency = 1
    end
    
    def updateFlow keyboard
        @xt += keyboard.left_right * 0.1
        @yt += keyboard.up_down * 0.1
        @zt += 0.1 if keyboard.key_held.i
        @zt -= 0.1 if keyboard.key_held.k
        if keyboard.left_right != 0 || keyboard.up_down != 0 || keyboard.key_held.i || keyboard.key_held.k
            scroll
        end
    end

    def scroll
        @h.times do |y|
            @w.times do |x|
                hash = @flow[x + y * @h]
                angle = (@perlin.noise3d((x + @xt) / @w * @frequency, (y + @yt) / @h * @frequency, @zt) + 1) * Math::PI
                hash[:angle] = angle * 180
                angle = angle * Math::PI
                hash[:x] = Math.cos(angle)
                hash[:y] = Math.sin(angle)
            end
        end
    end

    def getForce(x, y)
        x = ((x - @x) / @cell_size).floor
        y = ((y- @y) / @cell_size).floor
        return @flow[x + y * @h]
    end

    def draw_override(ffi_draw)
        i = 0
        while i < @w
            j = 0
            while j < @h
                ffi_draw.draw_sprite_3(
                    @x + i * @cell_size, @y + j * @cell_size, @cell_size, @cell_size, 
                    @path, @flow[i + j * @h][:angle],
                    100, nil, nil, nil,
                    nil, nil, nil, nil,
                    false, false,
                    0.5, 0.5,
                    nil, nil, nil, nil)
                j += 1
            end
            i += 1
        end
    end
end