#include "types.h"

typedef struct EffectNode {
    s16 next;
    u8 pad02[2];
    s32 serial;
    s32 kind;
    u8 pad0C[0x3C];
} EffectNode;

typedef struct EffectKind {
    void (*update)(EffectNode *effect, s32 *result);
    u8 pad04[0x8];
} EffectKind;

extern s16 D_802C13E0;
extern s16 D_802C13F4;
extern s16 D_802C3A28;
extern u8 D_80125C44[][0x2E];
extern EffectKind D_802C3800[];
extern EffectNode D_802C3A30[];
extern void retire_effect_group_lists(void) __asm__("func_8008B1F0");

void update_active_effect_list(s32 group) __asm__("func_8008B2C8");

void update_active_effect_list(s32 group)
{
    s16 *link;
    EffectNode *effect;
    s32 result;
    s16 index;

    retire_effect_group_lists();
    link = &D_802C13F4;
    while (*link != -1) {
        result = 0;
        if (D_80125C44[group][D_802C3A30[*link].kind] != 0) {
            effect = &D_802C3A30[*link];
            D_802C3800[effect->kind].update(effect, &result);
            switch ((u32)result) {
            case 2:
                D_802C3A30[*link].serial = 0;
                index = *link;
                *link = D_802C3A30[index].next;
                D_802C3A30[index].next = D_802C13E0;
                D_802C13E0 = index;
                break;
            case 1:
                index = *link;
                *link = D_802C3A30[index].next;
                D_802C3A30[index].next = D_802C3A28;
                D_802C3A28 = index;
                break;
            case 0:
                link = &D_802C3A30[*link].next;
                break;
            }
        } else {
            link = &D_802C3A30[*link].next;
        }
    }
    retire_effect_group_lists();
}
