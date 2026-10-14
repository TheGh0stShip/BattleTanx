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

typedef struct SlotTarget {
    f32 x;
    f32 z;
} SlotTarget;

typedef struct SlotHeadingEffect {
    u8 pad00[0xC];
    u8 flags;
    u8 pad0D[0x5];
    s16 slot;
    u8 pad14[0xA];
    s16 heading;
} SlotHeadingEffect;

extern float sqrtf(float);
extern SlotSession *func_800821C0(void);
extern void func_8008B89C(SlotHeadingEffect *effect);
extern void func_80093590(SlotHeadingEffect *effect, s32 arg1, SlotTarget *target, SlotPositionReport *report);
extern s16 radians_to_angle(f32 radians) __asm__("func_800F3BE4");

void slot_heading_effect_handle_message(SlotHeadingEffect *effect, s32 arg1, u32 message, SlotTarget *target,
                                        SlotPositionReport *report) __asm__("func_80093A5C");

static inline void slot_heading_effect_face_target(SlotHeadingEffect *effect, SlotTarget *target) {
    SlotPosition *slot;
    f32 dz;
    f32 dx;

    effect->flags |= 3;
    slot = &func_800821C0()->slots[effect->slot];
    dz = target->z - slot->value4C;
    dx = target->x - slot->value48;
    if ((dz != 0.0f) | (dx != 0.0f)) {
        effect->flags |= 8;
        if (-dz < 0.0f) {
            effect->heading = -radians_to_angle(-dx / sqrtf(dz * dz + dx * dx));
        } else {
            effect->heading = radians_to_angle(-dx / sqrtf(dz * dz + dx * dx));
        }
    }
    func_8008B89C(effect);
}

void slot_heading_effect_handle_message(SlotHeadingEffect *effect, s32 arg1, u32 message, SlotTarget *target,
                                        SlotPositionReport *report) {
    SlotPosition *slot;

    switch (message) {
    case 0:
        func_80093590(effect, arg1, target, report);
        break;
    case 2:
        if (!(effect->flags & 4)) {
            report->valid = 1;
            slot = &func_800821C0()->slots[effect->slot];
            report->value4C = slot->value4C;
            report->value48 = slot->value48;
        }
        break;
    case 3:
        if (!(effect->flags & 4)) {
            slot_heading_effect_face_target(effect, target);
        }
        break;
    case 7:
        if (!(effect->flags & 4)) {
            slot_heading_effect_face_target(effect, target);
        }
        break;
    }
}
