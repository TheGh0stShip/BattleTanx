#include "types.h"

typedef struct DispatchSlotPosition {
    u8 pad00[0x48];
    f32 value48;
    f32 value4C;
    u8 pad50[0x8];
} DispatchSlotPosition;

typedef struct DispatchSlotSession {
    u8 pad000[0x568];
    DispatchSlotPosition *slots;
} DispatchSlotSession;

typedef struct DispatchPositionReport {
    s8 valid;
    u8 pad01[0x3];
    f32 value48;
    f32 value4C;
} DispatchPositionReport;

typedef struct DispatchSlotEffect {
    u8 pad00[0xC];
    u8 flags;
    u8 pad0D[0x13];
    s32 slot;
} DispatchSlotEffect;

extern DispatchSlotSession *func_800821C0(void);
extern void func_800F0738(DispatchSlotEffect *effect, s32 arg1, s32 arg3, DispatchPositionReport *report);
extern void func_800F09D0(DispatchSlotEffect *effect, s32 arg1, s32 arg3, s32 arg4);
extern void func_800F0B60(DispatchSlotEffect *effect, s32 arg1, s32 arg3);

void effect_slot_message_dispatch(DispatchSlotEffect *effect, s32 arg1, u32 message, s32 arg3,
                                  DispatchPositionReport *report) __asm__("func_800F0CF0");

void effect_slot_message_dispatch(DispatchSlotEffect *effect, s32 arg1, u32 message, s32 arg3,
                                  DispatchPositionReport *report)
{
    DispatchSlotPosition *slot;

    switch (message) {
    case 0:
        func_800F0738(effect, arg1, arg3, report);
        return;
    case 2:
        if (!(effect->flags & 4)) {
            report->valid = 1;
            slot = &func_800821C0()->slots[effect->slot];
            report->value4C = slot->value4C;
            report->value48 = slot->value48;
        }
        return;
    case 3:
        func_800F09D0(effect, 0, arg3, 0);
        return;
    case 7:
        func_800F0B60(effect, arg1, arg3);
        break;
    }
}
