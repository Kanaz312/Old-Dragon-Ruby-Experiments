$gtk.ffi_misc.gtk_dlopen("ext")
include FFI::RE

def tick args
    init(args) if args.state.tick_count == 0
    # free args if args.inputs.keyboard.key_down.f
    update_sprite(args.state.potion)
    update_sprite(args.state.potion2)
    update_sprite(args.state.potion3)
    update_sprite(args.state.death1)
    update_sprite(args.state.death2)
    update_sprite(args.state.death3)
    update_sprite(args.state.death4)

    args.outputs.primitives << [0, 0, args.state.potion[0].sprite_w, args.state.potion[0].sprite_h, :potion, 0].sprite
    args.outputs.primitives << [200, 0, args.state.potion2[0].sprite_w, args.state.potion2[0].sprite_h, :potion2, 0].sprite
    args.outputs.primitives << [300, 0, args.state.potion3[0].sprite_w, args.state.potion3[0].sprite_h, :potion3, 0].sprite
    args.outputs.primitives << [300, 100, args.state.death1[0].sprite_w, args.state.death1[0].sprite_h, :death1, 0].sprite
    args.outputs.primitives << [700, 100, args.state.death2[0].sprite_w, args.state.death2[0].sprite_h, :death2, 0].sprite
    args.outputs.primitives << [500, 400, args.state.death3[0].sprite_w, args.state.death3[0].sprite_h, :death3, 0].sprite
    args.outputs.primitives << [600, 400, args.state.death4[0].sprite_w, args.state.death4[0].sprite_h, :death4, 0].sprite


    args.outputs.debug << args.gtk.framerate_diagnostics_primitives
    args.outputs.background_color = [200, 200, 200]
    # args.outputs.labels << [0, 720, "framerate: #{args.gtk.current_framerate.to_s}"]
end

def free args
    destroyArray(args.state.noise)
    destroyArray(args.state.pixels)
    $gtk.exit()
end

def init args
    # images changed to be ones I could push publicly
    args.state.potion = make_sprite("sprites/dino.png", "potion", 94, 112, 256, -123)
    args.state.potion2 = make_sprite("sprites/dino.png", "potion2", 94, 112, 256, 9487)
    args.state.potion3 = make_sprite("sprites/dino.png", "potion3", 94, 112, 256, 727192)
    args.state.death1 = make_sprite("sprites/bird.png", "death1", 207, 235, 256, 32342)
    args.state.death2 = make_sprite("sprites/bird.png", "death2", 207, 235, 256, -1348)
    args.state.death3 = make_sprite("sprites/bird.png", "death3", 207, 235, 256, 0)
    args.state.death4 = make_sprite("sprites/bird.png", "death4", 207, 235, 256, 34)

    # args.state.freq = 4
    # args.state.pixels = makePixelArr(args.state.w, args.state.h)
    # args.state.noise = makeNoiseArr(args.state.w, args.state.h)
end