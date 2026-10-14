#include "ai_action_internal.h"

s32 ai_action_invert_owner_behavior_flag(AiActionContext *context) __asm__("func_800EBCE4");

s32 ai_action_invert_owner_behavior_flag(AiActionContext *context)
{
    ai_invert_owner_behavior_flag(context);
    return -1;
}
