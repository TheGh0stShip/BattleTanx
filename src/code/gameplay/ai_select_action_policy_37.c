#include "ai_action_policy.h"

extern AiActionPolicy D_80137354;

s32 ai_select_action_policy_37(AiActionContext *context) __asm__("func_800EBD04");

s32 ai_select_action_policy_37(AiActionContext *context)
{
    return ai_select_weighted_action(context, &D_80137354);
}
