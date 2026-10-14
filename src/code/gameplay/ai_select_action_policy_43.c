#include "ai_action_policy.h"

extern AiActionPolicy D_8013755C;

s32 ai_select_action_policy_43(AiActionContext *context) __asm__("func_800EBF28");

s32 ai_select_action_policy_43(AiActionContext *context)
{
    return ai_select_weighted_action(context, &D_8013755C);
}
