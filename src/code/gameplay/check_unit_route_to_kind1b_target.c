#include "types.h"

typedef struct NearestBuffer {
    u8 data[0x200];
} NearestBuffer;

typedef struct PlanarPoint {
    f32 value0;
    f32 value4;
} PlanarPoint;

typedef struct ReachTarget {
    u8 pad00[0x4];
    s32 owner;
    s32 kind;
    u8 pad0C[0x10];
    PlanarPoint position;
    u8 pad24[0x8];
    s16 count;
} ReachTarget;

typedef struct ReachUnit {
    u8 pad000[0x24];
    f32 value24;
    u8 pad028[0x4];
    f32 value2C;
    u8 pad030[0x316];
    u16 value346;
} ReachUnit;

extern void initialize_bitstream_header(NearestBuffer *header) __asm__("func_800DDCA4");
extern void func_800DE1B4(NearestBuffer *header, u16 limit);
extern u16 func_800DE664(NearestBuffer *header, PlanarPoint *from, PlanarPoint *to, s32 a3, s32 a4);

s32 check_unit_route_to_kind1b_target(ReachUnit *unit, ReachTarget *object, s32 owner) __asm__("func_800E3C34");

s32 check_unit_route_to_kind1b_target(ReachUnit *unit, ReachTarget *object, s32 owner) {
    NearestBuffer buffer;
    PlanarPoint point;
    ReachTarget *target;

    if (object == 0) {
        return 0;
    }
    if (object->kind != 0x1B) {
        return 0;
    }
    target = object;
    if (target->count <= 0) {
        return 0;
    }
    if (owner != 0 && target->owner != owner) {
        return 0;
    }
    point.value4 = unit->value24;
    point.value0 = unit->value2C;
    initialize_bitstream_header(&buffer);
    func_800DE1B4(&buffer, unit->value346 * 3);
    return func_800DE664(&buffer, &point, &target->position, 1, 0) != 0;
}
