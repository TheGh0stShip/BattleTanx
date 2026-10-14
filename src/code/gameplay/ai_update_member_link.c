#include "ai_action_helpers.h"

extern void update_member_link(void *link, s16 index) __asm__("func_800E3554");

s32 ai_update_member_link(AiActionContext *context) __asm__("func_800E6B14");

s32 ai_update_member_link(AiActionContext *context)
{
    update_member_link((u8 *)context->member + 0x18, context->linkIndex);
    return -1;
}
