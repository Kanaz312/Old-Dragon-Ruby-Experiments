class PerlinNoise
    attr_accessor :noise_map
  
    def initialize(res, pixel, factor: [0.05, 0.05], mode: 'smooth', vectors: 'random')
      @noise_map = []
      @res = res
      @pixel = pixel
      @factor = factor
      @mode = mode
      @vectors = vectors
      render_sections
    end
  
    def render_sections
      @res[0].times { |x| render_column(x) }
    end
  
    def render_column(x)
      @res[1].times do |y|
        @noise_map << [x * @pixel[0], y * @pixel[1], @pixel[0], @pixel[1],
                       grey(perlin(x * @factor[0], y * @factor[1]))]
      end
    end
  
    def perlin(x, y)
      xi = x.to_i
      yi = y.to_i
      interpolate(calc(xi, 1 + xi, yi, x, y), calc(xi, 1 + xi, 1 + yi, x, y), y - yi, @mode)
    end
  
    def interpolate(a0, a1, w, type = '')
      case type
      when 'linear' then (1 - w) * a0 + w * a1
      when 'smooth' then w**2 * (3 - 2 * w) * (a1 - a0) + a0
      else (a0 + a1) * w
      end
    end
  
    def calc(x1, x2, y1, x, y)
      interpolate(dot_product(x1, y1, x, y), dot_product(x2, y1, x, y), x - x1, @mode)
    end
  
    def dot_product(ix, iy, x, y)
      (x - ix) * vecs(ix, iy, @vectors).value(0) + (y - iy) * vecs(ix, iy, @vectors).value(1)
    end
  
    def vecs(ix, iy, type = '')
      return [Math.cos(ix * iy), Math.sin(ix * iy)] unless type == 'random'
  
      random = 2920 * Math.sin(ix * 21_942 + iy * 171_324 + 8912) *
               Math.cos(ix * 23_157 * iy * 217_832 + 9758)
      [Math.cos(random), Math.sin(random)]
    end
  
    def grey(val)
      level = (val * 127 + 127).to_i
      [level, level, level]
    end
  end
  
  $perlin = PerlinNoise.new([50, 50], [1, 1], factor: [0.1, 0.1], mode: 'smooth')
  $map = $perlin.noise_map
  
  def tick(args)
    $perlin.render_sections
    # args.render_target(:perlin_noise).solids << $map if args.state.tick_count.zero?
    # args.sprites << [0, 0, 1280, 720, :perlin_noise]
    args.outputs.debug << args.gtk.framerate_diagnostics_primitives
  end