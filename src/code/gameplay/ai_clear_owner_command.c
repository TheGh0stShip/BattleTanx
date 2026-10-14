#include "ai_action_internal.h"

s32 ai_action_clear_owner_command(AiActionContext *context) __asm__("func_800EB110");

s32 ai_action_clear_owner_command(AiActionContext *context)
{
    ai_clear_owner_command(context);
    return -1;
}
