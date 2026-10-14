#include "ai_action_policy.h"

extern AiActionPolicy D_80137038;

s32 ai_select_action_policy_30(AiActionContext *context) __asm__("func_800EBAB8");

s32 ai_select_action_policy_30(AiActionContext *context)
{
    return ai_select_weighted_action(context, &D_80137038);
}
