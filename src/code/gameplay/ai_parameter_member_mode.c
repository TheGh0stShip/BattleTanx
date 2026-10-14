#include "types.h"

typedef struct AiParameterMember {
    u8 pad00[0x14];
    u16 flags;
    u8 pad16[2];
    s32 mode;
} AiParameterMember;

typedef struct AiParameterContext {
    u8 pad00[8];
    AiParameterMember *member;
} AiParameterContext;

f32 ai_parameter_member_not_mode_2(AiParameterContext *context) __asm__("func_800E8D14");
f32 ai_parameter_member_flag_4(AiParameterContext *context) __asm__("func_800E8D3C");

f32 ai_parameter_member_not_mode_2(AiParameterContext *context)
{
    f32 result = 0.0f;

    if (context->member->mode != 2) {
        result = 1.0f;
    }
    return result;
}

f32 ai_parameter_member_flag_4(AiParameterContext *context)
{
    f32 result = 1.0f;

    if (!(context->member->flags & 4)) {
        result = 0.0f;
    }
    return result;
}
