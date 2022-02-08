#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "ext.h"

#define DISTORT_STRENGTH 0.2
#define PERLIN_FREQ 13

double clamp(double val, double min, double max);
extern void *(*drb_symbol_lookup)(const char *sym);
typedef void (*drb_upload_pixel_array_fn)(const char *name, const int w, const int h, const Uint32 *pixels);
typedef void *(*drb_load_image_fn)(const char *fname, int *w, int *h);

Uint32 *makePixelArr(int w, int h)
{
    Uint32 *arr = malloc(w * h * sizeof(Uint32));
    if (NULL == (arr = malloc(w * h * sizeof(double))))
    {
        exit(EXIT_FAILURE);
    }
    return arr;
}

/* returns an array of perlin noise values size w * h that is tileable (wraps)
 * octaves is the number of octaves that should be summed
 * persistence is how much each subsequent octave should affect the final result
 *   generally this should be less than (0.4 is nice imo)
 * end_freq is the final frequency you want (higher means more detail)
 */
double *makeSeamlessNoiseArr(int w, int h, int octaves, double persistence, int seed, int end_freq)
{
    double x, y, work_freq, amplitude, total, max, value, *arr;
    int i, j;
    if (NULL == (arr = malloc(w * h * sizeof(double))))
    {
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

        /* sums perlin nosie for each octave (shrinking amplitude by persistence) */
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
    return arr;
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

Uint32 getColor(Uint32 brightness, double v)
{
    Uint32 b = brightness * 0;
    Uint32 g = mix(0, brightness - 20, (1 - v));
    // Uint32 g = brightness;
    Uint32 r = brightness;
    if (brightness < 40)
        return 0;
    return  0xFF000000 + (b << 16) + (g << 8) + r;
}

Sprite *make_sprite(char *fname, char *sprite_symbol, int sprite_w, int sprite_h, int noise_size, int seed) 
{
    static drb_load_image_fn drb_load_image = NULL;
    int w, h;
    double *noise;
    char *symbol;
    Uint32 *source, *pixels;
    Sprite *sprite;
    if (!drb_load_image) 
    {
        drb_load_image = drb_symbol_lookup("drb_load_image");
    }

    if (drb_load_image) 
    {
        source = (Uint32 *) drb_load_image(fname, &w, &h);
        if(source == NULL){
            exit(EXIT_FAILURE); // sadge
        }
    }

    sprite = malloc(sizeof(Sprite));
    if (sprite == NULL)
        exit(EXIT_FAILURE);

    pixels = malloc(sprite_w * sprite_h * sizeof(Uint32));
    if (pixels == NULL)
        exit(EXIT_FAILURE);

    symbol = malloc(strlen(sprite_symbol) + 1);
    if (symbol == NULL)
        exit(EXIT_FAILURE);
    strcpy(symbol, sprite_symbol);

    noise = makeSeamlessNoiseArr(noise_size, noise_size, 8, 0.4, seed, 23);

    sprite->pixels = pixels;
    sprite->source = source;
    sprite->noise = noise;
    sprite->noise_size = noise_size;
    sprite->sprite_w = sprite_w;
    sprite->sprite_h = sprite_h;
    sprite->source_w = w;
    sprite->source_h = h;
    sprite->step = 0.1;
    sprite->symbol = symbol;
    return sprite;
}

void update_sprite(Sprite *sprite, double skip)
{
    static drb_upload_pixel_array_fn drb_upload_pixel_array = NULL;
    Uint32 distort, original, *pixels = sprite->pixels, *source = sprite->source;
    int x, y, r, g, b, src_x, src_y, noise_x, noise_y,
        noise_size = sprite->noise_size, w = sprite->sprite_w,
        h = sprite->sprite_h, src_w = sprite->source_w, src_h = sprite->source_h;
    double shift, u, v, step = sprite->step, *noise = sprite->noise;
    
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
            original = source[src_x + src_y * src_w];
            if ((original & 0xFF000000) == 0xFF000000)
            {
                pixels[x + y * w] = original;
                continue;
            }
            noise_x = (int) floor((u + step) * noise_size) & (noise_size - 1);
            noise_y = (int) floor((v + step) * noise_size) & (noise_size - 1);
            shift = noise[noise_x + noise_y * noise_size] / 15;
            u = (u + shift);
            u = u < 0 ? 0 : (u > 1 ? 1 : u);
            v = (v + shift);
            v = v < 0 ? 0 : (v > 1 ? 1 : v);
            src_x = (int) floor(u * src_w);
            src_x= src_x < 0 ? 0 : (src_x > src_w - 1 ? src_w - 1 : src_x);
            src_y = (int) floor(v * src_h);
            src_y = src_y < 0 ? 0 : (src_y > src_h - 1 ? src_h - 1 : src_y);
            distort = source[src_x + src_y * src_w];
            distort *= 1 - (0x1 & original >> 31);
            pixels[x + y * w] = distort + original;
        }
    }

    sprite->step = step + 0.001;

    drb_upload_pixel_array(sprite->symbol, w, h, pixels);
}