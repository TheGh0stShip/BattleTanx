#include "types.h"

typedef struct PlanarMotion {
    f32 accelScale;
    f32 turnScale;
    f32 pad08;
    f32 x;
    f32 z;
    f32 velX;
    f32 velZ;
    f32 heading;
    f32 turnRate;
    f32 accelX;
    f32 accelZ;
    f32 turnAccel;
} PlanarMotion;

extern f64 D_800721D0;

void advance_wrapped_planar_motion(PlanarMotion *motion, f32 dt) __asm__("func_80097C64");

/* Integrates velocity and heading by dt, zeroing slow velocity axes and wrapping heading to [0, 360]. */
void advance_wrapped_planar_motion(PlanarMotion *motion, f32 dt)
{
    f32 velX;
    f32 velZ;

    motion->velX += motion->accelScale * motion->accelX * dt;
    motion->velZ += motion->accelScale * motion->accelZ * dt;
    velX = motion->velX;
    motion->velX = ((velX < 0.0f ? -velX : velX) < D_800721D0) ? 0.0f : velX;
    velZ = motion->velZ;
    motion->velZ = ((velZ < 0.0f ? -velZ : velZ) < D_800721D0) ? 0.0f : velZ;
    motion->turnRate += motion->turnScale * motion->turnAccel * dt;
    motion->x += motion->velX * dt;
    motion->z += motion->velZ * dt;
    motion->heading += motion->turnRate * dt;
    if (motion->heading > 360.0f) {
        do {
            motion->heading -= 360.0f;
        } while (motion->heading > 360.0f);
    }
    while (motion->heading < 0.0f) {
        motion->heading += 360.0f;
    }
}
