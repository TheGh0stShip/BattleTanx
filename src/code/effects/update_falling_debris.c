#include "types.h"

typedef struct FallingDebris {
    u8 pad00[0xC];
    f32 pos[3];
    f32 vel[3];
    u16 value24;
    u16 pad26;
    u16 value28;
    u16 pad2A;
    f32 value2C;
    u8 pad30[4];
    u8 flags;
} FallingDebris;

extern void func_800ED8C0(f32 *pos, s32 kind);

void update_falling_debris(FallingDebris *debris, s32 *state) __asm__("func_8008EC80");

void update_falling_debris(FallingDebris *debris, s32 *state)
{
    debris->vel[1] -= debris->value2C * 0.35f;
    debris->pos[0] += debris->vel[0];
    debris->pos[2] += debris->vel[2];
    debris->pos[1] += debris->vel[1];
    if ((debris->flags & 1) && debris->vel[1] < 2.0) {
        func_800ED8C0(debris->pos, 5);
    } else {
        debris->pos[1] -= 1.0f;
        if (debris->pos[1] > 0.0f) {
            debris->value28 += (u16)(debris->value2C * 1280.0f);
            debris->value24 += (u16)(debris->value2C * 2048.0f);
            return;
        }
    }
    *state = 2;
}
