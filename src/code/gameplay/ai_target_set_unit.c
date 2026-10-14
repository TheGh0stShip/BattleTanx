#include "types.h"

typedef struct TargetUnit {
    u8 pad00[0x24];
    f32 value24;
    u8 pad28[0x4];
    f32 value2C;
} TargetUnit;

typedef struct AiTargetRef {
    s32 valid;
    f32 *point;
    f32 point0;
    f32 point1;
    TargetUnit *unit;
    s32 metric;
} AiTargetRef;

extern TargetUnit *get_unit(s16 id) __asm__("func_800A03B8");
extern s32 func_800E52A0(s16 fromId, s16 toId);

void ai_target_set_unit(AiTargetRef *target, s16 fromId, s16 toId) __asm__("func_800E34B4");

void ai_target_set_unit(AiTargetRef *target, s16 fromId, s16 toId)
{
    TargetUnit *unit;

    if (toId != 0xFF) {
        get_unit(fromId);
        unit = get_unit(toId);
        target->unit = unit;
        target->metric = func_800E52A0(fromId, toId);
        target->point1 = unit->value24;
        target->point0 = unit->value2C;
        target->point = &target->point0;
        target->valid = 1;
    } else {
        target->valid = 0;
        target->point = 0;
    }
}
