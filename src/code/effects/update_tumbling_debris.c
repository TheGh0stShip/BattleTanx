#include "types.h"

typedef struct {
    u8 pad00[0xC];
    f32 pos[3];
    u8 pad18[0xC];
    f32 vel[3];
    u16 rot[3];
    u16 spin[3];
    u8 pad3C[4];
    u8 flags;
} TumblingDebris;

extern void func_800ED8C0(f32 *pos, s32 sound);
extern u32 next_random_u32(void) __asm__("func_800F38F4");
extern f32 gDebrisGravity __asm__("D_80071CDC");

void update_tumbling_debris(TumblingDebris *d, s32 *state) __asm__("func_8008FB1C");

void update_tumbling_debris(TumblingDebris *d, s32 *state) {
    u8 flags;

    if (d->flags & 8) {
        if (!(next_random_u32() & 0xF)) {
            d->vel[0] = -d->vel[0];
            d->vel[2] = -d->vel[2];
        }
    } else {
        d->vel[1] -= gDebrisGravity;
    }
    flags = d->flags;
    d->pos[0] += d->vel[0];
    d->pos[1] += d->vel[1];
    d->pos[2] += d->vel[2];
    if (flags & 2) {
        d->flags = flags ^= 4;
        if (flags & 4) {
            func_800ED8C0(d->pos, (flags & 0x10) ? 0x19 : 0x15);
        }
    }
    if ((!(d->vel[1] < 0.0f) || (!(d->flags & 1) && ((d->flags & 0xA) || (next_random_u32() & 7)))) && (d->pos[1] > 0.0f)) {
        d->rot[0] += d->spin[0];
        d->rot[1] += d->spin[1];
        d->rot[2] += d->spin[2];
        return;
    }
    *state = 2;
}
