#include "types.h"
#include "ai_play_stack.h"

typedef struct AiMemberScaled {
    u8 pad00[0x20];
    s32 value20;
    u8 pad24[0x35C - 0x24];
    u16 value35C;
} AiMemberScaled;

extern f32 D_800746FC;

s32 ai_step_scale_member_value(AiActionContext *context) __asm__("func_800E7560");
s32 ai_step_scale_member_value(AiActionContext *context) {
    f32 value = ((AiMemberScaled *)context->member)->value20;

    if (D_800746FC < value) {
        value = D_800746FC;
    }
    ((AiMemberScaled *)context->member)->value35C = (u32)(value * context->params[0]);
    return -1;
}
