#include "types.h"

extern float sqrtf(float);

typedef struct BlastSource {
    f32 z;
    f32 x;
    s32 radius;
    s32 value0C;
} BlastSource;

typedef struct BlastTarget {
    u8 pad00[0x4];
    u8 value04;
    u8 pad05[0x18 - 0x5];
    s32 value18;
    s32 value1C;
    u8 pad20[0x4];
    f32 value24[3];
    u8 pad30[0x4];
    f32 value34;
    u8 pad38[0x3D0 - 0x38];
    f32 value3D0;
} BlastTarget;

typedef struct BlastWatch {
    u8 pad00[0xC];
    BlastTarget *target;
    u8 triggered;
} BlastWatch;

typedef struct LinkedEntityInfo {
    u8 pad000[0x1BF];
    u8 value1BF;
} LinkedEntityInfo;

extern LinkedEntityInfo *get_linked_entity(u8 id) __asm__("func_800A6688");
extern void func_800983E0(BlastTarget *target, s32 amount, s32 arg2, s32 arg3);
extern void spawn_group_part_debris_mode(s32 group, f32 *pos, u16 arg2, u16 arg3, u16 arg4, s32 arg5,
                                         u8 mode) __asm__("func_800905D8");
extern void func_80097DD0(BlastTarget *target, s32 arg1, s32 arg2);
extern s16 D_802D5A5A;
extern s16 D_802D5A76;
extern s16 D_802D5A8E;

void apply_proximity_hit_to_target(BlastWatch *watch, s32 arg1, BlastSource *src) __asm__("func_8009F36C");

void apply_proximity_hit_to_target(BlastWatch *watch, s32 arg1, BlastSource *src) {
    BlastTarget *target;
    f32 dx;
    f32 dz;
    f32 distSq;
    f32 dist;
    s32 amount;
    s32 group;
    u8 mode;

    if (watch->triggered != 0) {
        return;
    }
    target = watch->target;
    dx = src->x - target->value24[0];
    dz = src->z - target->value24[2];
    distSq = dx * dx + dz * dz;
    if (distSq < src->radius) {
        watch->triggered = 1;
        dist = sqrtf(distSq);
        amount = 50;
        if (!(dist > 4000.0f)) {
            amount = (s32)((1.0f - dist / 4000.0f) * 50.0f) + 50;
        }
        func_800983E0(target, amount, src->value0C, 0);
        if (target->value1C == 0) {
            switch (target->value18) {
            case 1:
                group = D_802D5A76;
                break;
            case 2:
                group = D_802D5A8E;
                break;
            default:
                group = D_802D5A5A;
                break;
            }
            mode = get_linked_entity(target->value04)->value1BF;
            spawn_group_part_debris_mode(group, target->value24, 0, (u32)(target->value34 * 182.04445f), 0,
                                         mode, 0);
            target->value1C = -1;
            func_80097DD0(target, -1, 0);
        }
        target->value3D0 -= 6.0;
    }
}
