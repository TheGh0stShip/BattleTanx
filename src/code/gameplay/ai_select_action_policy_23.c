#include "ai_action_policy.h"

extern AiActionPolicy D_80136774;

s32 ai_select_action_policy_23(AiActionContext *context) __asm__("func_800EB69C");

s32 ai_select_action_policy_23(AiActionContext *context)
{
    ai_prepare_metric_6c5c(context);
    return ai_select_weighted_action(context, &D_80136774);
}
