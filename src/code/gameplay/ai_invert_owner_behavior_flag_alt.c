#include "ai_action_internal.h"

s32 ai_action_invert_owner_behavior_flag_alt(AiActionContext *context) __asm__("func_800EBDDC");

s32 ai_action_invert_owner_behavior_flag_alt(AiActionContext *context)
{
    ai_invert_owner_behavior_flag(context);
    return -1;
}
