#include "ai_action_helpers.h"

extern void select_member_plays(AiActionContext *context) __asm__("func_800E9E5C");

s32 ai_select_member_plays(AiActionContext *context) __asm__("func_800E6FD8");

s32 ai_select_member_plays(AiActionContext *context)
{
    select_member_plays(context);
    return -1;
}
