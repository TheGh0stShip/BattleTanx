#include "ai_action_policy.h"

extern AiActionPolicy D_80136D78;

s32 ai_select_action_policy_28(AiActionContext *context) __asm__("func_800EB9D8");

s32 ai_select_action_policy_28(AiActionContext *context)
{
    return ai_select_weighted_action(context, &D_80136D78);
}
