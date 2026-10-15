#include "types.h"

typedef struct EffectPoolNode {
    s16 nextFree;
    u8 pad02[0x46];
} EffectPoolNode;

extern s16 D_802C13E0;
extern EffectPoolNode D_802C3A30[];

void release_effect_pool_node(EffectPoolNode *node) __asm__("func_8008B030");

void release_effect_pool_node(EffectPoolNode *node)
{
    s16 oldHead;

    oldHead = D_802C13E0;
    D_802C13E0 = node - D_802C3A30;
    node->nextFree = oldHead;
}
