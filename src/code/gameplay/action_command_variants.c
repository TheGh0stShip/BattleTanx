#include "types.h"

extern void configure_action_command(void *command, s32 action, s32 mode)
    __asm__("func_800EF16C");

s32 configure_action_35_mode_2(void *context) __asm__("func_800EF11C");
s32 configure_action_32_mode_0(void *context) __asm__("func_800EF144");

s32 configure_action_35_mode_2(void *context)
{
    configure_action_command((u8 *)context + 0x18, 0x23, 2);
    return 1;
}

s32 configure_action_32_mode_0(void *context)
{
    configure_action_command((u8 *)context + 0x18, 0x20, 0);
    return 1;
}
