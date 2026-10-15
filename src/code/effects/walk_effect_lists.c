#include "types.h"

typedef struct EffectListNode {
    s16 next;
    u8 pad02[0x46];
} EffectListNode;

extern s16 D_802C13E0;
extern s16 D_802C13E2;
extern s16 D_802C13F4;
extern s16 D_802C13F6;
extern s16 D_802C3A28;
extern EffectListNode D_802C3A30[];

void walk_effect_lists(void) __asm__("func_8008B080");

void walk_effect_lists(void)
{
    s16 index;

    index = D_802C13E0;
    while (index != -1) {
        index = D_802C3A30[index].next;
    }
    index = D_802C13F4;
    while (index != -1) {
        index = D_802C3A30[index].next;
    }
    index = D_802C13E2;
    while (index != -1) {
        index = D_802C3A30[index].next;
    }
    index = D_802C3A28;
    while (index != -1) {
        index = D_802C3A30[index].next;
    }
    index = D_802C13F6;
    while (index != -1) {
        index = D_802C3A30[index].next;
    }
}
