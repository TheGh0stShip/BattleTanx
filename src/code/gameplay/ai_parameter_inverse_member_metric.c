#include "types.h"

typedef struct AiParameterContext AiParameterContext;

extern f32 ai_member_metric_9318(AiParameterContext *context) __asm__("func_800E9318");

f32 ai_parameter_inverse_member_metric(AiParameterContext *context) __asm__("func_800E9458");

f32 ai_parameter_inverse_member_metric(AiParameterContext *context)
{
    return 1.0f - ai_member_metric_9318(context);
}
