#include "types.h"

#ifndef NULL
#define NULL 0
#endif

s32 func_80107170(s32);

void finish_effect_when_expired(void *arg0, s32 *arg1) __asm__("func_800F2010");

void finish_effect_when_expired(void *arg0, s32 *arg1) {
    if ((*(s32 *)((s8 *)(arg0) + (0x18))) <= 0) {
        *arg1 = 2;
        func_80107170((*(s32 *)((s8 *)(arg0) + (0x1C))));
    }
}
