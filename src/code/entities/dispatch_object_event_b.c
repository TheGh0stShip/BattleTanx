#include "types.h"

typedef struct EventObjectB {
    u8 pad00[0xC];
    f32 value0C;
    u8 pad10[0x4];
    f32 value14;
    u8 pad18[0x4];
    u8 inactive;
} EventObjectB;

typedef struct EventReportB {
    s8 valid;
    u8 pad01[0x3];
    f32 value14;
    f32 value0C;
} EventReportB;

extern void func_800ECE4C(EventObjectB *object, s32 arg, s32 data, void *out);
extern void func_800ED380(EventObjectB *object, s32 arg, s32 data, s32 zero);
extern void func_800ED5C8(EventObjectB *object, s32 arg, s32 data);

void dispatch_object_event_b(EventObjectB *object, s32 arg, u32 event, s32 data, void *out)
    __asm__("func_800ED810");

void dispatch_object_event_b(EventObjectB *object, s32 arg, u32 event, s32 data, void *out)
{
    EventReportB *report;

    switch (event) {
    case 0:
        func_800ECE4C(object, arg, data, out);
        break;
    case 2:
        if (object->inactive == 0) {
            report = out;
            report->valid = 1;
            report->value0C = object->value0C;
            report->value14 = object->value14;
        }
        break;
    case 3:
        func_800ED380(object, 0, data, 0);
        break;
    case 7:
        func_800ED5C8(object, arg, data);
        break;
    }
}
