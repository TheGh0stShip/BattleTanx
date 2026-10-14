#include "types.h"

extern u8 gGraphicsMessageQueue[] __asm__("D_8014E0D0");

void *get_graphics_message_queue(void) __asm__("func_80078F60");

void *get_graphics_message_queue(void)
{
    return gGraphicsMessageQueue;
}
