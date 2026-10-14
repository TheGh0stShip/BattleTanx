#include "ai_action_policy.h"

extern AiActionPolicy D_80136B00;

s32 ai_select_action_policy_26(AiActionContext *context) __asm__("func_800EB8F8");

s32 ai_select_action_policy_26(AiActionContext *context)
{
    return ai_select_weighted_action(context, &D_80136B00);
}
