#include "types.h"

typedef struct AiParameterOwner {
    u8 pad000[0x198];
    s32 timerRange[2];
    u8 pad1A0[0x8];
    u16 objectiveId;
} AiParameterOwner;

typedef struct AiParameterContext {
    u8 pad00[0x4];
    AiParameterOwner *owner;
} AiParameterContext;

extern s32 get_frame_time(void) __asm__("func_8007B1DC");
extern f32 get_range_progress(s32 *range, s32 time) __asm__("func_8007B208");
extern f32 ai_get_parameter(AiParameterContext *context, s32 key) __asm__("func_800E9720");

f32 ai_parameter_owner_objective_is_0(AiParameterContext *context) __asm__("func_800E867C");
f32 ai_parameter_owner_objective_is_1(AiParameterContext *context) __asm__("func_800E86A0");
f32 ai_parameter_owner_objective_is_2(AiParameterContext *context) __asm__("func_800E86C8");
f32 ai_parameter_owner_objective_is_3(AiParameterContext *context) __asm__("func_800E86F0");
f32 ai_parameter_inverse_owner_value_0(AiParameterContext *context) __asm__("func_800E8718");
f32 ai_parameter_inverse_owner_value_1(AiParameterContext *context) __asm__("func_800E8740");
f32 ai_parameter_owner_timer_progress(AiParameterContext *context) __asm__("func_800E8768");

f32 ai_parameter_owner_objective_is_0(AiParameterContext *context)
{
    return context->owner->objectiveId == 0 ? 1.0f : 0.0f;
}

f32 ai_parameter_owner_objective_is_1(AiParameterContext *context)
{
    return context->owner->objectiveId == 1 ? 1.0f : 0.0f;
}

f32 ai_parameter_owner_objective_is_2(AiParameterContext *context)
{
    return context->owner->objectiveId == 2 ? 1.0f : 0.0f;
}

f32 ai_parameter_owner_objective_is_3(AiParameterContext *context)
{
    return context->owner->objectiveId == 3 ? 1.0f : 0.0f;
}

f32 ai_parameter_inverse_owner_value_0(AiParameterContext *context)
{
    return 1.0f - ai_get_parameter(context, 0x2000);
}

f32 ai_parameter_inverse_owner_value_1(AiParameterContext *context)
{
    return 1.0f - ai_get_parameter(context, 0x2001);
}

f32 ai_parameter_owner_timer_progress(AiParameterContext *context)
{
    return get_range_progress(context->owner->timerRange, get_frame_time());
}
