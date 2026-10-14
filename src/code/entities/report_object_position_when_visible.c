#include "types.h"

typedef struct VisibleObject {
    u8 pad00[0x10];
    f32 value10;
    u8 pad14[0x4];
    f32 value18;
    u8 pad1C[0x9];
    u8 hidden;
} VisibleObject;

typedef struct VisibleObjectReport {
    s8 valid;
    u8 pad01[0x3];
    f32 value18;
    f32 value10;
} VisibleObjectReport;

void report_object_position_when_visible(VisibleObject *object, s32 arg1, s32 arg2, VisibleObjectReport *report)
    __asm__("func_800A0908");

void report_object_position_when_visible(VisibleObject *object, s32 arg1, s32 arg2, VisibleObjectReport *report)
{
    if (object->hidden == 0) {
        report->valid = 1;
        report->value10 = object->value10;
        report->value18 = object->value18;
    }
}
