#include "types.h"
#include "ai_play_stack.h"

typedef struct AiMemberStatus {
    u8 pad000[0x35E];
    u16 value35E;
} AiMemberStatus;

s32 ai_store_member_param_u16(AiActionContext *context) __asm__("func_800E76D0");

s32 ai_store_member_param_u16(AiActionContext *context)
{
    ((AiMemberStatus *)context->member)->value35E = (u32)context->params[0];
    return -1;
}
