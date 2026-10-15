#include "types.h"

void delay_empty_iterations(void *unused, s32 count) __asm__("func_80086B20");

void delay_empty_iterations(void *unused, s32 count)
{
    s32 i;

    for (i = 0; i < count; i++) {
    }
}
