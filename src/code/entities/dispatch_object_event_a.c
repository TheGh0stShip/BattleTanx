#include "types.h"

typedef struct EventObjectA {
    u8 pad00[0x1C];
    f32 value1C;
    f32 value20;
} EventObjectA;

typedef struct EventReportA {
    s8 valid;
    u8 pad01[0x3];
    f32 value1C;
    f32 value20;
} EventReportA;

extern void func_800A27D0(EventObjectA *object, s32 arg, s32 data, void *out);
extern void func_800A2A44(EventObjectA *object, s32 arg, s32 data, s32 zero);
extern void func_800A2C38(EventObjectA *object, s32 arg, s32 data);

void dispatch_object_event_a(EventObjectA *object, s32 arg, u32 event, s32 data, void *out)
    __asm__("func_800A2EA4");

void dispatch_object_event_a(EventObjectA *object, s32 arg, u32 event, s32 data, void *out)
{
    EventReportA *report;

    switch (event) {
    case 0:
        func_800A27D0(object, arg, data, out);
        break;
    case 2:
        report = out;
        report->valid = 1;
        report->value20 = object->value20;
        report->value1C = object->value1C;
        break;
    case 3:
        func_800A2A44(object, 0, data, 0);
        break;
    case 7:
        func_800A2C38(object, arg, data);
        break;
    }
}
