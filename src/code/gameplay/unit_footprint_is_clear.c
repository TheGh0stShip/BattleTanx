#include "types.h"

typedef struct AreaBox {
    s16 bounds[12];
} AreaBox;

typedef struct Unit {
    u8 pad00[0x18];
    s32 kind;
    u8 pad1C[0x8];
    f32 x;
    u8 pad28[0x4];
    f32 z;
    u8 pad30[0x4];
    f32 heading;
    u8 pad38[0x4CC];
    void *self;
} Unit;

extern void init_area_box(
    AreaBox *box, s32 x, s32 z, s32 minX, s32 maxX, s32 minZ, s32 maxZ, s32 angle)
    __asm__("func_80109268");
extern u8 find_objects_in_area(AreaBox *box, s32 capacity, void **results, s32 *count)
    __asm__("func_80107A14");
s32 unit_footprint_is_clear(Unit *unit) __asm__("func_800A0218");

s32 unit_footprint_is_clear(Unit *unit)
{
    AreaBox box;
    void *results[16];
    s32 count;
    u16 angle = (u32)(unit->heading * 182.04445f);
    f32 x = unit->x;
    f32 z = unit->z;

    switch ((u32)unit->kind) {
    case 0:
        init_area_box(&box, x, z, -0x23, 0x23, -0x49, 0x51, angle);
        break;
    case 1:
        init_area_box(&box, x, z, -0x1A, 0x1A, -0x26, 0x1A, angle);
        break;
    case 2:
        init_area_box(&box, x, z, -0x3C, 0x3C, -0x4B, 0x51, angle);
        break;
    }
    find_objects_in_area(&box, 16, results, &count);
    if (count == 0 || (count == 1 && results[0] == unit->self)) {
        return 1;
    }
    return 0;
}
