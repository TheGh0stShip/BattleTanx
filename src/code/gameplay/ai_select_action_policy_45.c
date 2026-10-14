#include "ai_action_policy.h"

extern AiActionPolicy D_80137614;

s32 ai_select_action_policy_45(AiActionContext *context) __asm__("func_800EBFCC");

s32 ai_select_action_policy_45(AiActionContext *context)
{
    return ai_select_weighted_action(context, &D_80137614);
}
