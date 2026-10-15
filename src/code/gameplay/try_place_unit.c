#include "types.h"

typedef struct AreaBox {
    s16 bounds[12];
} AreaBox;

typedef struct Unit {
    u8 pad000[0x18];
    u32 kind;
    u8 pad01C[8];
    f32 x;
    u8 pad028[4];
    f32 z;
    u8 pad030[4];
    f32 angle;
    u8 pad038[0x34C];
    f32 lastX;
    f32 lastZ;
    u8 pad38C[0x70];
    f32 heading;
    f32 aimHeading;
    u8 pad404[0xA0];
    s32 areaHandle;
    u8 pad4A8[0x5C];
    s32 body;
} Unit;

extern void build_area_box(AreaBox *box, s32 x, s32 z, s32 minX, s32 maxX, s32 minZ, s32 maxZ, s32 angle)
    __asm__("func_80109268");
extern u8 find_objects_in_area(AreaBox *box, s32 capacity, s32 *results, s32 *count) __asm__("func_80107A14");
extern void func_80107170(s32 handle);
extern s32 func_80106D18(s32 body, s32 x, s32 z, s32 minX, s32 maxX, s32 minZ, s32 maxZ, s32 flags, s32 angle);

static inline void build_unit_box(AreaBox *box, u32 kind, f32 x, f32 z, u16 angle) {
    switch (kind) {
    case 0:
        build_area_box(box, x, z, -35, 35, -73, 81, angle);
        break;
    case 1:
        build_area_box(box, x, z, -26, 26, -38, 26, angle);
        break;
    case 2:
        build_area_box(box, x, z, -60, 60, -75, 81, angle);
        break;
    }
}

s32 try_place_unit(Unit *unit, f32 x, f32 z, u16 angle) __asm__("func_8009FEE0");

s32 try_place_unit(Unit *unit, f32 x, f32 z, u16 angle) {
    AreaBox box;
    s32 results[16];
    s32 count;
    f32 heading;

    build_unit_box(&box, unit->kind, x, z, angle);
    find_objects_in_area(&box, 16, results, &count);
    if (count == 0 || (count == 1 && results[0] == unit->body)) {
        unit->x = x;
        unit->z = z;
        unit->lastX = unit->x;
        unit->lastZ = unit->z;
        heading = angle * 0.0054931640625f;
        unit->angle = heading;
        unit->aimHeading = heading;
        unit->heading = heading;
        func_80107170(unit->areaHandle);
        switch (unit->kind) {
        case 0:
            unit->areaHandle = func_80106D18(unit->body, unit->x, unit->z, -35, 35, -73, 81, 0x4D6, angle);
            break;
        case 1:
            unit->areaHandle = func_80106D18(unit->body, unit->x, unit->z, -26, 26, -38, 26, 0x4D6, angle);
            break;
        case 2:
            unit->areaHandle = func_80106D18(unit->body, unit->x, unit->z, -60, 60, -75, 81, 0x4D6, angle);
            break;
        }
        return 1;
    }
    return -1;
}
