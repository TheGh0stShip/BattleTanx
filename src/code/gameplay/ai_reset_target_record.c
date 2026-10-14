#include "types.h"

typedef struct AiTargetRecord {
    s32 value00;
    s32 value04;
    s32 value08;
    s8 value0C;
    s8 value0D;
    s8 value0E;
    s8 value0F;
    s8 value10;
} AiTargetRecord;

void ai_reset_target_record(s32 unused, AiTargetRecord *record) __asm__("func_800E2ACC");

void ai_reset_target_record(s32 unused, AiTargetRecord *record)
{
    record->value00 = 0;
    record->value04 = 0;
    record->value08 = 0;
    record->value0C = 0;
    record->value0D = 0;
    record->value0E = 0;
    record->value0F = 0;
    record->value10 = 0;
}
