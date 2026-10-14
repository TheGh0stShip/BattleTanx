#include "ai_action_helpers.h"

extern void ai_set_indexed_float(void *base, u32 key, f32 value) __asm__("func_800E986C");

void ai_store_owner_float_parameter(AiActionContext *context, u32 key, f32 value)
    __asm__("func_800E97F0");

void ai_store_owner_float_parameter(AiActionContext *context, u32 key, f32 value)
{
    if (key & 0x1000) {
        ai_set_indexed_float(context->owner, key, value);
    }
}
