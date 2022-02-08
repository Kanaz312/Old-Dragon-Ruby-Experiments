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

typedef struct NoiseArray
{
    double *values;
    int w;
    int h;
} NoiseArray;

typedef struct Color
{
    double r;
    double g;
    double b;
    double a;
} Color;

typedef struct Texture
{
    Color *pixels;
    int w;
    int h;
} Texture;

typedef struct ShaderSprite
{
    Uint32 *pixels;
    int w;
    int h;
    char *symbol;
} ShaderSprite;

NoiseArray *makeSeamlessNoiseArr(int w, int h, int octaves, double persistence, int seed, int end_freq);
void normalizePerlin(NoiseArray *noise);
void destoryNoise(NoiseArray *noise);
void destroyArray(void *arr);
unsigned int squirrel1d(int posx, unsigned int seed);
double perlin2d(double x, double y, int seed);
double seamlessPerlin2d(double x, double y, int seed, int freq);
Color *uintArrayToColorArray(Uint32 *original, int w, int h);
Texture *loadColorTexture(char *path);
ShaderSprite *makeShaderSprite(char *sprite_symbol, int sprite_w, int sprite_h);
void changeSymbol(ShaderSprite *sprite, char *symbol);
void destroyTexture(Texture *texture);
void destroyShaderSprite(ShaderSprite *sprite);
void displayNoise(ShaderSprite *sprite, NoiseArray *noise, double step);
void wobbleShader(ShaderSprite *sprite, Texture *source, NoiseArray *noise, double step, double offset_strength);
void horizWaveShader(ShaderSprite *sprite, Texture *source, double step, double offset_strength);
void wipeShader(ShaderSprite *sprite, Texture *source, Texture *wipe_texture, double step);
void dissolveShader(ShaderSprite *sprite, Texture *source, NoiseArray *noise, Uint32 highlight_color, double step);
void dissolveFromTextureShader(ShaderSprite *sprite, Texture *source, Texture *dissolve, Uint32 highlight_color, double step);
#endif