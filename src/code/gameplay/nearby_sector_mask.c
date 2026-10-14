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
extern s32 test_point_outside_sector(f32 x, f32 y, f32 r, SectorPoint *point) __asm__("func_800941E0");
extern s32 D_801C9174;

u8 nearby_sector_mask(SectorTable *table, f32 x, f32 y, f32 radius) __asm__("func_8008488C");

u8 nearby_sector_mask(SectorTable *table, f32 x, f32 y, f32 radius) {
    u8 mask = 0;
    s32 count = get_difficulty_level();
    s32 i;
    s32 j;

    for (i = 0; i < count; i++) {
        SectorPoint *point;

        j = 0;
        point = &table->points[i];
        for (; j < 4; j++) {
            f32 dx = point->value24 - x;
            f32 dy = point->value20 - y;
            s32 inRange = 0;

            if (dx * dx + dy * dy < D_801C9174) {
                inRange = 1;
            }
            if (inRange) {
                if (test_point_outside_sector(x, y, radius, point) == 0) {
                    mask |= 1 << i;
                }
                break;
            }
        }
    }
    return mask;
}
