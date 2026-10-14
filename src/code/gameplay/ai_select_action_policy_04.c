#include "ai_action_policy.h"

extern AiActionPolicy D_80135F84;

s32 ai_select_action_policy_04(AiActionContext *context) __asm__("func_800EAD74");

s32 ai_select_action_policy_04(AiActionContext *context)
{
    return ai_select_weighted_action(context, &D_80135F84);
}
