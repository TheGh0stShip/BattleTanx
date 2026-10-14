#include "ai_action_policy.h"

extern AiActionPolicy D_80136480;

s32 ai_select_action_policy_16(AiActionContext *context) __asm__("func_800EB394");

s32 ai_select_action_policy_16(AiActionContext *context)
{
    return ai_select_weighted_action(context, &D_80136480);
}
