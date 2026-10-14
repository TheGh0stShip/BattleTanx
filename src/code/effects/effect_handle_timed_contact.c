#include "types.h"

typedef struct TimedContactEffect {
    u8 pad00[0x18];
    s32 spawnTick;
    s32 disabled;
    u8 pad20[0x4];
    s32 resultData;
} TimedContactEffect;

typedef struct TimedContactRecord {
    u8 pad00[0x8];
    s32 kind;
} TimedContactRecord;

typedef struct TimedContactResult {
    s32 action;
    s32 value;
    s32 data;
} TimedContactResult;

#define CONTACT_KIND_UNIT 0
#define CONTACT_KIND_1D 0x1D
#define CONTACT_ARM_DELAY 60

extern s32 gGameTicks __asm__("D_801B4AA8");
extern void func_8008B89C();

void effect_handle_timed_contact(TimedContactEffect *effect, TimedContactRecord *contact, void *unused,
                                 TimedContactResult *result) __asm__("func_8010DCD0");

void effect_handle_timed_contact(TimedContactEffect *effect, TimedContactRecord *contact, void *unused,
                                 TimedContactResult *result)
{
    if (effect->disabled != 0) {
        return;
    }
    switch (contact->kind) {
    case CONTACT_KIND_UNIT:
        if (effect->spawnTick + CONTACT_ARM_DELAY < gGameTicks) {
            func_8008B89C(effect);
            result->action = 8;
            result->value = 0x1E;
            result->data = effect->resultData;
            return;
        }
        break;
    case CONTACT_KIND_1D:
        func_8008B89C(effect);
        return;
    }
    result->action = 1;
}

typedef struct TimedContactPosition {
    u8 pad00[0xC];
    f32 value0C;
    f32 value10;
} TimedContactPosition;

typedef struct TimedContactReport {
    s8 valid;
    u8 pad01[0x3];
    f32 value0C;
    f32 value10;
} TimedContactReport;

void effect_report_timed_contact_position(TimedContactPosition *effect, void *unused1, void *unused2,
                                          TimedContactReport *report) __asm__("func_8010DD78");

void effect_report_timed_contact_position(TimedContactPosition *effect, void *unused1, void *unused2,
                                          TimedContactReport *report)
{
    report->valid = 1;
    report->value10 = effect->value10;
    report->value0C = effect->value0C;
}
