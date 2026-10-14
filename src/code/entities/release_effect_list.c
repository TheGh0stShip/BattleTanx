#include "types.h"

typedef struct EffectRecord {
    u8 pad00[0x2C];
    struct EffectRecord *next;
} EffectRecord;

typedef struct EffectListOwner {
    u8 pad00[0x98];
    EffectRecord *effects;
} EffectListOwner;

typedef struct EffectReleaseContext {
    u8 pad00[0xC];
    u8 ownerId;
} EffectReleaseContext;

extern void release_effect(EffectRecord *effect, u8 ownerId) __asm__("func_800A6E30");

void release_effect_list(EffectListOwner *owner, EffectReleaseContext *context) __asm__("func_800A72C8");

void release_effect_list(EffectListOwner *owner, EffectReleaseContext *context)
{
    EffectRecord *effect;
    EffectRecord *next;

    effect = owner->effects;
    while (effect != 0) {
        next = effect->next;
        release_effect(effect, context->ownerId);
        effect = next;
    }
    owner->effects = 0;
}
