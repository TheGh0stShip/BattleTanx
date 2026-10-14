#include "types.h"

typedef struct ActiveEffect {
    u8 pad00[0xC];
    f32 value0C;
    u8 pad10[0x4];
    f32 value14;
    u8 pad18[0x4];
    u8 inactive;
} ActiveEffect;

typedef struct ActiveEffectReport {
    s8 valid;
    u8 pad01[0x3];
    f32 value14;
    f32 value0C;
} ActiveEffectReport;

void effect_report_position_when_active(ActiveEffect *effect, s32 arg1, s32 arg2, ActiveEffectReport *report)
    __asm__("func_800ED358");

void effect_report_position_when_active(ActiveEffect *effect, s32 arg1, s32 arg2, ActiveEffectReport *report)
{
    if (effect->inactive == 0) {
        report->valid = 1;
        report->value0C = effect->value0C;
        report->value14 = effect->value14;
    }
}
