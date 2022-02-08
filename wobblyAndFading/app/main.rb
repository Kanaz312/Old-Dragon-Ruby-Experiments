$gtk.ffi_misc.gtk_dlopen("ext")
include FFI::RE

def tick args
    init(args) if args.state.tick_count == 0
    free args if args.inputs.keyboard.key_down.f

    if (args.state.death1_step > 1.3 || args.state.death1_step < -0.2)
        args.state.death1_step_add = -args.state.death1_step_add
    end
    args.state.death1_step += args.state.death1_step_add

    if (args.state.death2_step > 1.3 || args.state.death2_step < -0.2)
        args.state.death2_step_add = -args.state.death2_step_add
    end
    args.state.death2_step += args.state.death2_step_add

    if (args.state.death3_step > 1.3 || args.state.death3_step < -0.2)
        args.state.death3_step_add = -args.state.death3_step_add
    end
    args.state.death3_step += args.state.death3_step_add

    if (args.state.death4_step > 1.3 || args.state.death4_step < -0.2)
        args.state.death4_step_add = -args.state.death4_step_add
    end
    args.state.death4_step += args.state.death4_step_add

    args.state.slime1_step += 0.03
    
    dissolveFromTextureShader(args.state.death1, args.state.death_img, args.state.squish_img, 0xFF9F5F5F, args.state.death1_step)
    wipeShader(args.state.death2, args.state.death_img, args.state.spiral_img, args.state.death2_step)
    wipeShader(args.state.death3, args.state.death_img, args.state.polar_img, args.state.death3_step)
    dissolveShader(args.state.death4, args.state.death_img, args.state.death4_noise, 0xFF3F8F3F, args.state.death4_step)
    horizWaveShader(args.state.slime1, args.state.slime_img, args.state.slime1_step, 0.05)

    args.outputs.primitives << [300, 100, args.state.death1[0].w, args.state.death1[0].h, :death1, 0].sprite
    args.outputs.sprites << [100, 100, 200, 200, "sprites/squish_dissolve.png"]
    args.outputs.primitives << [800, 100, args.state.death2[0].w, args.state.death2[0].h, :death2, 0].sprite
    args.outputs.sprites << [1000, 100, 200, 200, "sprites/spiral.png"]
    args.outputs.primitives << [800, 400, args.state.death3[0].w, args.state.death3[0].h, :death3, 0].sprite
    args.outputs.sprites << [1000, 400, 200, 200, "sprites/polar_wipe.png"]
    args.outputs.primitives << [300, 400, args.state.death4[0].w, args.state.death4[0].h, :death4, 0].sprite
    args.outputs.sprites << [100, 400, 200, 200, :noise]
    args.outputs.primitives << [600, 400, args.state.slime1[0].w, args.state.slime1[0].h, :slime1, 0].sprite

    args.outputs.debug << args.gtk.framerate_diagnostics_primitives
    args.outputs.background_color = [200, 200, 200]
    # args.outputs.labels << [0, 720, "framerate: #{args.gtk.current_framerate.to_s}"]
end

def free args
    destoryNoise(args.state.death1_noise)
    destroyShaderSprite(args.state.death1)
    destroyTexture(args.state.death_img)
    $gtk.exit()
end


def init args
    args.state.death_img = loadColorTexture("sprites/dino.png")
    args.state.death1_noise = makeSeamlessNoiseArr(256, 256, 8, 0.25, 256357, 22)
    args.state.death1 = makeShaderSprite("death1", 207, 235)
    args.state.death1_step = 0
    args.state.death1_step_add = 0.01

    args.state.death2 = makeShaderSprite("death2", 207, 235)
    args.state.death2_step = 0
    args.state.death2_step_add = 0.01

    args.state.death3 = makeShaderSprite("death3", 207, 235)
    args.state.death3_step = 0
    args.state.death3_step_add = 0.02

    args.state.death4 = makeShaderSprite("death4", 207, 235)
    args.state.death4_noise = makeSeamlessNoiseArr(256, 256, 8, 0.25, 912381, 8)
    normalizePerlin(args.state.death4_noise)
    args.state.death4_step = 0
    args.state.death4_step_add = 0.01

    args.state.slime_img = loadColorTexture("sprites/bird.png")
    args.state.slime1 = makeShaderSprite("slime1", 116, 101)
    args.state.slime1_step = 256

    args.state.spiral_img = loadColorTexture("sprites/spiral.png")
    args.state.polar_img = loadColorTexture("sprites/polar_wipe.png")
    args.state.squish_img = loadColorTexture("sprites/squish_dissolve.png")
    args.state.noise_sprite = makeShaderSprite("noise", 200, 200)
    displayNoise(args.state.noise_sprite, args.state.death4_noise, 0)
end