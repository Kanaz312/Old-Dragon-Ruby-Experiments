#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "ext.h"

double clamp(double val, double min, double max);
extern void *(*drb_symbol_lookup)(const char *sym);
typedef void (*drb_upload_pixel_array_fn)(const char *name, const int w, const int h, const Uint32 *pixels);
typedef void *(*drb_load_image_fn)(const char *fname, int *w, int *h);

/* returns an array of perlin noise values size w * h that is tileable (wraps)
 * octaves is the number of octaves that should be summed
 * persistence is how much each subsequent octave should affect the final result
 *   generally this should be less than 1 (0.4 is nice imo)
 * end_freq is the final frequency you want (higher means more detail)
 */
NoiseArray *makeSeamlessNoiseArr(int w, int h, int octaves, double persistence, int seed, int end_freq)
{
    double x, y, work_freq, amplitude, total, max, value, *arr;
    int i, j;
    NoiseArray *noise;
    if (NULL == (arr = malloc(w * h * sizeof(double))))
    {
        fprintf(stderr, "Malloc fail in file:%s line: %d\n", __FILE__, __LINE__);
        fflush(stderr);
        exit(EXIT_FAILURE);
    }
    
    for (i = 0; i < w * h; i++)
    {
        x = (i % w) * end_freq / (double) w;
        y = floor(i / (double) h) * end_freq / (double) h;

        /* the working frequency (unrelated to the end result frequency) */
        work_freq = 1;
        amplitude = 1;
        total = 0;
        max = 0;
        
        /* uncomment to make some darker areas */
        total += seamlessPerlin2d(x * work_freq, y * work_freq, seed, work_freq * end_freq) * amplitude;
        max += amplitude;

        /* sums perlin noise for each octave (shrinking amplitude by persistence) */
        for (j = 0; j < octaves; j++)
        {
            total += seamlessPerlin2d(x * work_freq, y * work_freq, seed, work_freq * end_freq) * amplitude;
            max += amplitude;
            amplitude *= persistence;
            work_freq *= 2;
        }

        /* gets the perlin [-1, 1] value*/
        value = (total / max);
        /* sets array value to range [-1, 1] */
        arr[i] = clamp(value, -1, 1);
        // arr[i] = seamlessPerlin2d(x, y, seed, end_freq);
    }

    if (NULL == (noise = malloc(sizeof(NoiseArray))))
    {
        fprintf(stderr, "Malloc fail in file:%s line: %d\n", __FILE__, __LINE__);
        fflush(stderr);
        exit(EXIT_FAILURE);
    }

    noise->values = arr;
    noise->w = w;
    noise->h = h;
    return noise;
}

void normalizePerlin(NoiseArray *noise)
{
    int i, max = noise->w * noise->h;
    for (i = 0; i < max; i++)
    {
        (noise->values)[i] = ((noise->values)[i] + 1) * 0.5;
    }
}

void destoryNoise(NoiseArray *noise)
{
    free(noise->values);
    free(noise);
}

void destroyArray(void *arr)
{
    free(arr);
}

unsigned int squirrel1d(int posx, unsigned int seed)
{
    unsigned int mangled_bits = (unsigned int) posx;
    mangled_bits *= BIT_NOISE1;
    mangled_bits += seed;
    mangled_bits ^= mangled_bits >> 8;
    mangled_bits += BIT_NOISE2;
    mangled_bits ^= mangled_bits << 8;
    mangled_bits *= BIT_NOISE3;
    mangled_bits ^= mangled_bits >> 8;
    return mangled_bits;
}

unsigned int squirrel2d(int posx, int posy, unsigned int seed)
{
   return squirrel1d(posx + (PRIME * posy), seed);
}

double fade(double t)
{
    return t * t * t * (t * (t * 6 - 15) + 10);
}

double lerp(double t, double a, double b)
{
        return a + t * (b - a);
}

double grad2d(int hash, double x, double y)
{
    hash = hash & 0x3;
    // double u = (hash & 0x2) == 0 ? x : -x; // maps hash to either (1, 0) or (-1, 0)
    // double v = (hash & 0x1) == 0 ? y : -y; // detmines signedness e.x. (0, 1) vs (0, -1)
    // return u + v;
    return ((hash & 0x2) == 0 ? x : -x) + ((hash & 0x1) == 0 ? y : -y);
}

double perlin2d(double x, double y, int seed)
{
    // get unit cube for the points (cube x, y, z)
    int gridx = floor(x);
    int gridy = floor(y);

    // change to local position relative to unit cube
    x -= gridx;
    y -= gridy;
    

    // compute fade curves for each of x, y, z (possibly just replace?)
    double u = fade(x);
    double v = fade(y);

    // get hash values for the corners of the square
    int corn1 = squirrel1d(squirrel1d(gridx, seed) + gridy, seed);
    int corn2 = squirrel1d(squirrel1d(gridx, seed) + gridy + 1, seed);
    int corn3 = squirrel1d(squirrel1d(gridx + 1, seed) + gridy, seed);
    int corn4 = squirrel1d(squirrel1d(gridx + 1, seed) + gridy + 1, seed);
    

    // add blended results from 4 corners of the square
    return lerp(v, 
        lerp(u, grad2d(corn1, x, y), grad2d(corn3, x  - 1, y)),
        lerp(u, grad2d(corn2, x, y - 1), grad2d(corn4, x - 1, y - 1)));
}

double seamlessPerlin2d(double x, double y, int seed, int freq)
{
    // get unit cube for the points (cube x, y, z)
    int gridx0 = (int) floor(x);
    int gridy0 = (int) floor(y);
    int gridx1 = (gridx0 + 1) % freq;
    int gridy1 = (gridy0 + 1) % freq;

    // change to local position relative to unit cube
    x -= gridx0;
    y -= gridy0;
    

    // compute fade curves for each of x, y, z (possibly just replace?)
    double u = fade(x);
    double v = fade(y);

    // get hash values for the corners of the square
    int corn1 = squirrel1d(squirrel1d(gridx0, seed) + gridy0, seed);
    int corn2 = squirrel1d(squirrel1d(gridx0, seed) + gridy1, seed);
    int corn3 = squirrel1d(squirrel1d(gridx1, seed) + gridy0, seed);
    int corn4 = squirrel1d(squirrel1d(gridx1, seed) + gridy1, seed);
    

    // add blended results from 4 corners of the square
    return lerp(v, 
        lerp(u, grad2d(corn1, x, y), grad2d(corn3, x  - 1, y)),
        lerp(u, grad2d(corn2, x, y - 1), grad2d(corn4, x - 1, y - 1)));
}

double clamp(double val, double min, double max)
{
    return val < min ? min : (val > max ? max : val);
}

double mix(double x, double y, double a)
{
    double val = x * a + (1 - a) * y;
    return clamp(val, x, y);
}

Color *uintArrayToColorArray(Uint32 *original, int w, int h)
{
    int i, uint_color;
    Color *color_array, color;
    if (NULL == (color_array = malloc(w * h * sizeof(Color))))
    {
        fprintf(stderr, "Malloc fail in file:%s line: %d\n", __FILE__, __LINE__);
        fflush(stderr);
        exit(EXIT_FAILURE);
    }
    
    for (i = 0; i < w * h; i++)
    {
        uint_color = original[i];
        color.r = (uint_color & 0xFF) / (double) 256;
        color.g = ((uint_color >> 8) & 0xFF) / (double) 256;
        color.b = ((uint_color >> 16) & 0xFF) / (double) 256;
        color.a = ((uint_color >> 24) & 0xFF) / (double) 256;
        color_array[i] = color;
    }

    return color_array;
}

Texture *loadColorTexture(char *path)
{
    static drb_load_image_fn drb_load_image = NULL;
    Uint32 *uint_source;
    Color *source;
    Texture *texture;
    int w, h;

    if (!drb_load_image) 
    {
        drb_load_image = drb_symbol_lookup("drb_load_image");
    }

    if (drb_load_image) 
    {
        uint_source = (Uint32 *) drb_load_image(path, &w, &h);
        if(uint_source == NULL)
        {
            fprintf(stderr, "drb_load_image fail in file:%s line: %d\n", __FILE__, __LINE__);
            fflush(stderr);
            exit(EXIT_FAILURE); // sadge
        }
        source = uintArrayToColorArray(uint_source, w, h);
    }

    texture = malloc(sizeof(Texture));
    if (texture == NULL)
    {
        fprintf(stderr, "Malloc fail in file:%s line: %d\n", __FILE__, __LINE__);
        fflush(stderr);
        exit(EXIT_FAILURE);
    }
    texture->pixels = source;
    texture->w = w;
    texture->h = h;
    return texture;
}

ShaderSprite *makeShaderSprite(char *sprite_symbol, int sprite_w, int sprite_h)
{
    char *symbol;
    Uint32 *pixels;
    ShaderSprite *sprite;
    
    sprite = malloc(sizeof(ShaderSprite));
    if (sprite == NULL)
    {
        fprintf(stderr, "Malloc fail in file:%s line: %d\n", __FILE__, __LINE__);
        fflush(stderr);
        exit(EXIT_FAILURE);
    }

    pixels = malloc(sprite_w * sprite_h * sizeof(Uint32));
    if (pixels == NULL)
    {
        fprintf(stderr, "Malloc fail in file:%s line: %d\n", __FILE__, __LINE__);
        fflush(stderr);
        exit(EXIT_FAILURE);
    }

    symbol = malloc(strlen(sprite_symbol) + 1);
    if (symbol == NULL)
    {
        fprintf(stderr, "Malloc fail in file:%s line: %d\n", __FILE__, __LINE__);
        fflush(stderr);
        exit(EXIT_FAILURE);
    }
    strcpy(symbol, sprite_symbol);

    sprite->pixels = pixels;
    sprite->w = sprite_w;
    sprite->h = sprite_h;
    sprite->symbol = symbol;

    return sprite;
}

void changeSymbol(ShaderSprite *sprite, char *symbol)
{
    char *new_symbol;
    free(sprite->symbol);

    new_symbol = malloc(strlen(symbol) + 1);
    if (new_symbol == NULL)
    {
        fprintf(stderr, "Malloc fail in file:%s line: %d\n", __FILE__, __LINE__);
        fflush(stderr);
        exit(EXIT_FAILURE);
    }
    strcpy(new_symbol, symbol);
    sprite->symbol = new_symbol;
}

void destroyTexture(Texture *texture)
{
    free(texture->pixels);
    free(texture);
}

void destroyShaderSprite(ShaderSprite *sprite)
{
    free(sprite->pixels);
    free(sprite->symbol);
    free(sprite);
}

void multiplyColorByScalar(Color *color, double scalar)
{
    color->r *= scalar;
    color->g *= scalar;
    color->b *= scalar;
    color->a *= scalar;
}

Color multiplyColors(Color a, Color b)
{
    Color result;
    result.r = a.r * b.r;
    result.g = a.g * b.g;
    result.b = a.b * b.b;
    result.a = a.a * b.a;
    return result;
}

Color sumColors(Color a, Color b)
{
    Color result;
    result.r = a.r + b.r;
    result.g = a.g + b.g;
    result.b = a.b + b.b;
    result.a = a.a + b.a;
    return result;
}

Uint32 colorToUint(Color color)
{
    Uint32 r, g, b, a;
    r = floor(clamp(color.r, 0, 1) * 255);
    g = floor(clamp(color.g, 0, 1) * 255);
    b = floor(clamp(color.b, 0, 1) * 255);
    a = floor(clamp(color.a, 0, 1) * 224);
    return (r + (g << 8) + (b << 16) + (a << 24));
}

void displayNoise(ShaderSprite *sprite, NoiseArray *noise, double step)
{
    static drb_upload_pixel_array_fn drb_upload_pixel_array = NULL;
    int x, y, w = sprite->w, h = sprite->h,
        noise_x, noise_y, noise_size = noise->w;
    Uint32 grey, *pixels = sprite->pixels;
    double u, v, value, *noise_values = noise->values;

    if (!drb_upload_pixel_array) {
        drb_upload_pixel_array = drb_symbol_lookup("drb_upload_pixel_array");
        if (!drb_upload_pixel_array) {
            return;  // oh well.
        }
    }

    for (y = 0; y < h; y++)
    {
        for (x = 0; x < w; x++)
        {
            u = (x / (double) w);
            v = (y / (double) h);
            noise_x = (int) floor((u + step) * noise_size) & (noise_size - 1);
            noise_y = (int) floor((v + step) * noise_size) & (noise_size - 1);
            value = noise_values[noise_x + noise_y * noise_size];
            // value = value / 2;
            grey = (int) floor(value * 255) & 0xFF;
            pixels[x + y * w] = 0xFF000000 + (grey << 16) + (grey << 8) + grey;
        }
    }

    drb_upload_pixel_array(sprite->symbol, w, h, pixels);
}

void wobbleShader(ShaderSprite *sprite, Texture *source, NoiseArray *noise, double step, double offset_strength)
{
    static drb_upload_pixel_array_fn drb_upload_pixel_array = NULL;
    Uint32 *pixels = sprite->pixels;
    Color original, distort, *source_colors = source->pixels;
    int x, y, src_x, src_y, noise_x, noise_y,
        noise_size = noise->w, w = sprite->w,
        h = sprite->h, src_w = source->w, src_h = source->h;
    double shift, u, v, *noise_values = noise->values;
    if (!drb_upload_pixel_array) {
        drb_upload_pixel_array = drb_symbol_lookup("drb_upload_pixel_array");
        if (!drb_upload_pixel_array) {
            return;  // oh well.
        }
    }

    for (y = 0; y < h; y++)
    {
        for (x = 0; x < w; x++)
        {
            u = (x / (double) w);
            v = (y / (double) h);
            src_x = (int) floor(u * src_w);
            src_y = (int) floor(v * src_h);
            original = source_colors[src_x + src_y * src_w];
            if (original.a > 0.99)
            {
                pixels[x + y * w] = colorToUint(original);
                continue;
            }
            // only works if noise_size is a power of 2
            noise_x = (int) floor((u + step) * noise_size) & (noise_size - 1);
            noise_y = (int) floor((v + step) * noise_size) & (noise_size - 1);
            shift = noise_values[noise_x + noise_y * noise_size] * offset_strength;
            u = (u + shift);
            u = u < 0 ? 0 : (u > 1 ? 1 : u);
            v = (v + shift);
            v = v < 0 ? 0 : (v > 1 ? 1 : v);
            src_x = (int) floor(u * src_w);
            src_x= src_x < 0 ? 0 : (src_x > src_w - 1 ? src_w - 1 : src_x);
            src_y = (int) floor(v * src_h);
            src_y = src_y < 0 ? 0 : (src_y > src_h - 1 ? src_h - 1 : src_y);
            distort = source_colors[src_x + src_y * src_w];
            multiplyColorByScalar(&distort, distort.a);
            multiplyColorByScalar(&distort, 1 - original.a);
            pixels[x + y * w] = colorToUint(sumColors(distort, original));
        }
    }

    drb_upload_pixel_array(sprite->symbol, w, h, pixels);
}


void horizWaveShader(ShaderSprite *sprite, Texture *source, double step, double offset_strength)
{
    static drb_upload_pixel_array_fn drb_upload_pixel_array = NULL;
    Uint32 *pixels = sprite->pixels;
    Color original, distort, *source_colors = source->pixels;
    int x, y, src_x, src_y, w = sprite->w,
        h = sprite->h, src_w = source->w, src_h = source->h;
    double shift, u, v;

    if (!drb_upload_pixel_array)
    {
        drb_upload_pixel_array = drb_symbol_lookup("drb_upload_pixel_array");
        if (!drb_upload_pixel_array)
        {
            return;  // oh well.
        }
    }

    for (y = 0; y < h; y++)
    {
        for (x = 0; x < w; x++)
        {
            u = (x / (double) w);
            v = (y / (double) h);
            src_x = (int) floor(u * src_w);
            src_y = (int) floor(v * src_h);
            original = source_colors[src_x + src_y * src_w];
            shift = sin((step + v) * 10) * offset_strength;
            u = (u + shift);
            u = u < 0 ? 0 : (u > 1 ? 1 : u);
            // v = (v + shift);
            // v = v < 0 ? 0 : (v > 1 ? 1 : v);
            src_x = (int) floor(u * src_w);
            src_x= src_x < 0 ? 0 : (src_x > src_w - 1 ? src_w - 1 : src_x);
            src_y = (int) floor(v * src_h);
            src_y = src_y < 0 ? 0 : (src_y > src_h - 1 ? src_h - 1 : src_y);
            distort = source_colors[src_x + src_y * src_w];
            pixels[x + y * w] = colorToUint(distort);
        }
    }

    drb_upload_pixel_array(sprite->symbol, w, h, pixels);
}

void wipeShader(ShaderSprite *sprite, Texture *source, Texture *wipe_texture, double step)
{
    static drb_upload_pixel_array_fn drb_upload_pixel_array = NULL;
    Uint32 *pixels = sprite->pixels;
    Color original, *source_colors = source->pixels, *wipe_vals = wipe_texture->pixels;
    int x, y, w = sprite->w, h = sprite->h,
        wipe_x, wipe_y, wipe_w = wipe_texture->w, wipe_h = wipe_texture->h,
        src_x, src_y, src_w = source->w, src_h = source->h;
    double u, v;

    if (!drb_upload_pixel_array)
    {
        drb_upload_pixel_array = drb_symbol_lookup("drb_upload_pixel_array");
        if (!drb_upload_pixel_array)
        {
            return;  // oh well.
        }
    }

    for (y = 0; y < h; y++)
    {
        for (x = 0; x < w; x++)
        {
            u = (x / (double) w);
            v = (y / (double) h);
            src_x = (int) floor(u * src_w);
            src_y = (int) floor(v * src_h);
            wipe_x = (int) floor(u * wipe_w);
            wipe_y = (int) floor(v * wipe_h);
            original = source_colors[src_x + src_y * src_w];
            pixels[x + y * w] = colorToUint(original) * (wipe_vals[wipe_x + wipe_y * wipe_w].r < step);
        }
    }

    drb_upload_pixel_array(sprite->symbol, w, h, pixels);
}

void dissolveShader(ShaderSprite *sprite, Texture *source, NoiseArray *noise, Uint32 highlight_color, double step)
{
    static drb_upload_pixel_array_fn drb_upload_pixel_array = NULL;
    Uint32 highlight, *pixels = sprite->pixels, final_color;
    Color original, *source_colors = source->pixels;
    int is_solid, x, y, w = sprite->w, h = sprite->h,
        noise_x, noise_y, noise_w = noise->w, noise_h = noise->h,
        src_x, src_y, src_w = source->w, src_h = source->h;
    double u, v, *noise_values = noise->values;

    if (!drb_upload_pixel_array)
    {
        drb_upload_pixel_array = drb_symbol_lookup("drb_upload_pixel_array");
        if (!drb_upload_pixel_array)
        {
            return;  // oh well.
        }
    }

    for (y = 0; y < h; y++)
    {
        for (x = 0; x < w; x++)
        {
            u = (x / (double) w);
            v = (y / (double) h);
            src_x = (int) floor(u * src_w);
            src_y = (int) floor(v * src_h);
            noise_x = (int) floor(u * noise_w);
            noise_y = (int) floor(v * noise_h);
            original = source_colors[src_x + src_y * src_w];
            final_color = colorToUint(original);
            is_solid = noise_values[noise_x + noise_y * noise_w] < step;
            highlight = highlight_color & (final_color | 0x00FFFFFF);
            highlight = highlight * (noise_values[noise_x + noise_y * noise_w] < (step + 0.05)) * (1 - is_solid);
            final_color *= is_solid;
            pixels[x + y * w] = final_color + highlight;
        }
    }

    drb_upload_pixel_array(sprite->symbol, w, h, pixels);
}

void dissolveFromTextureShader(ShaderSprite *sprite, Texture *source, Texture *dissolve, Uint32 highlight_color, double step)
{
    static drb_upload_pixel_array_fn drb_upload_pixel_array = NULL;
    Uint32 highlight, *pixels = sprite->pixels, final_color;
    Color original, *source_colors = source->pixels, *dissolve_values = dissolve->pixels;
    int is_solid, x, y, w = sprite->w, h = sprite->h,
        dissolve_x, dissolve_y, dissolve_w = dissolve->w, dissolve_h = dissolve->h,
        src_x, src_y, src_w = source->w, src_h = source->h;
    double u, v;

    if (!drb_upload_pixel_array)
    {
        drb_upload_pixel_array = drb_symbol_lookup("drb_upload_pixel_array");
        if (!drb_upload_pixel_array)
        {
            return;  // oh well.
        }
    }

    for (y = 0; y < h; y++)
    {
        for (x = 0; x < w; x++)
        {
            u = (x / (double) w);
            v = (y / (double) h);
            src_x = (int) floor(u * src_w);
            src_y = (int) floor(v * src_h);
            dissolve_x = (int) floor(u * dissolve_w);
            dissolve_y = (int) floor(v * dissolve_h);
            original = source_colors[src_x + src_y * src_w];
            final_color = colorToUint(original);
            is_solid = dissolve_values[dissolve_x + dissolve_y * dissolve_w].r < step;
            highlight = highlight_color & (final_color | 0x00FFFFFF);
            highlight = highlight * (dissolve_values[dissolve_x + dissolve_y * dissolve_w].r < (step + 0.05)) * (1 - is_solid);
            final_color *= is_solid;
            pixels[x + y * w] = final_color + highlight;
        }
    }

    drb_upload_pixel_array(sprite->symbol, w, h, pixels);
}