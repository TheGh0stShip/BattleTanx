#include "ai_action_policy.h"

extern AiActionPolicy D_80135E64;

s32 ai_select_action_policy_03(AiActionContext *context) __asm__("func_800EAD4C");

s32 ai_select_action_policy_03(AiActionContext *context)
{
    return ai_select_weighted_action(context, &D_80135E64);
}
