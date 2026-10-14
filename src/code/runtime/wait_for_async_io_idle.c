#include "types.h"

extern volatile s32 D_802E17D0;

void wait_for_async_io_idle(void) __asm__("func_800A8EE0");

void wait_for_async_io_idle(void)
{
    while (D_802E17D0 != 0) {
    }
}
