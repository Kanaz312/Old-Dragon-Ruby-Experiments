require "classes/flow.rb"
require "classes/colliders.rb"
require "classes/entities.rb"
require "classes/terrain.rb"
require "classes/hash.rb"
require "classes/physics.rb"


class Object
    def log *args
      GTK::Log.puts(*args)
    end
end

def tick args
    if args.state.tick_count == 0
        args.state.held_ball = nil
        args.state.launch = false
        args.state.subdivisions = 4
        args.state.sim_time = 1 / (60 * args.state.subdivisions)
        args.state.max_steps = 15
        args.state.balls = []
        args.state.walls = []
        args.state.new_wall_coords = []
        args.state.spatial_hash = SpatialHash.new(1280, 720)
        args.state.collision_engine = CollisionEngine.new(args.state.spatial_hash)
        # 1.times do |i|
        #     ball = Entity.new()
        #     args.state.balls << ball
        #     args.outputs.static_sprites << ball
        # end
        flow = Flow.new(0, 0, 42, 42, 30)
        args.outputs.static_sprites << flow
        args.state.flow = flow
    end
    mouseAction args.inputs.mouse, args

    if args.inputs.keyboard.key_down.space
        ball = Entity.new()
        args.state.balls << ball
        args.outputs.static_sprites << ball
    end
    args.state.flow.updateFlow args.inputs.keyboard
    # move balls

    args.state.subdivisions.times do |i|
        args.state.balls.each do |ball|
            ball.sim_time = args.state.sim_time
        end
        args.state.max_steps.times do |j|
            args.state.balls.each do |ball|
                flow_force = args.state.flow.getForce(ball.collider.x, ball.collider.y)
                ball.update args.state.spatial_hash, flow_force
            end
            args.state.collision_engine.handleCollisions(args)
        end
    end
    args.outputs.debug << args.gtk.framerate_diagnostics_primitives
    args.outputs.labels << [0, 20, "framerate: #{args.gtk.current_framerate.to_s}"]
    # args.outputs.debug << args.state.spatial_hash
end

def mouseAction mouse, args

    if mouse.down
        args.state.balls.each do |ball|
            if ball.collider.mouseInside(mouse)
                args.state.held_ball = ball
                args.state.launch = mouse.button_left ? false : true
                break
            end
        end
        args.state.walls.each do |wall|
            if wall.mouseOnCircle?(mouse.x, mouse.y)
                args.state.held_wall = wall
                box = args.state.held_wall.boundingBox
                args.state.spatial_hash.deleteBoundingBox(box[:left], box[:bottom], box[:right], box[:top], wall)
                break
            end
        end
    elsif args.state.held_ball && mouse.up
        if args.state.launch
            ball = args.state.held_ball
            ball.x_vel = 0.5  * (ball.collider.x - mouse.x)
            ball.y_vel = 0.5 * (ball.collider.y - mouse.y)
            args.state.launch = false
        end
        args.state.held_ball = nil
    elsif args.state.held_wall != nil && mouse.up
        box = args.state.held_wall.boundingBox
        args.state.spatial_hash.insertBoundingBox(box[:left], box[:bottom], box[:right], box[:top], args.state.held_wall)
        args.state.held_wall = nil
    end

    if mouse.button_middle && mouse.down
        if args.state.new_wall_coords.length == 0
            args.state.new_wall_coords = [mouse.x, mouse.y]
        else
            wall = Wall.new(args.state.new_wall_coords[0], args.state.new_wall_coords[1], mouse.x, mouse.y)
            args.outputs.static_sprites << wall
            args.state.walls << wall
            box = wall.boundingBox
            args.state.spatial_hash.insertBoundingBox(box[:left], box[:bottom], box[:right], box[:top], wall)
            args.state.new_wall_coords = []
        end
    end
    if args.state.held_ball
        if args.state.launch
            args.outputs.lines << [args.state.held_ball.collider.x, args.state.held_ball.collider.y, mouse.x, mouse.y, 0, 255, 0]
        else
            # args.state.spatial_hash.deleteBoundingBox(ball.x, ball.y, ball.x + ball.w, ball.y + ball.h, ball)
            args.state.held_ball.moveCenterTo(mouse.x, mouse.y)
            # args.state.spatial_hash.insertBoundingBox(ball.x, ball.y, ball.x + ball.w, ball.y + ball.h, ball)
        end
    elsif args.state.held_wall != nil
        args.state.held_wall.moveToMouse(mouse.x, mouse.y)
    end
end