#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "ext.h"
#define SIZE 300
#define DISTORT_STRENGTH 0.2
#define PERLIN_FREQ 5

double clamp(double val, double min, double max);
extern void *(*drb_symbol_lookup)(const char *sym);
typedef void (*drb_upload_pixel_array_fn)(const char *name, const int w, const int h, const Uint32 *pixels);

Uint32 *makePixelArr(int w, int h)
{
    Uint32 *arr = malloc(w * h * sizeof(Uint32));
    if (NULL == (arr = malloc(w * h * sizeof(double))))
    {
        exit(EXIT_FAILURE);
    }
    return arr;
}
double *makeNoiseArr(int w, int h)
{
    double x, y, freq, amplitude, total, max, value, *arr;
    int i, j, seed = 124324;
    if (NULL == (arr = malloc(w * h * sizeof(double))))
    {
        exit(EXIT_FAILURE);
    }
    
    for (i = 0; i < w * h; i++)
    {
        x = (i % w) * 5 / (double) w;
        y = floor(i / h) * 5 / (double) h;
        freq = 1;
        amplitude = 1;
        total = 0;
        max = 0;
        // total += seamlessPerlin2d(x * freq, y * freq, seed, freq * 5) * amplitude;
        
        for (j = 0; j < 21; j++)
        {
            total += seamlessPerlin2d(x * freq, y * freq, seed, freq * 5) * amplitude;
            max += amplitude;
            amplitude *= 0.4;
            freq *= 2;
            seed *= 4;
        }
        // perlin_value = perlin_value + seamlessPerlin2d(x * (PERLIN_FREQ + 3), y * (PERLIN_FREQ + 3), 15, PERLIN_FREQ + 3);
        // perlin_value = perlin_value + seamlessPerlin2d(x * (PERLIN_FREQ + 7), y * (PERLIN_FREQ + 7), 18231, PERLIN_FREQ + 7);
        // perlin_value = perlin_value + seamlessPerlin2d(x * (PERLIN_FREQ + 13), y * (PERLIN_FREQ + 13), 23409, PERLIN_FREQ + 13);
        // perlin_value = perlin_value + seamlessPerlin2d(x * (PERLIN_FREQ + 23), y * (PERLIN_FREQ + 23), 34909, PERLIN_FREQ + 23);
        value = (total / max) + 1;
        // if( value < 0.5 && value > 0.1)
        //     value -= 0.2;
        arr[i] = clamp(value, 0, 2) / 2;
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

void update_texture(double *arr, Uint32 *pixels, int w, int h, int freq, double step)
{
    static drb_upload_pixel_array_fn drb_upload_pixel_array = NULL;
    int i, x, y, u_anim, v_anim, cx, cy, r2;
    double u, v, shift = 0, perlin_value;
    Uint32 brightness;
    r2 = w / 2;
    r2 = r2 * r2;
    cx = w / 2;
    cy = h / 2;
    if (!drb_upload_pixel_array) {
        drb_upload_pixel_array = drb_symbol_lookup("drb_upload_pixel_array");
        if (!drb_upload_pixel_array) {
            return;  // oh well.
        }
    }

    // Set up our "texture" pixel array and fill it with black pixels.

    // You could make this faster by making this array static (which will
    //  initialize it all to zero at startup), and then blanking the previous
    //  line and drawing the next, and not touching the rest.
    for (i = 0; i < w * h; i++)
    {
        x = i % w;
        y = floor(i / h);
        // if (y > h / 2 && (x - cx) * (x - cx) + (y - cy) * (y - cy) > r2)
        // {
        //     pixels[i] = 0;
        //     continue;
        // }
        u = (x / (double) w);
        v = (y / (double) h);
        shift = perlin2d(u * 1.5, v * 1.5, 16) * DISTORT_STRENGTH;
        // u_anim = u + shift - (step / 3));
        // v_anim = v + shift + step;
        // perlin_value = perlin2d(u_anim * freq, v_anim * freq, 0);
        // perlin_value = perlin_value + perlin2d(u_anim * (freq + 3), v_anim * (freq + 3), 0) / 2;
        // perlin_value = perlin_value + perlin2d(u_anim * (freq + 7), v_anim * (freq + 7), 0) / 3;
        // perlin_value = (perlin_value + 1) / 2;
        // perlin_value = clamp(perlin_value,  0, 1);
        u_anim = ((unsigned int) floor(x + shift * w - (step * w / 3))) % w;
        v_anim = ((unsigned int) floor(y + shift * h + step * h)) % h;
        perlin_value = arr[u_anim + v_anim * h];
        perlin_value = mix(-1, 2, (1 - v) + 0.2) / 2 + perlin_value;
        brightness = clamp(floor(256 * (perlin_value)), 0, 255);
        pixels[i] = getColor(brightness, v);
    }

    // Send it to the renderer to create/update a sprite.
    drb_upload_pixel_array("noise_texture", w, h, pixels);
}
