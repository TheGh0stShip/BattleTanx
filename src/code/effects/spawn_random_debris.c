#include "types.h"

typedef struct PartRecord PartRecord;

extern u32 random_u32(void) __asm__("func_800F38F4");
extern void spawn_part_debris(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 angleX, s32 angleY, s32 angleZ,
                              s32 arg7, s32 arg8, s32 arg9, f32 arg10, PartRecord *part, s32 arg12,
                              s32 arg13) __asm__("func_8008F6F4");
extern f32 D_80071CE8;

void spawn_random_debris(s32 arg0, s32 count) __asm__("func_800902BC");

void spawn_random_debris(s32 arg0, s32 count) {
    s32 i;
    s32 angleX;
    s32 angleY;
    s32 angleZ;
    s32 spin;

    for (i = 0; i < count; i++) {
        angleX = (random_u32() % 1280) & 0xFFFF;
        angleY = (random_u32() % 1280) & 0xFFFF;
        angleZ = (random_u32() % 1280) & 0xFFFF;
        spin = (random_u32() % 65535) & 0xFFFF;
        spawn_part_debris(arg0, 0, 0, 0, angleX, angleY, angleZ, spin, 0x2000, 0,
                          D_80071CE8, 0, 0, 0x12);
    }
}
