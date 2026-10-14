#include "ai_action_helpers.h"

extern void ai_assign_member_play_slots(AiActionContext *context) __asm__("func_800E9E5C");

s32 ai_select_member_plays(AiActionContext *context) __asm__("func_800E6FD8");

s32 ai_select_member_plays(AiActionContext *context)
{
    ai_assign_member_play_slots(context);
    return -1;
}
