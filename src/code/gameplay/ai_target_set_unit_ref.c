#include "types.h"

typedef struct TargetUnit TargetUnit;

typedef struct AiTargetRef {
    s32 kind;
    f32 *point;
    f32 point0;
    f32 point1;
    TargetUnit *unit;
    s32 metric;
} AiTargetRef;

extern TargetUnit *get_unit(s16 id) __asm__("func_800A03B8");
extern s32 func_800E52A0(s16 fromId, s16 toId);

void ai_target_set_unit_ref(AiTargetRef *target, s16 fromId, s16 toId) __asm__("func_800E3AB0");

void ai_target_set_unit_ref(AiTargetRef *target, s16 fromId, s16 toId)
{
    if (toId != 0xFF) {
        get_unit(fromId);
        target->unit = get_unit(toId);
        target->metric = func_800E52A0(fromId, toId);
        target->point = 0;
        target->kind = 5;
    } else {
        target->kind = 0;
        target->point = 0;
    }
}
