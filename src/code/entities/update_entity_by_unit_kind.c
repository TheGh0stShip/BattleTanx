#include "types.h"

#ifndef NULL
#define NULL 0
#endif

void *func_800A03B8(s16);
s32 func_800A4610(void *);
s32 func_800A47AC(void *);

s32 update_entity_by_unit_kind(void *arg0) __asm__("func_800A4A00");

s32 update_entity_by_unit_kind(void *arg0) {
    s16 temp_a0;
    s32 var_v0;

    temp_a0 = (*(s16 *)((s8 *)(arg0) + (0x20)));
    var_v0 = -1;
    if (temp_a0 != 0xFF) {
        if ((*(s32 *)((s8 *)(func_800A03B8(temp_a0)) + (0x18))) != 2) {
            return func_800A4610(arg0);
        }
        var_v0 = func_800A47AC(arg0);
        return var_v0;
    }
    return var_v0;
}
