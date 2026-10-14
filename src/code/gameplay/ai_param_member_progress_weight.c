#include "ai_play_stack.h"

typedef struct ProgressOwner {
    u8 pad000[0x1A5];
    u8 reversed;
} ProgressOwner;

typedef struct ProgressMember {
    u8 pad000[0x4E0];
    f32 length;
    f32 travelled;
} ProgressMember;

extern f32 D_80074814;
extern f32 D_80074818;

f32 ai_param_member_progress_weight(AiActionContext *context) __asm__("func_800E8DAC");

#define MEMBER_PROGRESS(context) \
    (((ProgressMember *)(context)->member)->travelled / ((ProgressMember *)(context)->member)->length)

f32 ai_param_member_progress_weight(AiActionContext *context)
{
    f32 progress;

    if (((ProgressOwner *)context->owner)->reversed) {
        progress = D_80074814 - MEMBER_PROGRESS(context);
    } else {
        progress = MEMBER_PROGRESS(context);
    }
    return D_80074818 - progress;
}
