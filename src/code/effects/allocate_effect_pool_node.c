#include "types.h"

typedef struct EffectPoolNode {
    s16 nextFree;
    u8 pad02[0x46];
} EffectPoolNode;

extern s16 D_802C13E0;
extern EffectPoolNode D_802C3A30[];

EffectPoolNode *allocate_effect_pool_node(void) __asm__("func_8008AFE4");

EffectPoolNode *allocate_effect_pool_node(void)
{
    s32 index;

    if (D_802C13E0 == -1) {
        return 0;
    }
    index = D_802C13E0;
    D_802C13E0 = D_802C3A30[index].nextFree;
    return &D_802C3A30[index];
}
