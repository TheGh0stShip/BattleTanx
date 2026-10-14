#include "ai_action_policy.h"

extern AiActionPolicy D_8013741C;

s32 ai_select_action_policy_39(AiActionContext *context) __asm__("func_800EBDB4");

s32 ai_select_action_policy_39(AiActionContext *context)
{
    return ai_select_weighted_action(context, &D_8013741C);
}
