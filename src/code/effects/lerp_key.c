#include "types.h"

typedef struct LerpKey {
    s16 x;
    s16 y;
    s16 z;
    u8 pad06[6];
    u8 r;
    u8 g;
    u8 b;
} LerpKey;

void lerp_key(s32 t, LerpKey *start, LerpKey *end, LerpKey *out) __asm__("func_8009189C");

void lerp_key(s32 t, LerpKey *start, LerpKey *end, LerpKey *out)
{
    out->x = start->x + (((end->x - start->x) * t) >> 8);
    out->y = start->y + (((end->y - start->y) * t) >> 8);
    out->z = start->z + (((end->z - start->z) * t) >> 8);
    out->r = start->r + (((s32)(end->r - start->r) * t) >> 8);
    out->g = start->g + (((s32)(end->g - start->g) * t) >> 8);
    out->b = start->b + (((s32)(end->b - start->b) * t) >> 8);
}
