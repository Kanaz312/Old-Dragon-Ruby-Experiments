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

typedef struct Sprite
{
    Uint32 *pixels;
    Uint32 *source;
    double *noise;
    int sprite_w;
    int sprite_h;
    int source_w;
    int source_h;
    int noise_size;
    double step;
    char *symbol;
} Sprite;

double *makeSeamlessNoiseArr(int w, int h, int octaves, double persistence, int seed, int end_freq);
Uint32 *makePixelArr(int w, int h);
void destroyArray(void *arr);
unsigned int squirrel1d(int posx, unsigned int seed);
double perlin2d(double x, double y, int seed);
double seamlessPerlin2d(double x, double y, int seed, int freq);
Sprite *make_sprite(char *fname, char *sprite_symbol, int sprite_w, int sprite_h, int noise_size, int seed);
void update_sprite(Sprite *sprite, double skip);

#endif