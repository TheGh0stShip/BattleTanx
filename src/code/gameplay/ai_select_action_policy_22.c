#include "ai_action_policy.h"

extern AiActionPolicy D_801366DC;

s32 ai_select_action_policy_22(AiActionContext *context) __asm__("func_800EB640");

s32 ai_select_action_policy_22(AiActionContext *context)
{
    return ai_select_weighted_action(context, &D_801366DC);
}
