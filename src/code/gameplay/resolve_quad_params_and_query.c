#include "types.h"

extern s32 func_80094C58(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 key,
                         s32 *out0, s32 *out1, s32 *out2, s32 *out3) __asm__("func_80094C58");
extern s32 func_80095CDC(s32 value0, s32 value1, s32 value2, s32 value3, s32 arg4, s32 key) __asm__("func_80095CDC");

s32 resolve_quad_params_and_query(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 key) __asm__("func_80095EAC");

s32 resolve_quad_params_and_query(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 key)
{
    s32 value0;
    s32 value1;
    s32 value2;
    s32 value3;

    if (func_80094C58(arg0, arg1, arg2, arg3, key, &value0, &value1, &value2, &value3) != 0) {
        return func_80095CDC(value0, value1, value2, value3, arg4, key);
    }
    return 0;
}
