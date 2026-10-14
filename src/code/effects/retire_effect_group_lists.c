#include "types.h"

typedef struct EffectNode {
    s16 next;
    u8 pad02[0x46];
} EffectNode;

extern EffectNode D_802C3A30[];
extern s16 D_802C13E2;
extern s16 D_802C13F4;
extern s16 D_802C13F6;
extern s16 D_802C3A28;

void retire_effect_group_lists(void) __asm__("func_8008B1F0");

void retire_effect_group_lists(void) {
    s16 index;
    s32 next;

    for (index = D_802C13E2; index != -1; index = next) {
        next = D_802C3A30[index].next;
        D_802C3A30[index].next = D_802C13F4;
        D_802C13F4 = index;
        D_802C13E2 = next;
    }
    for (index = D_802C13F6; index != -1; index = next) {
        next = D_802C3A30[index].next;
        D_802C3A30[index].next = D_802C3A28;
        D_802C3A28 = index;
        D_802C13F6 = next;
    }
}
