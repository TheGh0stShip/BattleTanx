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
extern s16 D_802C13F4;
extern s16 D_802C13F6;
extern s16 D_802C3A28;
extern EffectNode D_802C3A30[];
extern s32 D_80125C40;

static inline EffectNode *take_free_effect(u8 group, s32 kind) {
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

EffectNode *allocate_or_recycle_effect(u8 group, s32 kind, s32 size) __asm__("func_8008AE18");

EffectNode *allocate_or_recycle_effect(u8 group, s32 kind, s32 size) {
    EffectNode *node;
    s32 index;
    s32 busy;

    node = take_free_effect(group, kind);
    if (node != 0) {
        return node;
    }
    if (group) {
        index = D_802C13F4;
    } else {
        index = D_802C3A28;
    }
    if (index == -1) {
        return 0;
    }
    do {
        switch (D_802C3A30[index].kind) {
        case 2:
        case 4:
        case 12:
        case 13:
        case 17:
        case 24:
        case 27:
        case 29:
        case 30:
        case 34:
            busy = 0;
            break;
        default:
            busy = 1;
            break;
        }
        if (!busy) {
            break;
        }
        index = D_802C3A30[index].next;
    } while (index != -1);
    if (index == -1) {
        return 0;
    }
    D_802C3A30[index].kind = kind;
    D_802C3A30[index].serial = D_80125C40++;
    return &D_802C3A30[index];
}
