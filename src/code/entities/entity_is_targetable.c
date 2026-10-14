#include "types.h"

#ifndef NULL
#define NULL 0
#endif

extern s32 D_801B4AA8;

s32 entity_is_targetable(void *arg0) __asm__("func_8009FB8C");

s32 entity_is_targetable(void *arg0) {
    s32 var_v0;

    var_v0 = 0;
    if ((*(s32 *)((s8 *)(arg0) + (0x10))) == 0) {
        var_v0 = 1;
        if ((*(s32 *)((s8 *)(arg0) + (0x98))) == 0) {
            var_v0 = 0;
            if ((D_801B4AA8 - 0x5A) >= (*(s32 *)((s8 *)(arg0) + (0x4B0)))) {
                if ((*(s32 *)((s8 *)(arg0) + (0xC))) != 0) {
                    return (D_801B4AA8 - 0x2D) < (*(s32 *)((s8 *)(arg0) + (0x4B4)));
                }
                var_v0 = 1;
                return var_v0;
            }
            return var_v0;
        }
        return var_v0;
    }
    return var_v0;
}
