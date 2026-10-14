#include "types.h"

typedef struct EffectNode {
    s16 next;
    u8 pad02[2];
    s32 serial;
    s32 kind;
    u8 pad0C[0x3C];
} EffectNode;

extern s16 D_802C13E0;
extern s16 D_802C13E2;
extern s16 D_802C13F6;
extern EffectNode D_802C3A30[];
extern s32 D_80125C40;

EffectNode *allocate_effect(u8 group, s32 kind, s32 size) __asm__("func_8008AD10");

EffectNode *allocate_effect(u8 group, s32 kind, s32 size) {
    s32 index;

    if (D_802C13E0 == -1) {
        return 0;
    }
    index = D_802C13E0;
    D_802C13E0 = D_802C3A30[index].next;
    if (group == 1) {
        D_802C3A30[index].next = D_802C13E2;
        D_802C13E2 = index;
    } else {
        D_802C3A30[index].next = D_802C13F6;
        D_802C13F6 = index;
    }
    D_802C3A30[index].kind = kind;
    D_802C3A30[index].serial = D_80125C40++;
    return &D_802C3A30[index];
}
