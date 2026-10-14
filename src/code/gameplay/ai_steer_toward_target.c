#include "types.h"

typedef struct SteerCommand {
    s32 value00;
    f32 turn;
    f32 drive;
} SteerCommand;

typedef struct SteerUnit {
    u8 pad00[0x14];
    u16 flags;
    u8 pad16[0x2];
    s32 kind;
    u8 pad1C[0x3FC - 0x1C];
    f32 targetHeading;
    f32 heading;
} SteerUnit;

extern void func_800E21E4(SteerUnit *unit, SteerCommand *out, void *target);
extern void func_800E28DC(SteerUnit *unit, void *target, s32 *angle, s32 arg3, s32 arg4);

void ai_steer_toward_target(SteerUnit *unit, SteerCommand *out, void *target) __asm__("func_800E2AF0");

void ai_steer_toward_target(SteerUnit *unit, SteerCommand *out, void *target) {
    s32 hasTarget = 1;
    s32 angle;
    s32 magnitude;
    f32 rate;

    if (target == 0) {
        s32 diff = (u16)(u32)(unit->heading * 182.04445f) - (u16)(u32)(unit->targetHeading * 182.04445f);

        if (diff > 0) {
            if (diff > 0x8000) {
                angle = diff - 0xFFFF;
            } else {
                angle = diff;
            }
        } else if (diff < -0x8000) {
            angle = diff + 0xFFFF;
        } else {
            angle = diff;
        }
        hasTarget = 0;
    } else {
        func_800E28DC(unit, target, &angle, 0, 0);
    }

    magnitude = (angle >= 0) ? angle : -angle;
    if (magnitude < 600) {
        rate = magnitude / 600.0f;
    } else {
        rate = 1.0f;
    }

    if (hasTarget) {
        if (magnitude < 400) {
            func_800E21E4(unit, out, target);
        }
    }

    if (unit->kind == 1) {
        rate *= 40.0f;
        if (angle < 0) {
            out->turn = rate;
        } else {
            out->turn = -rate;
        }
    } else {
        if (!(unit->flags & 4)) {
            rate *= 135.0f;
        }
        if (angle < 0) {
            out->drive = -rate;
        } else {
            out->drive = rate;
        }
    }
}
