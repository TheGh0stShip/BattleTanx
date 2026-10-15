#include "types.h"

typedef struct AreaBox {
    s16 value00;
    s16 x;
    s16 y;
    s16 minA;
    s16 maxA;
    s16 minB;
    s16 maxB;
    s16 radius;
    s16 value10;
} AreaBox;

typedef struct AreaContact {
    u8 pad00[0x8];
    s32 value08;
} AreaContact;

typedef struct SpawnPos {
    f32 x;
    f32 y;
} SpawnPos;

typedef struct AreaEffect1D {
    u8 pad00[0xC];
    f32 x;
    f32 y;
    s32 motion;
    s32 spawnTime;
    s32 value1C;
    u8 pad20[0x4];
    s32 tag;
} AreaEffect1D;

extern u8 func_80107A14(AreaBox *box, s32 capacity, AreaContact **results, s32 *count);
extern AreaEffect1D *allocate_effect(s32 group, s32 kind, s32 size) __asm__("func_8008AD10");
extern s32 create_effect_motion(AreaEffect1D *effect, s32 x, s32 y, s32 minX, s32 maxX, s32 minY,
                                s32 maxY, s32 mode, s32 flags) __asm__("func_80106D18");
extern s32 D_801B4AA8;

s32 spawn_effect_kind1d_if_area_clear(SpawnPos *pos, s32 tag) __asm__("func_8010DAA0");

s32 spawn_effect_kind1d_if_area_clear(SpawnPos *pos, s32 tag) {
    AreaContact *results[16];
    AreaBox box;
    s32 count;
    s32 i;
    AreaEffect1D *effect;

    box.x = pos->y;
    box.y = pos->x;
    box.minA = -10;
    box.minB = -10;
    box.maxA = 10;
    box.maxB = 10;
    box.radius = 14;
    box.value10 = 0;
    if (tag != -1) {
        if (func_80107A14(&box, 16, results, &count)) {
            for (i = 0; i < count; i++) {
                if ((u32)results[i] < 3) {
                    return -1;
                }
                if (results[i]->value08 != 0) {
                    return -1;
                }
            }
        }
    }
    effect = allocate_effect(0, 0x1D, 0x28);
    if (effect == 0) {
        return -1;
    }
    effect->y = pos->y;
    effect->x = pos->x;
    effect->value1C = 0;
    effect->tag = tag;
    effect->spawnTime = D_801B4AA8;
    effect->motion = create_effect_motion(effect, effect->y, effect->x, -10, 10, -10, 10, 0x242, 0);
    return 0;
}
