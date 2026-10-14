#include "types.h"

typedef struct PositionEffect {
    u8 pad00[0xC];
    s32 value0C;
    s32 value10;
} PositionEffect;

typedef struct PositionReport {
    s8 valid;
    u8 pad01[0x3];
    f32 value10;
    f32 value0C;
} PositionReport;

void effect_report_position(PositionEffect *effect, void *unused1, void *unused2, PositionReport *report)
    __asm__("func_800908CC");

void effect_report_position(PositionEffect *effect, void *unused1, void *unused2, PositionReport *report)
{
    report->valid = 1;
    report->value0C = effect->value0C;
    report->value10 = effect->value10;
}
