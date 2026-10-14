#include "types.h"

typedef struct IndexCycleEffect {
    u8 pad00[0x1C];
    s32 lifetime;
    u8 pad20[0x10];
    u8 mode;
    u8 pad31[0x7];
    f32 drift;
    u8 currentIndex;
    u8 nextIndex;
    u8 value3E;
    u8 pad3F;
    u16 blend;
    u16 blendStep;
} IndexCycleEffect;

extern u16 D_80142B70[];

void tick_effect_index_cycle(IndexCycleEffect *effect, s32 *result) __asm__("func_8010BEFC");

void tick_effect_index_cycle(IndexCycleEffect *effect, s32 *result)
{
    s32 lifetime = effect->lifetime;

    if (lifetime != -1) {
        if (lifetime != 0) {
            effect->lifetime = lifetime - 1;
        } else {
            *result = 2;
            return;
        }
    }
    if (effect->mode == 1) {
        effect->value3E += (u32)effect->drift;
    }
    if (effect->mode != 3) {
        effect->blend += effect->blendStep;
        if (effect->blend >= 0x100) {
            effect->currentIndex = effect->nextIndex;
            effect->nextIndex = D_80142B70[effect->nextIndex];
            effect->blend = 0;
        }
    }
}
