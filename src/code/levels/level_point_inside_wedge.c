#include "types.h"

typedef struct LevelPoint {
    f32 forwardY;
    f32 forwardX;
    f32 sideX;
    f32 sideY;
    f32 originX;
    f32 originY;
    u8 disabled;
} LevelPoint;

s32 level_point_inside_wedge(f32 x, f32 y, LevelPoint *point) __asm__("func_800940AC");

s32 level_point_inside_wedge(f32 x, f32 y, LevelPoint *point)
{
    f32 relativeY;
    f32 relativeX;
    f32 forward;
    f32 side;

    if (point->disabled != 0) {
        return 0;
    }
    relativeY = y + point->originY;
    relativeX = x + point->originX;
    forward = point->forwardY * relativeY + point->forwardX * relativeX;
    side = point->sideX * relativeX - point->sideY * relativeY;
    if (!(forward <= 0.0f)) {
        if (!(side > 0.0f)) {
            side = -side;
        }
        if (forward <= side) {
            return 1;
        }
        return 0;
    }
    return 1;
}
