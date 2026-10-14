#include "ai_action_internal.h"

s32 ai_action_reset_member_link(AiActionContext *context) __asm__("func_800EBFF4");

s32 ai_action_reset_member_link(AiActionContext *context)
{
    ai_reset_member_link_state(context);
    return -1;
}
