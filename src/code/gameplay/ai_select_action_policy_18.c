#include "ai_action_policy.h"

extern AiActionPolicy D_8013652C;

s32 ai_select_action_policy_18(AiActionContext *context) __asm__("func_800EB418");

s32 ai_select_action_policy_18(AiActionContext *context)
{
    return ai_select_weighted_action(context, &D_8013652C);
}
