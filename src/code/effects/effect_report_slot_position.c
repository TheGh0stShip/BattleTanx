#include "types.h"

typedef struct SlotPosition {
    u8 pad00[0x48];
    f32 value48;
    f32 value4C;
    u8 pad50[0x8];
} SlotPosition;

typedef struct SlotSession {
    u8 pad000[0x568];
    SlotPosition *slots;
} SlotSession;

typedef struct SlotPositionReport {
    s8 valid;
    u8 pad01[0x3];
    f32 value48;
    f32 value4C;
} SlotPositionReport;

typedef struct FrameSlotEffect {
    u8 pad00[0xD];
    u8 frameCount;
    u8 frame;
    u8 pad0F[0x5];
    s16 slot;
} FrameSlotEffect;

extern SlotSession *func_800821C0();

void effect_report_slot_position(FrameSlotEffect *effect, s32 arg1, s32 arg2, SlotPositionReport *report)
    __asm__("func_80093338");

void effect_report_slot_position(FrameSlotEffect *effect, s32 arg1, s32 arg2, SlotPositionReport *report)
{
    SlotPosition *slot;

    if (effect->frame < effect->frameCount - 1) {
        report->valid = 1;
        slot = &func_800821C0()->slots[effect->slot];
        report->value4C = slot->value4C;
        report->value48 = slot->value48;
    }
}
