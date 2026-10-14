#include "ai_action_internal.h"

s32 ai_action_copy_owner_behavior_flag_alt(AiActionContext *context) __asm__("func_800EBE24");

s32 ai_action_copy_owner_behavior_flag_alt(AiActionContext *context)
{
    ai_copy_owner_behavior_flag(context);
    return -1;
}
