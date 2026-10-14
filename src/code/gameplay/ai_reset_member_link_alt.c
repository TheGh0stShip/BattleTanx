#include "ai_action_internal.h"

s32 ai_action_reset_member_link_alt(AiActionContext *context) __asm__("func_800EB158");

s32 ai_action_reset_member_link_alt(AiActionContext *context)
{
    ai_reset_member_link_state(context);
    return -1;
}
