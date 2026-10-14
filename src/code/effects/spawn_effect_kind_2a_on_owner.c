#include "types.h"

typedef struct EffectVec3 {
    f32 x;
    f32 y;
    f32 z;
} EffectVec3;

typedef struct SpawnTemplate {
    u8 pad00[8];
    s16 value08;
} SpawnTemplate;

typedef struct AttachedEffect {
    u8 pad00[0xC];
    u8 templateIndex;
    s8 value0D;
    s8 value0E;
    u8 pad0F;
    s16 startTime;
    s16 lastTime;
    s16 value14;
    u8 pad16[2];
    s32 value18;
    EffectVec3 position;
    s16 randomSeed;
    u16 spin;
    s32 value2C;
    s32 value30;
    s32 value34;
    s32 value38;
    void *owner;
} AttachedEffect;

extern void transform_point_3x4(void *matrix, EffectVec3 *point, EffectVec3 *out) __asm__("func_800A7D10");
extern AttachedEffect *allocate_effect(s32 group, s32 kind, s32 size) __asm__("func_8008AD10");
extern u64 func_8007B268(void) __asm__("func_8007B268");
extern s16 func_800F38F4(void) __asm__("func_800F38F4");
extern SpawnTemplate *D_80137940[];
extern f32 D_80074BE0;
extern f32 D_80074BE4;

void spawn_effect_kind_2a_on_owner(u8 *owner) __asm__("func_800EED5C");

void spawn_effect_kind_2a_on_owner(u8 *owner) {
    EffectVec3 offset;
    EffectVec3 position;
    AttachedEffect *effect;
    u32 now;
    s16 seed;

    offset.x = 0.0f;
    offset.z = D_80074BE0;
    offset.y = D_80074BE4;
    transform_point_3x4(owner + 0x40C, &offset, &position);
    effect = allocate_effect(1, 0x2A, 0x40);
    if (effect != 0) {
        effect->templateIndex = 0x24;
        effect->owner = owner;
        effect->value2C = 0;
        effect->value30 = 0;
        effect->value34 = 0;
        effect->value38 = 0;
        effect->value0D = 0;
        effect->value0E = 1;
        effect->value18 = D_80137940[effect->templateIndex]->value08;
        now = (u32)func_8007B268() >> 16;
        effect->startTime = now;
        effect->lastTime = now;
        effect->value14 = 0;
        effect->position.x = position.x;
        effect->position.y = position.y;
        effect->position.z = position.z;
        seed = func_800F38F4();
        effect->randomSeed = seed;
        effect->spin = (seed & 1) ? -100 : 100;
    }
}
