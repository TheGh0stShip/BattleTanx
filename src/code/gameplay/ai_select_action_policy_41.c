#include "ai_action_policy.h"

extern AiActionPolicy D_801374A4;

s32 ai_select_action_policy_41(AiActionContext *context) __asm__("func_800EBE44");

s32 ai_select_action_policy_41(AiActionContext *context)
{
    return ai_select_weighted_action(context, &D_801374A4);
}
