#include "ai_action_policy.h"

extern AiActionPolicy D_80137648;

s32 ai_select_action_policy_46(AiActionContext *context) __asm__("func_800EC014");

s32 ai_select_action_policy_46(AiActionContext *context)
{
    return ai_select_weighted_action(context, &D_80137648);
}
