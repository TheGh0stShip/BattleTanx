#include "types.h"

typedef struct LevelPoint {
    u8 pad00[0x20];
    f32 value20;
    f32 value24;
    u8 pad28[0x4];
} LevelPoint;

typedef struct LevelPointSet {
    u8 pad000[0x584];
    LevelPoint points[1];
} LevelPointSet;

typedef struct LevelQueryPosition {
    f32 value00;
    f32 value04;
} LevelQueryPosition;

extern s32 D_801C9174;

extern s32 get_difficulty_level(void) __asm__("func_8007AAA0");
extern void handle_level_point(LevelPointSet *level, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 index) __asm__("func_800824E4");
extern s32 level_point_check(f32 a, f32 b, LevelPoint *point) __asm__("func_800940AC");

void visit_level_points_in_radius(LevelPointSet *level, s32 arg1, s32 arg2, s32 arg3, s32 arg4, LevelQueryPosition *pos) __asm__("func_80084A74");

static inline s32 level_point_in_radius(f32 a, f32 b, LevelPoint *point)
{
    f32 da = point->value24 - a;
    f32 db = point->value20 - b;

    if (da * da + db * db < (f32)D_801C9174) {
        return 1;
    }
    return 0;
}

void visit_level_points_in_radius(LevelPointSet *level, s32 arg1, s32 arg2, s32 arg3, s32 arg4, LevelQueryPosition *pos)
{
    s32 count = get_difficulty_level();
    s32 i;

    for (i = 0; i < count; i++) {
        f32 a = pos->value04;
        f32 b = pos->value00;
        LevelPoint *point = &level->points[i];

        if (level_point_in_radius(a, b, point) && level_point_check(a, b, point) == 0) {
            handle_level_point(level, arg1, arg2, 0, arg3, arg4, i);
        }
    }
}
