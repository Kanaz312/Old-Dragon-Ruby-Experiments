#ifndef EXT_H
#define EXT_H

#define BIT_NOISE1 0x68e31da4
#define BIT_NOISE2 0xb5297a4d
#define BIT_NOISE3 0x1b56c4e9
#define PRIME 198491317
#ifndef NULL
#define NULL 0
#endif

typedef unsigned int Uint32;
typedef struct Fire
{
    double *noise;
    Uint32 *pixels;
    int w;
    int h;
    int freq;
    double step;
} Fire;

double *makeNoiseArr(int w, int h);
Uint32 *makePixelArr(int w, int h);
void destroyArray(void *arr);
unsigned int squirrel1d(int posx, unsigned int seed);
double perlin2d(double x, double y, int seed);
double seamlessPerlin2d(double x, double y, int seed, int freq);
void update_texture(double *arr, Uint32 *pixels, int w, int h, int freq, double step);

#endif