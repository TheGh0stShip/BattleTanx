#include "ai_action_policy.h"

extern AiActionPolicy D_80137248;

s32 ai_select_action_policy_34(AiActionContext *context) __asm__("func_800EBC6C");

s32 ai_select_action_policy_34(AiActionContext *context)
{
    return ai_select_weighted_action(context, &D_80137248);
}
