#include "types.h"

typedef struct ViewVec3 {
    f32 x;
    f32 y;
    f32 z;
} ViewVec3;

typedef struct ViewMtx {
    f32 m[4][4];
} ViewMtx;

typedef struct ViewState {
    u8 pad00[0x24];
    ViewVec3 translation;
    ViewVec3 angles;
    u8 pad3C[0x3D8 - 0x3C];
    f32 pitch;
    f32 roll;
    u8 pad3E0[0x3F8 - 0x3E0];
    f32 yaw;
    f32 targetYaw;
    u8 pad400[0xC];
    ViewMtx matrix;
} ViewState;

typedef struct ViewOwner {
    u8 pad00[0xC];
    ViewState *state;
} ViewOwner;

extern void euler_angles_to_matrix(f32 m[4][4], ViewVec3 *angles) __asm__("func_800A7964");
extern void load_render_translation(void *target, ViewVec3 *vector) __asm__("func_800A76A0");

void build_mode_view_matrix(ViewOwner *owner, s32 unused, s32 *mode, f32 out[4][4]) __asm__("func_8009F18C");

/* Mode 0 uses stored angles, mode 1 copies a stored matrix, mode 2 snaps yaw toward its target. */
void build_mode_view_matrix(ViewOwner *owner, s32 unused, s32 *mode, f32 out[4][4])
{
    ViewState *state = owner->state;
    ViewVec3 angles;
    ViewVec3 base;
    f32 delta;

    switch ((u32)*mode) {
    case 0:
        euler_angles_to_matrix(out, &state->angles);
        break;
    case 1:
        *(ViewMtx *)out = state->matrix;
        return;
    case 2:
        base.x = state->pitch;
        base.y = 0.0f;
        base.z = state->roll;
        angles = base;
        delta = state->targetYaw - state->yaw;
        while (delta > 180.0) {
            delta -= 360.0;
        }
        while (delta < -180.0) {
            delta += 360.0;
        }
        if (delta > 0.0f) {
            state->yaw = state->targetYaw - 0.0f;
        } else if (delta < -0.0f) {
            state->yaw = state->targetYaw + 0.0f;
        }
        angles.y = state->yaw;
        euler_angles_to_matrix(out, &angles);
        break;
    default:
        return;
    }
    load_render_translation(out, &state->translation);
}
