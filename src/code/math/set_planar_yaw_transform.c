#include "types.h"

typedef struct YawTransform {
    f32 m[12];
    s32 value30;
    s32 value34;
    s32 value38;
} YawTransform;

extern f32 angle_cos(u16 angle) __asm__("func_800F3B40");
extern f32 angle_sin(u16 angle) __asm__("func_800F3AE0");
extern f32 D_800730B4;

void set_planar_yaw_transform(YawTransform *xf, s32 x, s32 z, u16 angle) __asm__("func_800A76BC");

void set_planar_yaw_transform(YawTransform *xf, s32 x, s32 z, u16 angle) {
    xf->value30 = x;
    xf->value38 = z;
    if (angle != 0) {
        f32 c = angle_cos(angle);
        f32 s = angle_sin(angle);

        xf->m[8] = s;
        xf->m[0] = c;
        xf->m[10] = c;
        xf->m[2] = -s;
    } else {
        f32 one = D_800730B4;

        xf->m[2] = 0.0f;
        xf->m[8] = 0.0f;
        xf->m[0] = one;
        xf->m[10] = one;
    }
}
