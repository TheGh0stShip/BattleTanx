#include "types.h"

typedef struct EffectRecord EffectRecord;

extern EffectRecord *D_802DF350;

void clear_effect_list(void) __asm__("func_800A68E0");
EffectRecord *get_effect_list_head(void) __asm__("func_800A68F0");

void clear_effect_list(void)
{
    D_802DF350 = 0;
}

EffectRecord *get_effect_list_head(void)
{
    return D_802DF350;
}
