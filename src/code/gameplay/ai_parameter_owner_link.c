#include "types.h"

typedef struct AiLinkUnit {
    u8 pad00[0x24];
    f32 x;
    f32 y;
    f32 z;
} AiLinkUnit;

typedef struct AiLinkOwner {
    u8 pad000[0x1AA];
    s16 linkedId;
} AiLinkOwner;

typedef struct AiParameterContext {
    u8 pad00[0x4];
    AiLinkOwner *owner;
} AiParameterContext;

extern AiLinkUnit *get_unit(s16 id) __asm__("func_800A03B8");
extern void ai_measure_relative_point(void *entity, f32 *point, s32 arg2, s32 *result, s32 arg4)
    __asm__("func_800E28DC");

s32 ai_unit_relative_result_negative(void *entity, s16 unitId) __asm__("func_800E8DFC");
f32 ai_parameter_owner_has_link(AiParameterContext *context) __asm__("func_800E8E5C");
f32 ai_parameter_owner_lacks_link(AiParameterContext *context) __asm__("func_800E8E84");

s32 ai_unit_relative_result_negative(void *entity, s16 unitId)
{
    AiLinkUnit *unit = get_unit(unitId);
    f32 point[2];
    s32 result;

    point[1] = unit->x;
    point[0] = unit->z;
    ai_measure_relative_point(entity, point, 0, &result, 0);
    return (u32)result >> 31;
}

f32 ai_parameter_owner_has_link(AiParameterContext *context)
{
    return context->owner->linkedId != 0xFF ? 1.0f : 0.0f;
}

f32 ai_parameter_owner_lacks_link(AiParameterContext *context)
{
    f32 linked = 1.0f;

    if (context->owner->linkedId == 0xFF) {
        linked = 0.0f;
    }
    return 1.0f - linked;
}
