#include "types.h"

typedef struct AiTargetRef {
    s32 kind;
    s32 *point;
    s32 point0;
    s32 point1;
    void *unit;
    s32 metric;
} AiTargetRef;

#define AI_TARGET_NONE 0xB
#define AI_TARGET_POINT 9

void ai_target_clear(AiTargetRef *target) __asm__("func_800E35CC");
void ai_target_set_point(AiTargetRef *target, s32 unused, s32 point1, s32 point0) __asm__("func_800E35F0");

void ai_target_clear(AiTargetRef *target)
{
    target->metric = -1;
    target->unit = 0;
    target->point1 = 0;
    target->point0 = 0;
    target->point = 0;
    target->kind = AI_TARGET_NONE;
}

void ai_target_set_point(AiTargetRef *target, s32 unused, s32 point1, s32 point0)
{
    target->point = &target->point0;
    target->point1 = point1;
    target->point0 = point0;
    target->kind = AI_TARGET_POINT;
}
