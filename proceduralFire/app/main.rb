$gtk.ffi_misc.gtk_dlopen("ext")
include FFI::RE

class Perlin

    NOISE1 = 0x68e31da4  # 0b 0110'1000'1110'0011'0001'1101'1010'0100
    NOISE2 = 0xb5297a4d  # 0b 1011'0101'0010'1001'0111'1010'0100'1101
    NOISE3 = 0x1b56c4e9  # 0b 0001'1011'0101'0110'1100'0100'1110'1001

    CAP = ~(~0 << 32)

    def initialize()
        arr = Array.new(256) {|i| i}
        arr.shuffle!
        @perm = Array.new(512) {|i| arr[i % 256]} # double the permutation array
    end

    def noise3d(x, y, z)
        # get unit cube for the points (cube x, y, z)
        cubex = x.floor & 0xFF
        cubey = y.floor & 0xFF

        # change to local position relative to unit cube
        x -= cubex
        y -= cubey
        

        # compute fade curves for each of x, y, z (possibly just replace?)
        u = fade(x)
        v = fade(y)

        # get the random values for the corners of the cube
        corn1 = @perm[cubex] + cubey # A
        corn2 = @perm[corn1] # AA
        corn3 = @perm[corn1 + 1] # AB
        corn4 = @perm[cubex + 1] + cubey # B
        corn5 = @perm[corn4] # BA
        corn6 = @perm[corn4 + 1] # BB

        # add blended results from 8 corners of the cube
        return lerp(v, 
            lerp(u, grad3d(@perm[corn2], x, y, z), grad3d(@perm[corn5], x - 1, y, z)),
            lerp(u, grad3d(@perm[corn3], x, y - 1, z), grad3d(@perm[corn6], x - 1, y - 1, z)))
    end

    def grad3d(hash, x, y, z)
        # convert lowest order 4 bits of hash code into 12 gradient directions
        h = hash & 0xF
        u = h < 8 ? x : y
        v = h < 4 ? y : (h == 12 || h == 14 ? x : z)
        return ((h & 0x1) == 0 ? u : -u) + ((h & 0x2) == 0 ? v : -v)
    end 

    def noise2d(x, y)
        # get unit cube for the points (cube x, y, z)
        gridx = x.floor & 0xFF
        gridy = y.floor & 0xFF

        # change to local position relative to unit cube
        x -= x.floor
        y -= y.floor
        

        # compute fade curves for each of x, y, z (possibly just replace?)
        u = fade(x)
        v = fade(y)

        # get hash values for the corners of the square
        a = @perm[gridx] + gridy # A
        aa = @perm[a] # AA
        ab = @perm[a + 1] # AB
        b = @perm[gridx + 1] + gridy # B
        ba = @perm[b] # BA
        bb = @perm[b + 1] # BB

        # add blended results from 4 corners of the square
        return lerp(v, 
            lerp(u, grad2d(@perm[aa], x, y), grad2d(@perm[ba], x - 1, y)),
            lerp(u, grad2d(@perm[ab], x, y - 1), grad2d(@perm[bb], x - 1, y - 1)))
    end

    # def grad2d(hash, x, y)
    #     # convert lowest order 2 bits of hash code into 12 gradient directions
    #     h = hash & 0x3
    #     u = h & 0x2 == 0 ? x : -x # maps hash to either (1, 0) or (-1, 0)
    #     v = h & 0x1 == 0 ? y : -y # detmines signedness e.x. (0, 1) vs (0, -1)
    #     return u + v
    # end 


    def squirrel2d(x, y)
        # get unit cube for the points (cube x, y, z)
        gridx = x.floor 
        gridy = y.floor

        # change to local position relative to unit cube
        x -= x.floor
        y -= y.floor
        

        # compute fade curves for each of x, y, z (possibly just replace?)
        u = fade(x)
        v = fade(y)

        # get hash values for the corners of the square
        # corn1 = squirrel1d(gridx) + gridy
        # corn2 = squirrel1d(gridx) + gridy + 1
        # corn3 = squirrel1d(gridx + 1) + gridy
        # corn4 = squirrel1d(gridx + 1) + gridy + 1
        corn1 = squirrel1d(squirrel1d(gridx) + gridy)
        corn2 = squirrel1d(squirrel1d(gridx) + gridy + 1)
        corn3 = squirrel1d(squirrel1d(gridx + 1) + gridy)
        corn4 = squirrel1d(squirrel1d(gridx + 1) + gridy + 1)

        # add blended results from 4 corners of the square
        return lerp(v, 
            lerp(u, grad2d(corn1, x, y), grad2d(corn3, x  - 1, y)),
            lerp(u, grad2d(corn2, x, y - 1), grad2d(corn4, x - 1, y - 1)))
    end

    # def fade(t)
    #     return t * t * t * (t * (t * 6 - 15) + 10) # 6t^5 - 15t^4 + 10t^3
    # end

    # def lerp(t, a, b)
    #     return a + t * (b - a)
    # end

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

def tick args
    init(args) if args.state.tick_count == 0 
    reset(args) if args.inputs.keyboard.key_down.space
    free args if args.inputs.keyboard.key_down.f
    update_texture(args.state.noise, args.state.pixels, args.state.w, args.state.h, args.state.freq, args.state.step)
    args.outputs.primitives << [550, 150, args.state.w, args.state.h, :noise_texture, 0].sprite
    args.state.step = (args.state.step + 0.01)
    args.outputs.debug << args.gtk.framerate_diagnostics_primitives
    args.outputs.background_color = [150, 150, 150]
    # args.outputs.labels << [0, 720, "framerate: #{args.gtk.current_framerate.to_s}"]
end

def free args
    destroyArray(args.state.noise)
    destroyArray(args.state.pixels)
    $gtk.exit()
end

def reset args
    args.state.w = 300
    args.state.h = 300
    args.state.freq = 4
    destroyArray(args.state.noise)
    destroyArray(args.state.pixels)
    args.state.pixels = makePixelArr(args.state.w, args.state.h)
    args.state.noise = makeNoiseArr(args.state.w, args.state.h)
    args.state.step = 200
end

def init args
    args.state.w = 300
    args.state.h = 300
    args.state.freq = 4
    args.state.pixels = makePixelArr(args.state.w, args.state.h)
    args.state.noise = makeNoiseArr(args.state.w, args.state.h)
    args.state.step = 200
end

def initializePixels args
    args.state.step += 0.01
    step = args.state.step
    perlin = args.state.perlin
    w = args.state.w
    h = args.state.h
    freq = 13
    # args.pixel_array(:noise_texture).width = args.state.w
    # args.pixel_array(:noise_texture).height = args.state.h
    # arr = args.pixel_array(:noise_texture).pixels
    y = 0
    x = 0
    while y < h
        x = 0
        while x < w
            brightness = 128 * (FFI::RE::perlin2d(x / w * freq, (y + step) / h * freq) + 1)
            abgr = 0xFF000000 + ((0x000000FF & brightness) << 16) + ((0x000000FF & brightness) << 8) + (0x000000FF & brightness)
            arr[x + y * h] = abgr
            x += 1
        end 
        y += 1
    end
    # puts args.pixel_array(:noise_texture).pixels
    # args.pixel_array(:noise_texture).pixels.copy(arr)
    # args.pixel_array(:noise_texture).pixels.fill(0xFF00FFFF, 0, w)
end



# def noise3d(x, y, z)
#     # get unit cube for the points (cube x, y, z)
#     cubex = x.floor & 0xFF
#     cubey = y.floor & 0xFF
#     cubez = z.floor & 0xFF

#     # change to local position relative to unit cube
#     x -= cubex
#     y -= cubey
#     z -= cubez
    

#     # compute fade curves for each of x, y, z (possibly just replace?)
#     u = fade(x)
#     v = fade(y)
#     w = fade(z)
    

#     # get the random values for the corners of the cube
#     corn1 = @perm[cubex] + cubey # A
#     corn2 = @perm[corn1] + cubez # AA
#     corn3 = @perm[corn1 + 1] + cubez # AB
#     corn4 = @perm[cubex + 1] + cubey # B
#     corn5 = @perm[corn4] + cubez # BA
#     corn6 = @perm[corn4 + 1] + cubez# BB

#     # add blended results from 8 corners of the cube
#     return lerp(w,
#     lerp(v, 
#         lerp(u, grad3d(@perm[corn2], x, y, z), grad3d(@perm[corn5], x0, y, z)),
#         lerp(u, grad3d(@perm[corn3], x, y - 1, z), grad3d(@perm[corn6], x0, y - 1, z))),
#     lerp(v,
#         lerp(u, grad3d(@perm[corn2 + 1], x, y, z - 1), grad3d(@perm[corn5 + 1], x0, y, z - 1)),
#         lerp(u, grad3d(@perm[corn3 + 1], x, y - 1, z - 1), grad3d(@perm[corn6 + 1], x0, y - 1 , z - 1)))
#     )

# end