#include "types.h"

typedef struct ShotEffect {
    u8 pad00[0xC];
    u32 kind;
    f32 pos[3];
    u16 value1C;
    u8 pad1E[7];
    u8 value25;
    u8 value26;
} ShotEffect;

typedef struct ShotEffectReport {
    s8 valid;
    u8 pad01[0x3];
    f32 value04;
    f32 value08;
} ShotEffectReport;

extern void func_8008B89C(ShotEffect *);
extern void func_800905D8(s32 sound, f32 *pos, s32, s32, s32, s32, s32);
extern void func_800A06F8(ShotEffect *, s32, s32, ShotEffectReport *);
extern void func_800A0930(ShotEffect *, s32, s32, s32);
extern s16 D_802D5A5A;
extern s16 D_802D5A76;
extern s16 D_802D5A8E;
extern s16 D_802D5AC0;

void shot_effect_handle_message(ShotEffect *effect, s32 arg1, u32 message, s32 arg3, ShotEffectReport *report)
    __asm__("func_800A0B8C");

void shot_effect_handle_message(ShotEffect *effect, s32 arg1, u32 message, s32 arg3, ShotEffectReport *report)
{
    s32 sound;

    switch (message) {
    case 0:
        func_800A06F8(effect, arg1, arg3, report);
        break;
    case 2:
        if (effect->value25 == 0) {
            report->valid = 1;
            report->value08 = effect->pos[0];
            report->value04 = effect->pos[2];
        }
        break;
    case 3:
        func_800A0930(effect, 0, arg3, 0);
        break;
    case 4:
        switch (effect->kind) {
        case 0:
            sound = D_802D5A5A;
            break;
        case 2:
            sound = D_802D5A8E;
            break;
        case 1:
            if (effect->value25 != 0) {
                sound = D_802D5AC0;
            } else {
                sound = D_802D5A76;
            }
            break;
        default:
            sound = 0;
            break;
        }
        func_800905D8(sound, effect->pos, 0, effect->value1C, 0, effect->value26, 0);
        func_8008B89C(effect);
        break;
    }
}
