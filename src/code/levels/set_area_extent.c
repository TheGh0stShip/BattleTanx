#include "types.h"

#define ABS(x) ((x) < 0 ? -(x) : (x))

typedef struct AreaExtent {
    u16 flags;
    s16 x;
    s16 y;
    s16 minA;
    s16 maxA;
    s16 minB;
    s16 maxB;
    s16 radius;
} AreaExtent;

extern u32 integer_sqrt(u32 value) __asm__("func_80109094");

void set_area_extent(AreaExtent *box, s32 minA, s32 maxA, s32 minB, s32 maxB) __asm__("func_80109364");

void set_area_extent(AreaExtent *box, s32 minA, s32 maxA, s32 minB, s32 maxB)
{
    s32 a;
    s32 b;

    a = (ABS(minA) > ABS(maxA)) ? ABS(minA) : ABS(maxA);
    b = (ABS(minB) > ABS(maxB)) ? ABS(minB) : ABS(maxB);
    box->radius = integer_sqrt(a * a + b * b);
    box->minA = minA;
    box->maxA = maxA;
    box->minB = minB;
    box->maxB = maxB;
    box->flags &= 0xFFF0;
}
