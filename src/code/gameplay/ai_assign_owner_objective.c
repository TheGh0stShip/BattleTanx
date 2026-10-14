#include "ai_action_internal.h"

s32 ai_action_assign_owner_objective(AiActionContext *context) __asm__("func_800EB5A0");

s32 ai_action_assign_owner_objective(AiActionContext *context)
{
    ai_assign_owner_objective(context);
    return -1;
}
