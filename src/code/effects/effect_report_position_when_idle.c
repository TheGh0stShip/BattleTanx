#include "types.h"

typedef struct IdleEffect {
    u8 pad00[0xC];
    f32 value0C;
    f32 value10;
    u8 pad14[0x4];
    u16 busy;
} IdleEffect;

typedef struct IdleEffectReport {
    s8 valid;
    u8 pad01[0x3];
    f32 value0C;
    f32 value10;
} IdleEffectReport;

void effect_report_position_when_idle(IdleEffect *effect, s32 arg1, s32 arg2, IdleEffectReport *report)
    __asm__("func_800EFCA8");

void effect_report_position_when_idle(IdleEffect *effect, s32 arg1, s32 arg2, IdleEffectReport *report)
{
    if (effect->busy == 0) {
        report->valid = 1;
        report->value10 = effect->value10;
        report->value0C = effect->value0C;
    }
}
