#include "types.h"

typedef struct ColorCycleEffect {
    u8 pad00[0xC];
    u8 colors[6];
    u8 pad12[2];
    s32 duration;
    s32 timer;
    s32 mode;
} ColorCycleEffect;

extern ColorCycleEffect *allocate_effect(s32 group, s32 kind, s32 size) __asm__("func_8008AD10");
extern u8 random_color_component(void) __asm__("func_800F38F4");

void update_color_cycle_effect(ColorCycleEffect *effect, s32 *state) __asm__("func_800F30C8");

void update_color_cycle_effect(ColorCycleEffect *effect, s32 *state) {
    ColorCycleEffect *next;
    s32 mode;

    if (++effect->timer < effect->duration) {
        return;
    }
    *state = 2;
    mode = effect->mode;
    switch (mode) {
    case 0:
        return;
    case 1: {
        u8 a = effect->colors[3];
        u8 b = effect->colors[4];
        u8 c = effect->colors[5];
        u8 d = effect->colors[0];
        u8 e = effect->colors[1];
        u8 g = effect->colors[2];
        s32 duration = effect->duration;

        next = allocate_effect(1, 0x20, 0x20);
        if (next == 0) {
            return;
        }
        next->colors[0] = a;
        next->colors[1] = b;
        next->colors[2] = c;
        next->colors[3] = d;
        next->colors[4] = e;
        next->colors[5] = g;
        next->duration = duration;
        next->timer = 0;
        next->mode = mode;
        break;
    }
    case 2: {
        u8 r = random_color_component();
        u8 g = random_color_component();
        u8 b = random_color_component();
        u8 a = effect->colors[3];
        u8 c = effect->colors[4];
        u8 d = effect->colors[5];
        s32 duration = effect->duration;
        s32 nextMode = effect->mode;

        next = allocate_effect(1, 0x20, 0x20);
        if (next == 0) {
            return;
        }
        next->colors[0] = a;
        next->colors[1] = c;
        next->colors[2] = d;
        next->colors[3] = r;
        next->colors[4] = g;
        next->colors[5] = b;
        next->duration = duration;
        next->timer = 0;
        next->mode = nextMode;
        break;
    }
    }
}
