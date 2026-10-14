#include "types.h"

typedef struct ResourceEffect {
    u8 pad00[0x20];
    s32 resource;
} ResourceEffect;

extern void func_80107170(s32 resource);

void release_effect_resource(ResourceEffect *effect, s32 *state) __asm__("func_800A04F0");

void release_effect_resource(ResourceEffect *effect, s32 *state)
{
    if (effect->resource != 0) {
        func_80107170(effect->resource);
    }
    *state = 2;
}
