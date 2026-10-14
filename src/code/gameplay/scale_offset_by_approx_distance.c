#include "types.h"

extern f32 gApproxDistanceMinorScaleA __asm__("D_800744B8");
extern f32 gApproxDistanceMinorDivisorA __asm__("D_800744BC");
extern f32 gApproxDistanceMinorScaleB __asm__("D_800744C0");
extern f32 gApproxDistanceMinorDivisorB __asm__("D_800744C4");

void scale_offset_by_approx_distance(f32 *from, f32 *to, f32 scale, f32 *out) __asm__("func_800E171C");

/* The retail code stores offset[1] from a value that is never initialized. */
void scale_offset_by_approx_distance(f32 *from, f32 *to, f32 scale, f32 *out)
{
    f32 offset[2];
    f32 absOffset[2];
    f32 absY;
    f32 absX;
    f32 yExtent;
    f32 xExtent;
    f32 distance;

    offset[1] = absX;
    offset[0] = to[0] - from[0];
    absY = to[1] - from[1];
    if (!(absY > 0.0f)) {
        absY = -absY;
    }
    absOffset[1] = absY;
    absX = to[0] - from[0];
    if (!(absX > 0.0f)) {
        absX = -absX;
    }
    absOffset[0] = absX;
    yExtent = absY;
    if (!(yExtent > 0.0f)) {
        yExtent = -yExtent;
    }
    xExtent = absX;
    if (!(xExtent > 0.0f)) {
        xExtent = -xExtent;
    }
    if (xExtent < yExtent) {
        distance = yExtent + xExtent * gApproxDistanceMinorScaleA / gApproxDistanceMinorDivisorA;
    } else {
        distance = xExtent + yExtent * gApproxDistanceMinorScaleB / gApproxDistanceMinorDivisorB;
    }
    out[1] = offset[1] * scale / distance;
    out[0] = offset[0] * scale / distance;
}
