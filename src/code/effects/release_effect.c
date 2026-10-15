#include "types.h"

typedef struct EffectNode {
    s16 next;
    u8 pad02[0x46];
} EffectNode;

extern s16 D_802C13E2;
extern s16 D_802C13F6;
extern s16 D_802C3A28;
extern EffectNode D_802C3A30[];

void release_effect(EffectNode *node) __asm__("func_8008B89C");

void release_effect(EffectNode *node)
{
    s16 index;
    s16 *link;
    s16 next;
    s32 current;

    index = node - D_802C3A30;
    for (link = &D_802C3A28; *link != index; link = &D_802C3A30[*link].next) {
        if (*link == -1) {
            goto search_inactive;
        }
    }
    current = *link;
    if (current != -1) {
        goto unlink;
    }
search_inactive:
    for (link = &D_802C13F6; *link != index; link = &D_802C3A30[*link].next) {
        if (*link == -1) {
            return;
        }
    }
    current = *link;
    if (current == -1) {
        return;
    }
unlink:
    next = D_802C3A30[current].next;
    D_802C3A30[current].next = D_802C13E2;
    D_802C13E2 = *link;
    *link = next;
}
