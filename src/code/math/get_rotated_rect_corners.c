#include "types.h"

typedef struct RectPoint {
    f32 x;
    f32 y;
} RectPoint;

typedef struct RotatedRect {
    u8 pad00[2];
    s16 originY;
    s16 originX;
    s16 minU;
    s16 maxU;
    s16 minV;
    s16 maxV;
    u8 pad0E[2];
    u16 angle;
} RotatedRect;

extern f32 angle_sin(u16 angle) __asm__("func_800F3AE0");
extern f32 angle_cos(u16 angle) __asm__("func_800F3B40");

void get_rotated_rect_corners(RotatedRect *rect, RectPoint *out) __asm__("func_8010B740");

void get_rotated_rect_corners(RotatedRect *rect, RectPoint *out) {
    RectPoint corners[4];
    f32 s;
    f32 c;
    s32 first;
    s32 i;

    s = -angle_sin(rect->angle);
    c = angle_cos(rect->angle);
    corners[0].y = c * rect->minU - s * rect->minV + rect->originY;
    corners[0].x = s * rect->minU + c * rect->minV + rect->originX;
    corners[1].y = c * rect->minU - s * rect->maxV + rect->originY;
    corners[1].x = s * rect->minU + c * rect->maxV + rect->originX;
    corners[2].y = c * rect->maxU - s * rect->maxV + rect->originY;
    corners[2].x = s * rect->maxU + c * rect->maxV + rect->originX;
    corners[3].y = c * rect->maxU - s * rect->minV + rect->originY;
    corners[3].x = s * rect->maxU + c * rect->minV + rect->originX;
    first = 0;
    for (i = 1; i < 4; i++) {
        if (corners[i].y < corners[first].y) {
            first = i;
        }
    }
    for (i = 0; i < 4; i++) {
        out[i].y = corners[(i + first) & 3].y;
        out[i].x = corners[(i + first) & 3].x;
    }
}
