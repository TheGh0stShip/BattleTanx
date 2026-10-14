#include "types.h"

typedef struct SteeringUnit {
    u8 pad000[0x24];
    f32 x;
    u8 pad028[0x4];
    f32 z;
    u8 pad030[0x4];
    f32 heading;
    u8 pad038[0x404 - 0x38];
    s8 leftDrive;
    s8 rightDrive;
} SteeringUnit;

extern f32 angle_sin(u16 angle) __asm__("func_800F3AE0");
extern f32 angle_cos(u16 angle) __asm__("func_800F3B40");

void steer_unit_toward_point(SteeringUnit *unit, f32 targetX, f32 targetZ, u16 targetAngle) __asm__("func_8009C8C8");

void steer_unit_toward_point(SteeringUnit *unit, f32 targetX, f32 targetZ, u16 targetAngle)
{
    f32 turn;
    f32 sinHeading;
    f32 cosHeading;
    f32 forward;
    f32 steer;

    turn = targetAngle * (360.0f / 65536.0f) - unit->heading;
    if (turn < -180.0f) {
        turn += 360.0f;
    }
    if (turn > 180.0f) {
        turn -= 360.0f;
    }
    sinHeading = angle_sin((u32)(unit->heading * 182.04445f));
    cosHeading = angle_cos((u32)(unit->heading * 182.04445f));
    forward = (sinHeading * (targetX - unit->x) + cosHeading * (targetZ - unit->z)) * 13.0f;
    steer = turn * 0.0055555557f;
    unit->leftDrive = forward + steer;
    unit->rightDrive = forward - steer;
}
