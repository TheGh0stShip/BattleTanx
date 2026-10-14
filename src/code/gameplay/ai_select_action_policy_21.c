#include "ai_action_policy.h"

extern AiActionPolicy D_801366A8;

s32 ai_select_action_policy_21(AiActionContext *context) __asm__("func_800EB5C0");

s32 ai_select_action_policy_21(AiActionContext *context)
{
    return ai_select_weighted_action(context, &D_801366A8);
}
