#include "types.h"

typedef struct EffectNode {
    s16 next;
    u8 pad02[2];
    s32 serial;
    s32 kind;
    u8 pad0C[0x3C];
} EffectNode;

typedef struct EffectKind {
    u8 pad00[0x4];
    void (*handle)(EffectNode *effect, void *sender, s32 message, s32 arg3, s32 arg4);
    void (*draw)(EffectNode *effect);
} EffectKind;

extern s16 D_802C13E2;
extern s16 D_802C13F4;
extern s16 D_802C13F6;
extern s16 D_802C3A28;
extern EffectKind D_802C3800[];
extern EffectNode D_802C3A30[];

void broadcast_effect_message_4(void) __asm__("func_8008B66C");

#define SEND_EFFECT_LIST(head)                                              \
    for (index = (head); index != -1; index = D_802C3A30[index].next) {     \
        effect = &D_802C3A30[index];                                        \
        if (D_802C3800[effect->kind].handle) {                              \
            D_802C3800[effect->kind].handle(effect, 0, 4, 0, 0);            \
        }                                                                   \
    }

void broadcast_effect_message_4(void)
{
    s32 index;
    EffectNode *effect;

    SEND_EFFECT_LIST(D_802C13F4);
    SEND_EFFECT_LIST(D_802C3A28);
    SEND_EFFECT_LIST(D_802C13E2);
    SEND_EFFECT_LIST(D_802C13F6);
}
