#include "ai_action_helpers.h"

extern void clear_member_transient_state(void *memberState) __asm__("func_800E3480");

s32 ai_clear_member_transient_state(AiActionContext *context) __asm__("func_800E6BF0");

s32 ai_clear_member_transient_state(AiActionContext *context)
{
    clear_member_transient_state((u8 *)context->member + 0x18);
    return -1;
}
