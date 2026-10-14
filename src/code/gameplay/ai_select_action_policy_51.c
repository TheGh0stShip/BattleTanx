#include "ai_action_policy.h"

extern AiActionPolicy D_801377D0;

s32 ai_select_action_policy_51(AiActionContext *context) __asm__("func_800EC218");

s32 ai_select_action_policy_51(AiActionContext *context)
{
    ai_push_param(context, 8.0f);
    ai_prepare_metric_6c14(context);
    ai_finalize_action_metrics(context);
    ai_prepare_metric_6fd8(context);
    return ai_select_weighted_action(context, &D_801377D0);
}
