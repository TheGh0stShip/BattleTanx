#include "types.h"

typedef struct AiProgressMember {
    u8 pad000[0x1C];
    s32 current;
    s32 limit;
    u8 pad024[0x338];
    u16 base;
} AiProgressMember;

typedef struct AiParameterContext {
    u8 pad00[0x8];
    AiProgressMember *member;
} AiParameterContext;

extern f32 ai_get_parameter(AiParameterContext *context, s32 key) __asm__("func_800E9720");

f32 ai_parameter_inverse_member_value_0(AiParameterContext *context) __asm__("func_800E9098");
f32 ai_parameter_inverse_member_value_1(AiParameterContext *context) __asm__("func_800E90C0");
f32 ai_parameter_member_progress(AiParameterContext *context) __asm__("func_800E90E8");
f32 ai_parameter_inverse_member_progress(AiParameterContext *context) __asm__("func_800E9148");

f32 ai_parameter_inverse_member_value_0(AiParameterContext *context)
{
    return 1.0f - ai_get_parameter(context, 0x1000);
}

f32 ai_parameter_inverse_member_value_1(AiParameterContext *context)
{
    return 1.0f - ai_get_parameter(context, 0x1001);
}

/* (current - base) / (limit - base), with current first clamped to limit. */
f32 ai_parameter_member_progress(AiParameterContext *context)
{
    AiProgressMember *member = context->member;
    s32 span = member->current - member->base;

    if (member->limit < member->current) {
        member->current = member->limit;
    }
    if (span > 0) {
        return (f32)span / (f32)(context->member->limit - context->member->base);
    }
    return 0.0f;
}

f32 ai_parameter_inverse_member_progress(AiParameterContext *context)
{
    AiProgressMember *member = context->member;
    s32 span = member->current - member->base;
    f32 progress;

    if (member->limit < member->current) {
        member->current = member->limit;
    }
    if (span > 0) {
        progress = (f32)span / (f32)(context->member->limit - context->member->base);
    } else {
        progress = 0.0f;
    }
    return 1.0f - progress;
}
