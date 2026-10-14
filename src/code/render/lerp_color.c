#include "types.h"

typedef struct LerpColor {
    u8 red;
    u8 green;
    u8 blue;
    u8 alpha;
} LerpColor;

void lerp_color(LerpColor *out, LerpColor *from, LerpColor *to, f32 t) __asm__("func_800AB24C");

void lerp_color(LerpColor *out, LerpColor *from, LerpColor *to, f32 t)
{
    f32 red;
    f32 green;
    f32 blue;
    f32 alpha;

    red = t * (to->red - from->red);
    out->red = from->red + (u32)red;
    green = t * (to->green - from->green);
    out->green = from->green + (u32)green;
    blue = t * (to->blue - from->blue);
    out->blue = from->blue + (u32)blue;
    alpha = t * (to->alpha - from->alpha);
    out->alpha = from->alpha + (u32)alpha;
}
