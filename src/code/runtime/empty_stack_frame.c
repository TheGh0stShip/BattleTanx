#include "types.h"

void empty_stack_frame(void) __asm__("func_800B87F4");

void empty_stack_frame(void)
{
    u8 scratch[16];
    (void)scratch;
}
