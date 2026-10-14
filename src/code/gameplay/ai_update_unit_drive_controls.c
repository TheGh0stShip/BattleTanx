#include "types.h"

typedef struct DriveTracker {
    u8 pad00[0x8];
    f32 distance;
    f32 delta;
    u8 pad10[0x5];
    u8 approaching;
} DriveTracker;

typedef struct DriveUnit {
    u8 pad000[0x4];
    u8 ownerId;
    u8 pad005[0x13];
    s32 kind;
    u8 pad01C[0x8];
    f32 position[3];
    u8 pad030[0x6C];
    u32 state;
    f32 *target;
    u8 targetPoint[0x8];
    struct DriveUnit *leader;
    u8 pad0B0[0x4];
    s32 value0B4;
    u8 pad0B8[0x84];
    u16 value13C;
    u8 pad13E[0x1F6];
    DriveTracker tracker;
    u8 pad34C[0x5];
    u8 delay;
    u8 pad352[0x9];
    u8 value35B;
    u8 pad35C[0x2];
    u16 range;
} DriveUnit;

typedef struct DriveOwner {
    u8 pad000[0x31C];
    f32 speed;
} DriveOwner;

extern s32 abs(s32 value);
extern f32 D_800745D4;
extern f32 D_800745D8;
extern f32 D_800745DC;
extern f32 D_800745E0;
extern f32 D_800745E4;
extern f32 D_800745E8;
extern f32 D_800745EC;
extern f32 D_800745F0;

extern DriveOwner *get_entity_record(u16 index) __asm__("func_800A6688");
extern f32 approx_xz_distance(void *a, void *b) __asm__("func_800E0D54");
extern f32 ai_horizontal_distance(f32 *a, f32 *b) __asm__("func_800E0C8C");
extern f32 ai_member_horizontal_distance(DriveUnit *unit, void *point) __asm__("func_800E1A20");
extern void ai_measure_relative_point(DriveUnit *unit, f32 *point, s32 *bodyDelta, s32 *headDelta, s32 arg4)
    __asm__("func_800E28DC");
extern f32 ai_get_indexed_float(DriveUnit *unit, s32 key) __asm__("func_800E9854");
extern void ai_set_indexed_float(DriveUnit *unit, s32 key, f32 value) __asm__("func_800E986C");

void ai_update_unit_drive_controls(DriveUnit *unit, f32 *out) __asm__("func_800E2DE8");

void ai_update_unit_drive_controls(DriveUnit *unit, f32 *out)
{
    f32 point[2];
    s32 angle;
    f32 *target;
    f32 speed;
    f32 turn;
    f32 throttle;
    f32 distance;
    s32 delta;
    s32 limit;
    s32 diff;
    s32 near;
    f32 current;
    f32 num;
    f32 den;
    DriveTracker *tracker;

    throttle = 0.0f;
    turn = throttle;
    speed = get_entity_record(unit->ownerId)->speed;
    if (unit->value35B == 0 && unit->value13C < 2) {
        return;
    }
    if (unit->delay != 0) {
        unit->delay--;
        return;
    }
    switch (unit->state) {
    case 0:
        if (unit->target == 0) {
            goto output;
        }
        break;
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
        break;
    default:
        goto output;
    }
    target = unit->target;
    if (target == 0) {
        goto output;
    }
    if (ai_get_indexed_float(unit, 0x1003) > 0.0f) {
        goto output;
    }
    point[1] = unit->position[0];
    point[0] = unit->position[2];
    ai_measure_relative_point(unit, target, 0, &angle, 0);
    delta = abs(angle);
    limit = 0x2000;
    if (unit->kind == 1) {
        limit = 0x1000;
    }
    if (delta >= limit) {
        turn = 0.0f;
    } else {
        diff = limit - delta;
        num = diff;
        num = num * (num * num);
        den = limit;
        turn = num / (den * (den * den));
    }
    switch (unit->state) {
    case 6:
        distance = ai_member_horizontal_distance(unit, unit->targetPoint);
        break;
    case 7:
        distance = ai_member_horizontal_distance(unit, unit->targetPoint);
        break;
    case 5:
        distance = approx_xz_distance(unit->position, unit->leader->position);
        break;
    default:
        distance = D_800745D4;
        break;
    }
    near = distance < unit->range;
    if (!near || unit->value0B4 == 0) {
        tracker = &unit->tracker;
        if (tracker->approaching) {
            if (tracker->distance < D_800745D8) {
                throttle = (turn + (D_800745DC - tracker->distance / D_800745D8)) / D_800745E0;
            } else {
                throttle = turn;
            }
        } else {
            throttle = turn;
        }
        current = ai_horizontal_distance(point, target);
        tracker->delta = current - tracker->distance;
        tracker->distance = current;
        if (tracker->delta < 0.0f) {
            tracker->approaching = 1;
        }
    }
    turn = (D_800745E4 - turn) * D_800745E8;
    if (angle > 0) {
        turn = -turn;
    }
output:
    out[1] = turn;
    out[0] = throttle * D_800745EC * speed / D_800745F0;
    ai_set_indexed_float(unit, 0x1008, throttle);
    ai_set_indexed_float(unit, 0x1009, 0.0f);
}
