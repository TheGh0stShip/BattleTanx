#include "types.h"
#include "ai_play_stack.h"

typedef struct AiRatioOwner {
    u8 pad000[0x1A5];
    u8 value1A5;
} AiRatioOwner;

typedef struct AiRatioMember {
    u8 pad000[0x4E0];
    f32 value4E0;
    f32 value4E4;
} AiRatioMember;

extern f32 D_80074810;

f32 ai_parameter_member_progress_ratio(AiActionContext *context) __asm__("func_800E8D64");

f32 ai_parameter_member_progress_ratio(AiActionContext *context)
{
    if (((AiRatioOwner *)context->owner)->value1A5 != 0) {
        return D_80074810 - ((AiRatioMember *)context->member)->value4E4 / ((AiRatioMember *)context->member)->value4E0;
    }
    return ((AiRatioMember *)context->member)->value4E4 / ((AiRatioMember *)context->member)->value4E0;
}
