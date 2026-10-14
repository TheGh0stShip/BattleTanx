#include "types.h"

typedef struct PlanarPoint {
    f32 x;
    f32 y;
} PlanarPoint;

extern f32 gRangeModeTwoLimitSq __asm__("D_800714A0");
extern f32 gRangeModeThreeFarSq __asm__("D_800714A4");
extern f32 gRangeModeThreeNearSq __asm__("D_800714A8");

s32 classify_planar_range(PlanarPoint *a, PlanarPoint *b, s32 mode) __asm__("func_800821D0");
s32 classify_planar_range(PlanarPoint *a, PlanarPoint *b, s32 mode)
{
    f32 dy;
    f32 dx;

    switch (mode) {
    case 2:
        dy = a->y - b->y;
        dx = a->x - b->x;
        if (gRangeModeTwoLimitSq < dy * dy + dx * dx) {
            return 1;
        }
        return 0;
    case 3:
        dy = a->y - b->y;
        dx = a->x - b->x;
        if (gRangeModeThreeFarSq < dy * dy + dx * dx) {
            return 2;
        }
        if (gRangeModeThreeNearSq < dy * dy + dx * dx) {
            return 1;
        }
        return 0;
    default:
        return 0;
    }
}
