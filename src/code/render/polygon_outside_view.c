#include "types.h"

typedef struct ViewCone {
    f32 m00;
    f32 m01;
    f32 m10;
    f32 m11;
    f32 offsetZ;
    f32 offsetX;
    u8 disabled;
} ViewCone;

s32 polygon_outside_view(f32 (*points)[2], s32 count, ViewCone *view) __asm__("func_800942A8");

s32 polygon_outside_view(f32 (*points)[2], s32 count, ViewCone *view)
{
    f32 rel[4][2];
    f32 proj[4][2];
    u8 codes[4];
    s32 i;
    s32 next;
    u8 k = 0xFF;
    f32 t;

    if (view->disabled) {
        return 0;
    }
    if (count >= 5) {
        return 1;
    }
    for (i = 0; i < count; i++) {
        rel[i][1] = points[i][1] + view->offsetZ;
        rel[i][0] = points[i][0] + view->offsetX;
        proj[i][1] = view->m10 * rel[i][1] - view->m11 * rel[i][0];
        proj[i][0] = view->m00 * rel[i][0] + view->m01 * rel[i][1];
        if (proj[i][1] > 0.0f) {
            if (proj[i][0] < 0.0f) {
                codes[i] = 5;
            } else if (proj[i][1] < proj[i][0]) {
                return 0;
            } else {
                codes[i] = 1;
            }
        } else {
            if (proj[i][0] < 0.0f) {
                codes[i] = 6;
            } else if (-proj[i][1] < proj[i][0]) {
                return 0;
            } else {
                codes[i] = 2;
            }
        }
    }
    for (i = 0; i < count; i++) {
        k &= codes[i];
    }
    if (k) {
        return 1;
    }
    for (i = 0; i < count; i = next) {
        next = i + 1;
        if ((codes[i] | codes[next % count]) == 3) {
            return 0;
        }
    }
    for (i = 0; i < count; i++) {
        if ((codes[i] ^ codes[(i + 1) % count]) == 7) {
            k = (i + 1) % count;
            t = -proj[i][1] / (proj[k][1] - proj[i][1]);
            if (t * (proj[k][0] - proj[i][0]) + proj[i][0] > 0.0f) {
                return 0;
            }
        }
    }
    return 1;
}
