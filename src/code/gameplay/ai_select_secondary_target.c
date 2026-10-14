#include "ai_action_internal.h"

s32 ai_action_select_secondary_target(AiActionContext *context) __asm__("func_800EAFC4");

s32 ai_action_select_secondary_target(AiActionContext *context)
{
    ai_select_secondary_target(context);
    return -1;
}
