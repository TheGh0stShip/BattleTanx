#include "types.h"

typedef struct FrameEffect {
    u8 pad00[0xC];
    u8 flags;
    u8 frameCount;
    u8 frame;
    u8 pad0F[0x5];
    s16 index;
} FrameEffect;

typedef struct FrameEffectReport {
    s8 valid;
    u8 pad01[0x3];
    f32 value04;
    f32 value08;
} FrameEffectReport;

typedef struct FrameEffectEntry {
    u8 pad00[0x48];
    f32 value48;
    f32 value4C;
    u8 pad50[0x8];
} FrameEffectEntry;

typedef struct FrameEffectWorld {
    u8 pad000[0x568];
    FrameEffectEntry *entries;
} FrameEffectWorld;

extern FrameEffectWorld *func_800821C0(void);
extern void func_8008B89C(FrameEffect *);
extern void func_80093080(FrameEffect *, s32, s32, FrameEffectReport *);
extern void func_80093F3C(FrameEffect *);

void frame_effect_handle_message(FrameEffect *effect, s32 arg1, u32 message, s32 arg3,
                                 FrameEffectReport *report) __asm__("func_8009345C");

void frame_effect_handle_message(FrameEffect *effect, s32 arg1, u32 message, s32 arg3,
                                 FrameEffectReport *report)
{
    FrameEffectEntry *entry;

    switch (message) {
    case 0:
        func_80093080(effect, arg1, arg3, report);
        break;
    case 2:
        if (effect->frame < effect->frameCount - 1) {
            report->valid = 1;
            entry = &func_800821C0()->entries[effect->index];
            report->value08 = entry->value4C;
            report->value04 = entry->value48;
        }
        break;
    case 3:
        if (effect->frame < effect->frameCount - 1) {
            func_8008B89C(effect);
            func_80093F3C(effect);
            effect->flags |= 0x10;
        }
        break;
    case 7:
        if (effect->frame < effect->frameCount - 1) {
            func_8008B89C(effect);
            func_80093F3C(effect);
        }
        break;
    }
}
