#include "ai_action_internal.h"

s32 ai_action_set_target(AiActionContext *context) __asm__("func_800EC35C");

s32 ai_action_set_target(AiActionContext *context)
{
    ai_set_target_from_action(context);
    return -1;
}
