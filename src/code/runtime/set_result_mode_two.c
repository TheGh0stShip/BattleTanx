#include "types.h"

void set_result_mode_two(void *arg0, s32 *result) __asm__("func_800ECC10");

void set_result_mode_two(void *arg0, s32 *result)
{
    *result = 2;
}
