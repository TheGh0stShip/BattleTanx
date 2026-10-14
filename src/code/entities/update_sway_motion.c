#include "types.h"

typedef struct SwayState {
    u8 pad00[0x74];
    f32 value74;
    u8 pad78[0x4];
    f32 value7C;
    u8 pad80[0x38C - 0x80];
    f32 value38C;
    f32 value390;
    u8 pad394[0x3B4 - 0x394];
    f32 value3B4;
    u8 pad3B8[0x3C8 - 0x3B8];
    f32 value3C8;
    f32 value3CC;
    f32 value3D0;
    f32 value3D4;
    f32 value3D8;
    f32 value3DC;
    f32 value3E0;
    f32 value3E4;
    f32 value3E8;
    f32 value3EC;
} SwayState;

extern f32 random_float_range(f32 range) __asm__("func_800F3880");
extern f32 D_802D8150;
extern f32 D_802D8154;

void update_sway_motion(SwayState *s) __asm__("func_80099A08");

void update_sway_motion(SwayState *s) {
    f32 v;
    f32 w;

    if (s->value3E8 != 0.0) {
        s->value3E8 -= s->value3EC;
        s->value3EC += 0.75;
        if (s->value3E8 < 0.0) {
            s->value3E8 = 0.0f;
            s->value3EC = 0.0f;
        }
        if (s->value3E8 > 8.0) {
            s->value3E8 = 8.0f;
        }
    }
    D_802D8150 -= s->value38C * s->value74 + s->value390 * s->value7C;
    D_802D8154 -= s->value38C * s->value7C + s->value390 * -s->value74;
    s->value3D0 += D_802D8150 / 30.0f;
    s->value3D4 += D_802D8154 / 30.0f;
    if (s->value3B4 != 0.0f) {
        s->value3C8 += random_float_range(0.5f) - 0.25f;
        s->value3CC += random_float_range(0.5f) - 0.25f;
    }
    s->value3C8 += s->value3D0;
    s->value3CC += s->value3D4;
    s->value3D0 -= s->value3C8 / 1.3f;
    s->value3D4 -= s->value3CC / 1.3f;
    s->value3D0 -= s->value3D0 / 2.5f;
    s->value3D4 -= s->value3D4 / 2.5f;
    v = s->value3C8;
    if (v > 10.0f) {
        v = 10.0f;
    }
    s->value3C8 = v;
    if (v < -10.0f) {
        v = -10.0f;
    }
    s->value3C8 = v;
    w = s->value3CC;
    if (w > 10.0f) {
        w = 10.0f;
    }
    s->value3CC = w;
    if (w < -10.0f) {
        w = -10.0f;
    }
    s->value3CC = w;
    s->value3D8 = random_float_range(s->value3E0) - s->value3E0 / 2.0f;
    s->value3DC = random_float_range(s->value3E4) - s->value3E4 / 2.0f;
    s->value3E0 -= s->value3E0 / 10.0f;
    s->value3E4 -= s->value3E4 / 10.0f;
}
