#include "ai_action_policy.h"

extern AiActionPolicy D_80135D80;

s32 ai_select_action_policy_00(AiActionContext *context) __asm__("func_800EABB0");

s32 ai_select_action_policy_00(AiActionContext *context)
{
    ai_push_param(context, 0.0f);
    ai_prepare_metric_75d4(context);
    ai_finalize_action_metrics(context);
    return ai_select_weighted_action(context, &D_80135D80);
}
