#include "types.h"

#ifndef NULL
#define NULL 0
#endif

s32 func_800DE0C0(s32, s32);
s32 func_800E3480(s32);

s32 ai_reset_controlled_member(void *arg0) __asm__("func_800E6AAC");

s32 ai_reset_controlled_member(void *arg0) {
    func_800E3480((*(s32 *)((s8 *)(arg0) + (0xC))));
    if (((*(s32 *)((s8 *)(arg0) + (0x40))) == 1) && ((*(f32 *)((s8 *)(arg0) + (0x20))) > 0.0f)) {
        func_800DE0C0((*(s32 *)((s8 *)(arg0) + (0xC))) + 0x98, 0);
    }
    return -1;
}
