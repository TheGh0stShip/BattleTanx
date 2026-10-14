#include "ai_action_helpers.h"

typedef struct AiMemberFlags {
    u8 pad000[0x2BA];
    u8 enabled;
} AiMemberFlags;

s32 ai_enable_member_flag_2ba(AiActionContext *context) __asm__("func_800E7380");
s32 ai_disable_member_flag_2ba(AiActionContext *context) __asm__("func_800E7394");

s32 ai_enable_member_flag_2ba(AiActionContext *context)
{
    ((AiMemberFlags *)context->member)->enabled = 1;
    return -1;
}

s32 ai_disable_member_flag_2ba(AiActionContext *context)
{
    ((AiMemberFlags *)context->member)->enabled = 0;
    return -1;
}
