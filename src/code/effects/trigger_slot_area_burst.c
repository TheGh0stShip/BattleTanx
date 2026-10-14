#include "types.h"

typedef struct {
    u8 pad00;
    s8 value01;
    u8 pad02[2];
    s32 value04;
    u8 pad08[0x54 - 0x08];
    u16 value54;
    u8 pad56[2];
} Slot58;

typedef struct {
    u8 pad00[0x568];
    Slot58 *slots;
} Session;

typedef struct {
    u8 pad00[0xC];
    f32 x;
    f32 y;
    f32 z;
    s16 slot;
    u8 pad1A[2];
    u8 triggered;
    u8 pad1D[3];
    s32 area;
    u8 burst;
} Obj;

typedef struct {
    f32 z;
    f32 x;
} Target;

typedef struct { f32 x, y, z; } Vec3;
typedef struct { u8 data[0x20]; } Corners;

extern float sqrtf(float);
extern Session *get_spawn_session(void) __asm__("func_800821C0");
extern void clear_record_halfword_flags(s32 index, u16 flags) __asm__("func_80106CCC");
extern s32 radians_to_angle(f32 radians) __asm__("func_800F3BE4");
extern void spawn_effect_kind_19(s32 a, s32 b, s32 c, s32 d, s32 e) __asm__("func_800F2E50");
extern f32 random_float_range(f32 range) __asm__("func_800F3880");
extern void spawn_kind24_burst(Vec3 *origin) __asm__("func_800F1E74");
extern void spawn_effect_kind_26(f32 *position, s32 variant) __asm__("func_800ED8C0");
extern void area_box_corners(s32 index, Corners *out) __asm__("func_80108E74");
extern void func_8008F248(Corners *c, s32 a, u16 angle, f32 b, f32 d, f32 e, s32 f);
extern f32 D_80074B04;
extern f32 D_80074B08;
extern f32 D_80074B0C;
extern f32 D_80074B10;

void trigger_slot_area_burst(Obj *obj, s32 unused, Target *target) __asm__("func_800ED380");

void trigger_slot_area_burst(Obj *obj, s32 unused, Target *target)
{
    Vec3 pos;
    Corners corners;
    Slot58 *slot;
    f32 dz;
    f32 dx;
    s32 angle;
    s32 i;
    s32 nonzero;
    f32 range;
    f32 offset;

    if (obj->triggered != 0) {
        return;
    }
    obj->triggered = 1;
    slot = &get_spawn_session()->slots[obj->slot];
    slot->value01 = 1;
    slot->value04 = 0x1C;
    slot->value54++;
    clear_record_halfword_flags(obj->area, 0x5D);
    dz = target->x - obj->x;
    dx = target->z - obj->z;
    nonzero = (dz != 0.0f) | (dx != 0.0f);
    angle = 0;
    if (nonzero) {
        if (-dz < 0.0f) {
            angle = -radians_to_angle(-dx / sqrtf(dz * dz + dx * dx));
        } else {
            angle = radians_to_angle(-dx / sqrtf(dz * dz + dx * dx));
        }
    }
    if (obj->burst != 0) {
        spawn_effect_kind_19(0x84, 0xFF, 0, 0xC, -1);
        i = 0;
        range = D_80074B04;
        offset = D_80074B08;
        do {
            pos.x = obj->x + random_float_range(range) - offset;
            pos.y = obj->y;
            pos.z = obj->z + random_float_range(range) - offset;
            i++;
            spawn_kind24_burst(&pos);
        } while (i < 4);
        spawn_effect_kind_26(&obj->x, 0x1B);
        return;
    }
    area_box_corners(obj->area, &corners);
    func_8008F248(&corners, 6, angle, 15.0f, D_80074B0C, D_80074B10, 0xF);
}
