#include "types.h"

typedef struct ListedEffect {
    u8 pad00[0x20];
    s32 owner;
    u8 pad24[0x4];
    struct ListedEffect *next;
} ListedEffect;

extern void release_effect(ListedEffect *effect) __asm__("func_8008B89C");
extern ListedEffect *gEffectListHead __asm__("D_80125D40");
extern ListedEffect *gEffectListTail __asm__("D_80125D44");
extern s16 gEffectListCount __asm__("D_80125D48");

void remove_effects_by_owner(s32 owner) __asm__("func_80093F3C");

void remove_effects_by_owner(s32 owner)
{
    ListedEffect *prev;
    ListedEffect *next;

    if (gEffectListCount == 0) {
        return;
    }
    while (gEffectListHead != 0 && gEffectListHead->owner == owner) {
        release_effect(gEffectListHead);
        gEffectListCount--;
        gEffectListHead = gEffectListHead->next;
    }
    if (gEffectListCount == 0) {
        gEffectListTail = 0;
        return;
    }
    prev = gEffectListHead;
    while (prev->next != 0) {
        next = prev->next;
        if (next->owner == owner) {
            release_effect(next);
            if (gEffectListTail == prev->next) {
                gEffectListTail = prev;
            }
            gEffectListCount--;
            prev->next = prev->next->next;
        } else {
            prev = next;
        }
    }
}
