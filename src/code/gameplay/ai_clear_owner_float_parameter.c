#include "ai_action_helpers.h"

extern void ai_set_indexed_float(void *base, u32 key, f32 value) __asm__("func_800E986C");

s32 ai_clear_owner_float_parameter(AiActionContext *context) __asm__("func_800E6FB0");

s32 ai_clear_owner_float_parameter(AiActionContext *context)
{
    ai_set_indexed_float(context->owner, 0x1003, 0.0f);
    return -1;
}
