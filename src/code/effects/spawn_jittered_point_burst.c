#include "types.h"

extern f32 random_float_range(f32 range) __asm__("func_800F3880");
extern void func_800F195C(f32 *origin, f32 *position, s32 arg2, s32 arg3, u8 byte0, u8 byte1, u8 byte2);
extern f32 D_80074DE0;
extern f32 D_80074DE4;

void spawn_jittebyte0_point_burst(f32 *origin, u8 byte0, u8 byte1, u8 byte2) __asm__("func_800F1BB4");

void spawn_jittebyte0_point_burst(f32 *origin, u8 byte0, u8 byte1, u8 byte2) {
    f32 range = D_80074DE0;
    f32 offset = D_80074DE4;
    f32 position[3];
    s32 i;

    for (i = 0; i < 15; i++) {
        position[0] = origin[0] + random_float_range(range) - offset;
        position[1] = origin[1] + random_float_range(range) - offset;
        position[2] = origin[2] + random_float_range(range) - offset;
        func_800F195C(origin, position, 12, 0, byte0, byte1, byte2);
    }
}
