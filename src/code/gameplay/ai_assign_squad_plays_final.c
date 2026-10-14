#include "ai_action_internal.h"

s32 ai_action_assign_squad_plays_final(void) __asm__("func_800EBBFC");

s32 ai_action_assign_squad_plays_final(void)
{
    ai_assign_squad_plays();
    return -1;
}
