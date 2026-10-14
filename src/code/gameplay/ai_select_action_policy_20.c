#include "ai_action_policy.h"

extern AiActionPolicy D_80136658;

s32 ai_select_action_policy_20(AiActionContext *context) __asm__("func_800EB554");

s32 ai_select_action_policy_20(AiActionContext *context)
{
    ai_push_param(context, 100.0f);
    ai_prepare_metric_76d0(context);
    ai_finalize_action_metrics(context);
    return ai_select_weighted_action(context, &D_80136658);
}
