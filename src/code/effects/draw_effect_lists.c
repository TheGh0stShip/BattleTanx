#include "types.h"

typedef struct EffectNode {
    s16 next;
    u8 pad02[2];
    s32 serial;
    s32 kind;
    u8 pad0C[0x3C];
} EffectNode;

typedef struct EffectKind {
    u8 pad00[0x8];
    void (*draw)(EffectNode *effect);
} EffectKind;

extern s16 D_802C13E2;
extern s16 D_802C13F4;
extern s16 D_802C13F6;
extern s16 D_802C3A28;
extern EffectKind D_802C3800[];
extern EffectNode D_802C3A30[];

void draw_effect_lists(void) __asm__("func_8008B48C");

#define DRAW_EFFECT_LIST(head)                                  \
    for (index = (head); index != -1; index = D_802C3A30[index].next) { \
        effect = &D_802C3A30[index];                            \
        if (D_802C3800[effect->kind].draw) {                    \
            D_802C3800[effect->kind].draw(effect);              \
        }                                                       \
    }

void draw_effect_lists(void)
{
    s32 index;
    EffectNode *effect;

    DRAW_EFFECT_LIST(D_802C13F4);
    DRAW_EFFECT_LIST(D_802C3A28);
    DRAW_EFFECT_LIST(D_802C13E2);
    DRAW_EFFECT_LIST(D_802C13F6);
}
