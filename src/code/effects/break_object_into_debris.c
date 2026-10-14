#include "types.h"

typedef struct {
    u8 pad00[0xC];
    u32 kind;
    f32 position[3];
    u16 value1C;
    u8 pad1E[0x7];
    u8 value25;
    u8 value26;
} DebrisObject;

extern float sqrtf(float);
extern void release_effect(DebrisObject *effect) __asm__("func_8008B89C");
extern s32 radians_to_angle(f32 radians) __asm__("func_800F3BE4");
extern void spawn_group_part_debris(s32 group, f32 *position, u16 arg2, u16 arg3, u16 arg4, u16 arg5, s32 arg6) __asm__("func_80090428");
extern s16 D_802D5A5A;
extern s16 D_802D5A76;
extern s16 D_802D5A8E;
extern s16 D_802D5AC0;

void break_object_into_debris(DebrisObject *object, s32 unused, f32 *point) __asm__("func_800A0930");

void break_object_into_debris(DebrisObject *object, s32 unused, f32 *point) {
    f32 dy;
    f32 dx;
    s32 heading;
    s32 group;

    if (object->value25 != 0) {
        return;
    }
    release_effect(object);
    dy = point[1] - object->position[0];
    dx = point[0] - object->position[2];
    if ((dy != 0.0f) | (dx != 0.0f)) {
        if (-dy < 0.0f) {
            heading = -radians_to_angle(-dx / sqrtf(dy * dy + dx * dx));
        } else {
            heading = radians_to_angle(-dx / sqrtf(dy * dy + dx * dx));
        }
    } else {
        heading = 0;
    }
    switch (object->kind) {
    case 0:
        group = D_802D5A5A;
        break;
    case 2:
        group = D_802D5A8E;
        break;
    case 1:
        if (object->value25 != 0) {
            group = D_802D5AC0;
        } else {
            group = D_802D5A76;
        }
        break;
    default:
        group = 0;
        break;
    }
    spawn_group_part_debris(group, object->position, 0, object->value1C, 0, heading, object->value26);
}
