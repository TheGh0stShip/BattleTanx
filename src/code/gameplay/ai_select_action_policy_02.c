#include "ai_action_policy.h"

extern AiActionPolicy D_80135DDC;

s32 ai_select_action_policy_02(AiActionContext *context) __asm__("func_800EACB4");

s32 ai_select_action_policy_02(AiActionContext *context)
{
    ai_prepare_metric_6d58(context);
    return ai_select_weighted_action(context, &D_80135DDC);
}
