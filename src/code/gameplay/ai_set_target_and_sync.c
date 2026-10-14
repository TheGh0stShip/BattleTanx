#include "ai_action_internal.h"

s32 ai_action_set_target_and_sync(AiActionContext *context) __asm__("func_800EB360");

s32 ai_action_set_target_and_sync(AiActionContext *context)
{
    ai_set_target_from_action(context);
    ai_sync_owner_action(context);
    return -1;
}
