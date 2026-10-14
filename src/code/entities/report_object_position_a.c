#include "types.h"

typedef struct PositionObjectA {
    u8 pad00[0x1C];
    f32 value1C;
    f32 value20;
} PositionObjectA;

typedef struct PositionReportA {
    s8 valid;
    u8 pad01[0x3];
    f32 value1C;
    f32 value20;
} PositionReportA;

void report_object_position_a(PositionObjectA *object, s32 arg1, s32 arg2, PositionReportA *report)
    __asm__("func_800A2A28");

void report_object_position_a(PositionObjectA *object, s32 arg1, s32 arg2, PositionReportA *report)
{
    report->valid = 1;
    report->value20 = object->value20;
    report->value1C = object->value1C;
}
