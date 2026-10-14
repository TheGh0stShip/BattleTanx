#include "types.h"
#include "ai_play_stack.h"

typedef struct AiAheadOwner {
    u8 pad000[0x1AA];
    s16 linkedId;
} AiAheadOwner;

typedef struct AiAheadUnit {
    u8 pad00[0x24];
    f32 x;
    f32 y;
    f32 z;
} AiAheadUnit;

extern AiAheadUnit *get_unit(s16 id) __asm__("func_800A03B8");
extern void ai_measure_relative_point(void *entity, f32 *point, s32 arg2, s32 *result, s32 arg4)
    __asm__("func_800E28DC");
extern f32 D_80074834;

f32 ai_parameter_linked_unit_ahead(AiActionContext *context) __asm__("func_800E9008");

f32 ai_parameter_linked_unit_ahead(AiActionContext *context)
{
    f32 point[2];
    s32 result;
    void *member;
    AiAheadUnit *unit;

    if (((AiAheadOwner *)context->owner)->linkedId == 0xFF) {
        return 0.0f;
    }
    member = context->member;
    unit = get_unit(((AiAheadOwner *)context->owner)->linkedId);
    point[1] = unit->x;
    point[0] = unit->z;
    ai_measure_relative_point(member, point, 0, &result, 0);
    if (result < 0) {
        return 0.0f;
    }
    return D_80074834;
}
