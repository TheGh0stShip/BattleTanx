#include "ai_action_policy.h"

extern AiActionPolicy D_80137210;

s32 ai_select_action_policy_33(AiActionContext *context) __asm__("func_800EBC44");

s32 ai_select_action_policy_33(AiActionContext *context)
{
    return ai_select_weighted_action(context, &D_80137210);
}
