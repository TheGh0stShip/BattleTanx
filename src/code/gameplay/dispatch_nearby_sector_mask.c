#include "types.h"

typedef struct SectorPoint {
    u8 pad00[0x20];
    f32 value20;
    f32 value24;
    u8 pad28[4];
} SectorPoint;

typedef struct SectorTable {
    u8 pad00[0x584];
    SectorPoint points[1];
} SectorTable;

extern s32 get_difficulty_level(void) __asm__("func_8007AAA0");
extern void func_80082D60(SectorTable *table, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6,
                          s32 a7, s32 mask);
extern s32 test_point_outside_sector(f32 x, f32 y, f32 r, SectorPoint *point) __asm__("func_800941E0");
extern s32 D_801C9174;

void dispatch_nearby_sector_mask(SectorTable *table, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6,
                                 s32 a7, f32 *pos, f32 radius) __asm__("func_80084DF4");

void dispatch_nearby_sector_mask(SectorTable *table, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6,
                                 s32 a7, f32 *pos, f32 radius) {
    u8 mask = 0;
    s32 count = get_difficulty_level();
    s32 i;

    for (i = 0; i < count; i++) {
        f32 x = pos[1];
        SectorPoint *point = &table->points[i];
        f32 dx = point->value24 - x;
        f32 y = pos[0];
        f32 dy = point->value20 - y;
        s32 inRange = 0;

        if (dx * dx + dy * dy < D_801C9174) {
            inRange = 1;
        }
        if (inRange && test_point_outside_sector(x, y, radius, point) == 0) {
            mask |= 1 << i;
        }
    }
    if (mask) {
        func_80082D60(table, a1, a2, a3, a4, a5, a6, a7, mask);
    }
}
