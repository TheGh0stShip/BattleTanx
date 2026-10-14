#include "types.h"

#define ABS(x) ((x) < 0 ? -(x) : (x))

typedef struct AreaBox {
    u16 flags;
    s16 x;
    s16 y;
    s16 minA;
    s16 maxA;
    s16 minB;
    s16 maxB;
    s16 radius;
    u16 kind;
} AreaBox;

extern u32 integer_sqrt(u32 value) __asm__("func_80109094");

void init_area_box(AreaBox *box, s32 x, s32 y, s32 minA, s32 maxA, s32 minB, s32 maxB, u16 kind) __asm__("func_80109268");

void init_area_box(AreaBox *box, s32 x, s32 y, s32 minA, s32 maxA, s32 minB, s32 maxB, u16 kind)
{
    s32 a;
    s32 b;

    box->x = x;
    box->y = y;
    box->minA = minA;
    box->maxA = maxA;
    box->minB = minB;
    box->maxB = maxB;
    box->kind = kind;
    a = (ABS(minA) > ABS(maxA)) ? minA : maxA;
    if (a < 0) {
        a = -a;
    }
    b = maxB;
    if (ABS(minB) > ABS(maxB)) {
        b = minB;
    }
    if (b < 0) {
        b = -b;
    }
    box->radius = integer_sqrt(a * a + b * b);
    box->flags &= 0xFFF0;
}
