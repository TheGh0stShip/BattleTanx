#include "ai_action_policy.h"

extern AiActionPolicy D_801362A8;

s32 ai_select_action_policy_11(AiActionContext *context) __asm__("func_800EB1C0");

s32 ai_select_action_policy_11(AiActionContext *context)
{
    return ai_select_weighted_action(context, &D_801362A8);
}
