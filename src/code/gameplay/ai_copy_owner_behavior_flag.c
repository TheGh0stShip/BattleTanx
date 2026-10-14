#include "ai_action_internal.h"

s32 ai_action_copy_owner_behavior_flag(AiActionContext *context) __asm__("func_800EBD2C");

s32 ai_action_copy_owner_behavior_flag(AiActionContext *context)
{
    ai_copy_owner_behavior_flag(context);
    return -1;
}
