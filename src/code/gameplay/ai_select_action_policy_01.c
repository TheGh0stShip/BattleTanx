#include "ai_action_policy.h"

extern AiActionPolicy D_80135DB4;

s32 ai_select_action_policy_01(AiActionContext *context) __asm__("func_800EAC48");

s32 ai_select_action_policy_01(AiActionContext *context)
{
    ai_select_owner_target_member(context);
    return ai_select_weighted_action(context, &D_80135DB4);
}
