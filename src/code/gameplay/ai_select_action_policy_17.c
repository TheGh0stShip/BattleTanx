#include "ai_action_policy.h"

extern AiActionPolicy D_801364E8;

s32 ai_select_action_policy_17(AiActionContext *context) __asm__("func_800EB3F0");

s32 ai_select_action_policy_17(AiActionContext *context)
{
    return ai_select_weighted_action(context, &D_801364E8);
}
