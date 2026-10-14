#include "types.h"

typedef struct LevelBounds {
    f32 minX;
    f32 minZ;
    f32 maxX;
    f32 maxZ;
} LevelBounds;

extern LevelBounds *gLevelBounds __asm__("D_801C9170");

s32 point_in_level_bounds(f32 x, f32 z) __asm__("func_80085D84");

s32 point_in_level_bounds(f32 x, f32 z)
{
    s32 inside;

    inside = 0;
    if (gLevelBounds->minX < x && x < gLevelBounds->maxX && gLevelBounds->minZ < z && z < gLevelBounds->maxZ) {
        inside = 1;
    }
    return inside;
}
