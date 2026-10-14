#include "types.h"
#include "ai_play_stack.h"

typedef struct AiMemberHeading {
    u8 pad000[0x35E];
    u16 heading;
} AiMemberHeading;

extern f32 D_80074704;

s32 ai_set_member_heading_from_param(AiActionContext *context) __asm__("func_800E75D4");

s32 ai_set_member_heading_from_param(AiActionContext *context)
{
    ((AiMemberHeading *)context->member)->heading = (u32)(context->params[0] * D_80074704);
    return -1;
}
