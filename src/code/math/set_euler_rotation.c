#include "types.h"

extern f32 angle_cos(u16 angle) __asm__("func_800F3B40");
extern f32 angle_sin(u16 angle) __asm__("func_800F3AE0");

void set_euler_rotation(f32 *m, u16 yaw, u16 pitch, u16 roll) __asm__("func_800A7800");

void set_euler_rotation(f32 *m, u16 yaw, u16 pitch, u16 roll) {
    f32 sr = angle_sin(roll);
    f32 cr = angle_cos(roll);
    f32 sp = angle_sin(pitch);
    f32 cp = angle_cos(pitch);
    f32 sy = angle_sin(yaw);
    f32 cy = angle_cos(yaw);

    m[0] = cp * cy;
    m[1] = cp * sy;
    m[2] = -sp;
    m[4] = sr * sp * cy - cr * sy;
    m[5] = sr * sp * sy + cr * cy;
    m[6] = sr * cp;
    m[8] = cr * sp * cy + sr * sy;
    m[9] = cr * sp * sy - sr * cy;
    m[10] = cr * cp;
}
