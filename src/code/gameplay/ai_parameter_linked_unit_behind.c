#include "types.h"
#include "ai_play_stack.h"

typedef struct AiBehindOwner {
    u8 pad000[0x1AA];
    s16 linkedId;
} AiBehindOwner;

typedef struct AiBehindUnit {
    u8 pad00[0x24];
    f32 x;
    f32 y;
    f32 z;
} AiBehindUnit;

extern AiBehindUnit *get_unit(s16 id) __asm__("func_800A03B8");
extern void ai_measure_relative_point(void *entity, f32 *point, s32 arg2, s32 *result, s32 arg4)
    __asm__("func_800E28DC");
extern f32 D_80074830;

f32 ai_parameter_linked_unit_behind(AiActionContext *context) __asm__("func_800E8F84");

f32 ai_parameter_linked_unit_behind(AiActionContext *context)
{
    f32 point[2];
    s32 result;
    s16 id = ((AiBehindOwner *)context->owner)->linkedId;
    void *member;
    AiBehindUnit *unit;
    f32 value;

    if (id != 0xFF) {
        member = context->member;
        unit = get_unit(id);
        point[1] = unit->x;
        point[0] = unit->z;
        ai_measure_relative_point(member, point, 0, &result, 0);
        value = D_80074830;
        if (result >= 0) {
            value = 0.0f;
        }
        return value;
    }
    return 0.0f;
}
