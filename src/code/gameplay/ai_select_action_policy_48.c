#include "ai_action_policy.h"

extern AiActionPolicy D_80137708;

s32 ai_select_action_policy_48(AiActionContext *context) __asm__("func_800EC0D4");

s32 ai_select_action_policy_48(AiActionContext *context)
{
    ai_push_param(context, 8.0f);
    ai_prepare_metric_6c14(context);
    ai_finalize_action_metrics(context);
    ai_prepare_metric_6fd8(context);
    return ai_select_weighted_action(context, &D_80137708);
}
