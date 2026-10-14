#include "types.h"

#ifndef NULL
#define NULL 0
#endif

s32 func_8008B89C();
s32 func_80093F3C(void *);

void advance_effect_frame(void *arg0) __asm__("func_80093410");

void advance_effect_frame(void *arg0) {
    if ((s32) (*(u8 *)((s8 *)(arg0) + (0xE))) < ((*(u8 *)((s8 *)(arg0) + (0xD))) - 1)) {
        func_8008B89C();
        func_80093F3C(arg0);
    }
}
