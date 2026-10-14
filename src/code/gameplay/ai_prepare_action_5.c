#include "types.h"

extern void ai_push_param(void *, f32) __asm__("func_800E9A00");
extern void ai_prepare_action_state(void *) __asm__("func_800E6C14");
extern void ai_finalize_action_state(void *) __asm__("func_800E99D4");

s32 ai_prepare_action_5(void *context) __asm__("func_800EB4A4");

s32 ai_prepare_action_5(void *context)
{
    ai_push_param(context, 5.0f);
    ai_prepare_action_state(context);
    ai_finalize_action_state(context);
    return -1;
}
