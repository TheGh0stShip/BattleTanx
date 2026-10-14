#include "types.h"

s32 render_callback_reject(void) __asm__("func_80106D00");
void render_callback_noop(void) __asm__("func_80106D08");
s32 render_callback_accept(void) __asm__("func_80106D10");

s32 render_callback_reject(void)
{
    return -1;
}

void render_callback_noop(void)
{
}

s32 render_callback_accept(void)
{
    return 0;
}
