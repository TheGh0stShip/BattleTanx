#include "types.h"

typedef struct Vec2f {
    f32 x;
    f32 z;
} Vec2f;

typedef struct Corners {
    Vec2f points[4];
} Corners;

typedef struct EffectKind03 {
    u8 pad00[0xC];
    Vec2f pos;
    u8 pad14[0x4];
    s32 kind;
    s32 handle;
    u8 value20;
    u8 pad21[0x3];
    s32 value24;
    s32 expireTick;
    s32 value2C;
    u8 value30;
} EffectKind03;

extern EffectKind03 *allocate_effect(s32 group, s32 kind, s32 size) __asm__("func_8008AD10");
extern s32 func_80106D18(EffectKind03 *, s32, s32, s32, s32, s32, s32, s32, s32);
extern Corners D_80071E64;
extern u8 D_80134E65;
extern u8 D_80134E69;
extern s32 gGameTicks __asm__("D_801B4AA8");
extern u8 gWeightTable[] __asm__("D_802D5BA0");
extern u8 D_802D5BB7;

s32 spawn_effect_kind_03(f32 *pos, s32 kind, s32 duration, s32 value) __asm__("func_800911A0");

s32 spawn_effect_kind_03(f32 *pos, s32 kind, s32 duration, s32 value)
{
    Vec2f corners[4];
    Corners offsets;
    EffectKind03 *effect;
    Vec2f *center;
    s32 i;

    if (kind != 0) {
        if (kind == 5) {
            if (D_80134E69 != 0) {
                return 0;
            }
        } else if (D_80134E65 == 0) {
            return 0;
        }
    }
    effect = allocate_effect(duration > 0, 3, 0x34);
    if (effect == 0) {
        return -1;
    }
    if ((kind != 1) & (duration == 0)) {
        gWeightTable[kind]++;
        D_802D5BB7++;
    }
    effect->kind = kind;
    effect->value20 = 0;
    effect->pos.z = pos[1];
    effect->pos.x = pos[0];
    center = &effect->pos;
    offsets = D_80071E64;
    for (i = 0; i < 4; i++) {
        corners[i].z = offsets.points[i].z + center->z;
        corners[i].x = offsets.points[i].x + center->x;
    }
    effect->handle = func_80106D18(effect, effect->pos.z, effect->pos.x, -0x23, 0x23, -0x23, 0x23, 2, 0);
    if (duration > 0) {
        effect->expireTick = gGameTicks + duration;
    } else {
        effect->expireTick = 0;
    }
    effect->value24 = 0;
    effect->value2C = value;
    effect->value30 = 0xFF;
    return 0;
}
