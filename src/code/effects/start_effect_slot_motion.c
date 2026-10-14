#include "types.h"

typedef struct OffsetPair {
    f32 y;
    f32 x;
} OffsetPair;

typedef struct MotionEffect {
    u8 pad00[0x10];
    s32 state;
    u8 pad14[4];
    s32 motion;
    f32 y;
    f32 x;
    s32 expireTick;
    s32 value28;
    s32 value2C;
} MotionEffect;

extern s32 create_effect_motion(MotionEffect *owner, s32 x, s32 y, s32 minX, s32 maxX, s32 minY,
                                s32 maxY, s32 mode, s32 flags) __asm__("func_80106D18");
extern void release_effect(MotionEffect *effect) __asm__("func_8008B89C");
extern s32 gGameTicks __asm__("D_801B4AA8");
extern OffsetPair D_801266D0[];

void start_effect_slot_motion(MotionEffect *effect, f32 x, f32 y, s32 slot) __asm__("func_800A6FC0");

void start_effect_slot_motion(MotionEffect *effect, f32 x, f32 y, s32 slot) {
    effect->state = 2;
    effect->value2C = 0;
    if (effect->motion == -1) {
        effect->motion = create_effect_motion(effect, x + D_801266D0[slot].x, y + D_801266D0[slot].y,
                                              -20, 20, -20, 20, 2, 0);
        effect->x = x + D_801266D0[slot].x;
        effect->y = y + D_801266D0[slot].y;
        effect->expireTick = gGameTicks + 0x78;
        release_effect(effect);
        effect->value28 = 0;
    }
}
