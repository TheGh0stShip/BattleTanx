#include "types.h"

#ifndef NULL
#define NULL 0
#endif

extern s32 D_80137900;
extern s32 D_8033B5F0;
extern s32 D_8033B620;
extern s32 D_8033B624;

u8 demo_get_recorded_input(s32 arg0) __asm__("func_800EC738");

u8 demo_get_recorded_input(s32 arg0) {
    void *temp_a1;

    if ((D_80137900 != 0) && (D_8033B624 >= 0)) {
        temp_a1 = D_8033B620 + (D_8033B624 * 0xC);
        if (((*(s16 *)((s8 *)(temp_a1) + (0))) == D_8033B5F0) && (((*(u8 *)((s8 *)(temp_a1) + (2))) & 0x7F) == arg0)) {
            return (*(u8 *)((s8 *)(temp_a1) + (3)));
        }
        return 0U;
    }
    return 0U;
}
