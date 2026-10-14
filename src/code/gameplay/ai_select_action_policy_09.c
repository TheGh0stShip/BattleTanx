#include "ai_action_policy.h"

extern AiActionPolicy D_8013624C;

s32 ai_select_action_policy_09(AiActionContext *context) __asm__("func_800EB130");

s32 ai_select_action_policy_09(AiActionContext *context)
{
    return ai_select_weighted_action(context, &D_8013624C);
}
