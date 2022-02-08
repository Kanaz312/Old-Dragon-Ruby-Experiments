class Entity
    FRICTION_MULTIPLIER = 0.1
    CIRCLE_COLORS = ["black", "blue", "gray", "green", "indigo", "orange", "red", "violet", "white", "yellow"]
    attr_sprite
    attr_accessor :x_vel, :y_vel, :mass, :collider, :sim_time, :old_x, :old_y
    def initialize(randomize=true, x=0, y=0, radius=0, mass=0, x_vel=0, y_vel=0)
        if randomize
            radius = 10 + rand(25)
            @x = radius + rand(1280 - (radius * 2))
            @y = radius + rand(720 - (radius * 2))
            @collider = CircleCollider.new(@x + radius, @y + radius, radius)
            @mass = Math::PI * radius * radius
            @x_vel = 0
            @y_vel = 0
        else
            @x = x - radius
            @y = y - radius
            @collider = CircleCollider.new(x, y, radius)
            @mass = mass
            @x_vel = x_vel
            @y_vel = y_vel
        end
        @w = radius * 2
        @h = radius * 2
        @x_accel = 0
        @y_accel = 0
        @path = "sprites/circle/#{CIRCLE_COLORS[rand(10)]}.png"
        @sim_time = 0
        @old_x = @x
        @old_y = @y
    end

    def update spatial_hash, flow_force
        if @sim_time > 0
            # spatial_hash.deleteBoundingBox(@x, @y, @x + @w, @y + @h, self)
            @old_x = @collider.x
            @old_y = @collider.y

            # apply flow force
            @x_vel += flow_force[:x] * 3 * @sim_time
            @y_vel += flow_force[:y] * 3 * @sim_time

            # apply friciton
            # @x_accel = -@x_vel * FRICTION_MULTIPLIER 
            # @y_accel = -@y_vel * FRICTION_MULTIPLIER 

            @x_vel += @x_accel * @sim_time
            @y_vel += @y_accel * @sim_time
            # @x_vel = 0
            # @y_vel =0

            @x_vel = (@x_vel).abs > 20 ? 20 * @x_vel / @x_vel.abs : @x_vel
            @y_vel = (@y_vel).abs > 20 ? 20 * @y_vel / @y_vel.abs : @y_vel
            # @x_vel = (@x_vel).abs > 0.03 ? @x_vel : 0
            # @y_vel = (@y_vel).abs > 0.03 ? @y_vel : 0
            moveBy(@x_vel * @sim_time, @y_vel * @sim_time)

            new_x = @x
            new_y = @y
            if @x < 0
                new_x = 1280 - @w + @x
            elsif @x > 1280 - @w
                new_x = @x - (1280 - @w)
            end

            if @y < 0
                new_y = 720 - @h + @y
            elsif @y > 720 - @h
                new_y = @y - (720 - @h)
            end

            moveCenterTo(new_x + @collider.r, new_y + @collider.r)
            # spatial_hash.insertBoundingBox(@x, @y, @x + @w, @y + @h, self)
        end
    end

    def moveBy(delta_x, delta_y)
        @x += delta_x
        @y += delta_y
        @collider.x += delta_x
        @collider.y += delta_y
    end

    def moveCenterTo(x, y)
        @x = x - @collider.r
        @y = y - @collider.r
        @collider.x = x
        @collider.y = y
    end

    def draw_override(ffi_draw)
        ffi_draw.draw_sprite(@x, @y, @w, @h, @path)
        # ffi_draw.draw_border(@x, @y, @w, @h, 0, 0, 0, 255)
    end

    def serialize
        {x: @x, y: @y, w: @w, h: @h, path: @path, mass: @mass}
    end

    def inspect
        serialize.to_s
    end

    def to_s
        return "Entity: #{@x}, #{@y}, #{@path}"
    end
end