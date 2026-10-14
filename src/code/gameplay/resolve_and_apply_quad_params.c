#include "types.h"

extern s32 func_80094C58(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 key,
                         s32 *out0, s32 *out1, s32 *out2, s32 *out3);
extern void func_800949D8(s32 value0, s32 value1, s32 value2, s32 value3, s32 arg4, s32 arg5, s32 key);

void resolve_and_apply_quad_params(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 key)
    __asm__("func_8009531C");

void resolve_and_apply_quad_params(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 key)
{
    s32 value0;
    s32 value1;
    s32 value2;
    s32 value3;

    if (func_80094C58(arg0, arg1, arg2, arg3, key, &value0, &value1, &value2, &value3) != 0) {
        func_800949D8(value0, value1, value2, value3, arg4, arg5, key);
    }
}
