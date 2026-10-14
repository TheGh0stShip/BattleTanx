#include "types.h"

s32 set_result_two(void *unused, s32 *result) __asm__("func_80091D04");

s32 set_result_two(void *unused, s32 *result)
{
    *result = 2;
    return 2;
}
