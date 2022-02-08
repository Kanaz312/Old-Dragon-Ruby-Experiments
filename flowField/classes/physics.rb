class CollisionEngine

    def initialize(spatial_hash)
        @collision_pairs = Hash.new
        @spatial_hash = spatial_hash
    end

    def handleCollisions(args)
        handleStaticCollisions(args.state.balls, args)
        handleDynamicCollisions(args)
        @collision_pairs.clear
    end

    def handleStaticCollisions(balls, args)
        i = 0
        walls = []
        while i < balls.length
            ball = balls[i]
            j = i + 1
            while j < balls.length # this is the slowdown, how should I go about reducing the number of checks
                staticBallAndBall(balls[j], ball)
                j += 1
            end
            @spatial_hash.queryBox(ball.x, ball.y, ball.x + ball.w, ball.y + ball.h, walls)
            walls.each do |wall|
                wallAndBall(wall, ball)
            end
            i += 1
            walls.clear
        end
    end
    
    def handleDynamicCollisions(args)
        @collision_pairs.each do |ball, other|
            dist = pythagorean(ball.collider.x, ball.collider.y, other.collider.x, other.collider.y)
            normx = (other.collider.x - ball.collider.x) / dist
            normy = (other.collider.y - ball.collider.y) / dist
            tanx = -normy
            tany = normx
    
            kx = (ball.x_vel - other.x_vel)
            ky = (ball.y_vel - other.y_vel)
            p = 2.0 * (normx * kx + normy * ky) / (ball.mass + other.mass)
            ball.x_vel = ball.x_vel - p * other.mass * normx
            ball.y_vel = ball.y_vel - p * other.mass * normy
            other.x_vel = other.x_vel + p * ball.mass * normx
            other.y_vel = other.y_vel + p * ball.mass * normy
        end
    end

    def wallAndBall(wall, ball)
        ball_collider = ball.collider
        closest_point = wall.closestPointOnWallTo(ball_collider.x, ball_collider.y)
        dist = pythagorean(ball_collider.x, ball_collider.y, closest_point[0], closest_point[1])
        if dist <= ball.collider.r + wall.r
            fake_ball = Entity.new(false, closest_point[0], closest_point[1], wall.r, ball.mass, -ball.x_vel, -ball.y_vel)
            dist = pythagorean(ball_collider.x, ball_collider.y, fake_ball.collider.x, fake_ball.collider.y)
            overlap = dist - ball_collider.r - fake_ball.collider.r
            
            #displace current ball
            delta_x = overlap * (ball_collider.x - fake_ball.collider.x) / dist
            delta_y = overlap * (ball_collider.y - fake_ball.collider.y) / dist
            ball.moveBy(-delta_x, -delta_y)

            # @collision_pairs << [ball, fake_ball, dist]
            @collision_pairs.store(ball, fake_ball)
        end
    end

    def staticBallAndBall(other, ball)
        ball_collider = ball.collider
        other_collider = other.collider
        if ball != other && overlapCircles?(ball_collider.x, ball_collider.y,
            ball_collider.r, other_collider.x, other_collider.y, other_collider.r)

            
            dist = pythagorean(ball_collider.x, ball_collider.y, other_collider.x, other_collider.y)
            overlap = 0.5 * (dist - ball_collider.r - other_collider.r)

            #displace current ball
            delta_x = overlap * (ball_collider.x - other_collider.x) / dist
            delta_y = overlap * (ball_collider.y - other_collider.y) / dist
            ball.moveBy(-delta_x, -delta_y)

            #displace other ball
            other.moveBy(delta_x, delta_y)

            # @collision_pairs << [ball, other, dist + overlap]
            @collision_pairs.store(ball, other)
        end
    end

    def overlapCircles? x1, y1, r1, x2, y2, r2
        return ((x1 - x2) * (x1 - x2)) + ((y1 - y2) * (y1 - y2)) < (r1 + r2) * (r1 + r2) - 0.001
    end
    
    def pythagorean x1, y1, x2, y2
        return Math.sqrt(((x1 - x2) * (x1 - x2)) + ((y1 - y2) * (y1 - y2)))
    end

    def serialize
        {pairs: @collision_pairs}
    end

    def inspect
        serialize.to_s
    end

    def to_s
        return "Collision Enginge: pairs #{@collision_pairs}"
    end
end