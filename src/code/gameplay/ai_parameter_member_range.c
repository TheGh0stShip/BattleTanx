#include "types.h"

typedef struct AiParameterContext {
    u8 pad00[0x8];
    void *member;
} AiParameterContext;

extern s32 ai_member_within_range(void *member) __asm__("func_800E2D40");

f32 ai_parameter_member_within_range(AiParameterContext *context) __asm__("func_800E9538");
f32 ai_parameter_member_outside_range(AiParameterContext *context) __asm__("func_800E9570");

f32 ai_parameter_member_within_range(AiParameterContext *context)
{
    if (ai_member_within_range(context->member)) {
        return 1.0f;
    }
    return 0.0f;
}

f32 ai_parameter_member_outside_range(AiParameterContext *context)
{
    return ai_member_within_range(context->member) == 0 ? 1.0f : 0.0f;
}
