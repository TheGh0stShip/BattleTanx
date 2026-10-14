#include "types.h"

typedef struct LevelPoint {
    u8 pad00[0x20];
    f32 x;
    f32 y;
    u8 pad28[0x4];
} LevelPoint;

extern s32 get_difficulty_level(void) __asm__("func_8007AAA0");
extern void handle_level_point(u8 *level, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 index) __asm__("func_800824E4");
extern s32 test_point_outside_sector(f32 x, f32 y, f32 r, LevelPoint *point) __asm__("func_800941E0");
extern s32 D_801C9174;

void handle_level_points_in_radius(u8 *level, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, f32 *pos, f32 radius) __asm__("func_80084CC4");

static inline s32 level_point_in_radius(f32 y, f32 x, LevelPoint *point)
{
    f32 dy = point->y - y;
    f32 dx = point->x - x;

    if (dy * dy + dx * dx < (f32)D_801C9174) {
        return 1;
    }
    return 0;
}

void handle_level_points_in_radius(u8 *level, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, f32 *pos, f32 radius)
{
    f32 y;
    s32 count;
    s32 i;
    LevelPoint *point;

    count = get_difficulty_level();
    for (i = 0; i < count; i++) {
        y = pos[1];
        point = (LevelPoint *)(level + 0x584) + i;
        if (level_point_in_radius(y, pos[0], point) && test_point_outside_sector(pos[1], pos[0], radius, point) == 0) {
            handle_level_point(level, arg1, arg2, arg3, arg4, arg5, i);
        }
    }
}
