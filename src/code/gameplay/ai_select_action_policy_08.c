#include "ai_action_policy.h"

extern AiActionPolicy D_801361CC;

s32 ai_select_action_policy_08(AiActionContext *context) __asm__("func_800EB0E8");

s32 ai_select_action_policy_08(AiActionContext *context)
{
    return ai_select_weighted_action(context, &D_801361CC);
}
