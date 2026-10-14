#include "types.h"

typedef struct AreaBox {
    s16 value00;
    s16 value02;
    s16 value04;
    s16 value06;
    s16 value08;
    s16 value0A;
    s16 value0C;
    s16 value0E;
    s16 value10;
} AreaBox;

extern void func_80109268(AreaBox *box, s32 x, s32 y, s32 minA, s32 maxA, s32 minB, s32 maxB, s32 flags);
extern u8 func_80107A14(AreaBox *box, s32 capacity, void **results, s32 *count);
extern f32 D_80126038[];
extern f32 D_80072C80;

s32 is_area_unoccupied_scaled(f32 x, f32 y, s32 sizeIndex) __asm__("func_800A12E4");

/* Builds a square query box around (x, y) sized from D_80126038 and reports whether the area query found nothing. */
s32 is_area_unoccupied_scaled(f32 x, f32 y, s32 sizeIndex)
{
    void *results[16];
    AreaBox box;
    s32 count;
    f32 half;

    half = D_80126038[sizeIndex] * D_80072C80;
    func_80109268(&box, x, y, -half, half, -half, half, 0);
    return !func_80107A14(&box, 16, results, &count);
}
