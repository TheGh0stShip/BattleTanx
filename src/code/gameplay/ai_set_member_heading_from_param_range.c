#include "types.h"
#include "ai_play_stack.h"

typedef struct AiMemberHeading {
    u8 pad000[0x35E];
    u16 heading;
} AiMemberHeading;

extern f32 D_8007470C;
extern f32 D_80074710;

extern f32 ai_get_parameter(AiActionContext *context, s32 key) __asm__("func_800E9720");

s32 ai_set_member_heading_from_param_range(AiActionContext *context) __asm__("func_800E7628");

s32 ai_set_member_heading_from_param_range(AiActionContext *context)
{
    f32 low;
    f32 span;

    low = context->params[0];
    span = context->params[1] - low;
    ((AiMemberHeading *)context->member)->heading =
        (u32)((low + span * (D_8007470C - ai_get_parameter(context, 0x1000))) * D_80074710);
    return -1;
}
