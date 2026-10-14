#include "ai_action_policy.h"

extern AiActionPolicy D_80136ED8;

s32 ai_select_action_policy_29(AiActionContext *context) __asm__("func_800EBA48");

s32 ai_select_action_policy_29(AiActionContext *context)
{
    return ai_select_weighted_action(context, &D_80136ED8);
}
