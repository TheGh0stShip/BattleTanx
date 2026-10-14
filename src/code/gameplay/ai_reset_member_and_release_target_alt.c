#include "ai_action_internal.h"

s32 ai_action_reset_member_and_release_target_alt(AiActionContext *context) __asm__("func_800EB668");

s32 ai_action_reset_member_and_release_target_alt(AiActionContext *context)
{
    ai_reset_controlled_member(context);
    ai_release_action_target(context);
    return -1;
}
