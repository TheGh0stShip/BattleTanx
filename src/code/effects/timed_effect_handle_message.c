#include "types.h"

typedef struct TimedEffect {
    u8 pad00[0xC];
    f32 value0C;
    f32 value10;
    u8 pad14[4];
    s32 startTick;
    s32 value1C;
    u8 pad20[4];
    s32 value24;
} TimedEffect;

typedef struct TimedEffectMessage {
    u8 pad00[8];
    s32 sender;
} TimedEffectMessage;

typedef union TimedEffectReport {
    struct {
        s32 kind;
        s32 value04;
        s32 value08;
    } words;
    struct {
        s8 valid;
        u8 pad01[3];
        f32 value04;
        f32 value08;
    } position;
} TimedEffectReport;

extern void func_8008B89C(TimedEffect *effect);
extern s32 gGameTicks __asm__("D_801B4AA8");

void timed_effect_handle_message(TimedEffect *effect, TimedEffectMessage *data, u32 message, s32 arg3,
                                 TimedEffectReport *report) __asm__("func_8010DDD4");

void timed_effect_handle_message(TimedEffect *effect, TimedEffectMessage *data, u32 message, s32 arg3,
                                 TimedEffectReport *report)
{
    s32 sender;

    switch (message) {
    case 0:
        if (effect->value1C != 0) {
            break;
        }
        sender = data->sender;
        if (sender != 0) {
            if (sender == 0x1D) {
                goto release;
            }
            report->words.kind = 1;
        } else if (effect->startTick + 0x3C < gGameTicks) {
            func_8008B89C(effect);
            report->words.kind = 8;
            report->words.value04 = 0x1E;
            report->words.value08 = effect->value24;
        } else {
            report->words.kind = 1;
        }
        break;
    case 2:
        report->position.valid = 1;
        report->position.value08 = effect->value10;
        report->position.value04 = effect->value0C;
        break;
    case 3:
    case 7:
    release:
        func_8008B89C(effect);
        break;
    }
}
