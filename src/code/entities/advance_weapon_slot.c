#include "types.h"

#ifndef NULL
#define NULL 0
#endif

void advance_weapon_slot(void *arg0) __asm__("func_80098780");

void advance_weapon_slot(void *arg0) {
    s32 temp_v0;

    if (!((*(u16 *)((s8 *)(arg0) + (0x14))) & 0x2000) && ((*(s32 *)((s8 *)(arg0) + (0x474))) != 0)) {
        do {
            temp_v0 = (*(s32 *)((s8 *)(arg0) + (0x474))) + 1;
            (*(s32 *)((s8 *)(arg0) + (0x474))) = temp_v0;
            if (temp_v0 == 0x11) {
                (*(s32 *)((s8 *)(arg0) + (0x474))) = 4;
            }
        } while ((*(s16 *)((s8 *)((((*(s32 *)((s8 *)(arg0) + (0x474))) * 2) + arg0)) + (0x480))) == 0);
    }
}
