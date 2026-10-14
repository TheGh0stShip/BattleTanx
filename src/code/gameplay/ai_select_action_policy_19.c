#include "ai_action_policy.h"

extern AiActionPolicy D_80136560;

s32 ai_select_action_policy_19(AiActionContext *context) __asm__("func_800EB47C");

s32 ai_select_action_policy_19(AiActionContext *context)
{
    return ai_select_weighted_action(context, &D_80136560);
}
