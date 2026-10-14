#include "types.h"

#ifndef NULL
#define NULL 0
#endif

void *func_800A6688(s32);
extern s32 D_801B4AAC;
extern void *D_801B4ABC;

s32 get_match_time_bonus(s32 *arg0) __asm__("func_8007D384");

s32 get_match_time_bonus(s32 *arg0) {
    s32 temp_a0;
    void *temp_v0;

    temp_v0 = func_800A6688(0);
    temp_a0 = (*(s32 *)((s8 *)(D_801B4ABC) + (0x218))) * 0x1E;
    *arg0 = temp_a0;
    if ((*(s32 *)((s8 *)(temp_v0) + (0x10))) != 0) {
        if (D_801B4AAC < temp_a0) {
            return (((temp_a0 - D_801B4AAC) / 30) * 0x64) + 0xFA0;
        }
        return 0;
    }
    return 0;
}
