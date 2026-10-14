#include "types.h"

typedef struct ShotEffect {
    u8 pad00[0xC];
    u32 kind;
    f32 pos[3];
    u16 value1C;
    u8 pad1E[2];
    s32 motion;
    u8 pad24;
    u8 value25;
    u8 value26;
} ShotEffect;

typedef struct ShotTarget {
    u8 pad00[0x18];
    s32 state;
} ShotTarget;

typedef struct ShotContact {
    u8 pad00[0x8];
    u32 kind;
    ShotTarget *target;
} ShotContact;

extern void func_8008B89C(ShotEffect *effect);
extern void func_800905D8(s32 sound, f32 *pos, s32, s32, s32, s32, s32);
extern s32 ai_member_status_is_1(ShotTarget *member) __asm__("func_800E3470");
extern void clear_record_halfword_flags(s32 index, u16 flags) __asm__("func_80106CCC");
extern s16 D_802D5A5A;
extern s16 D_802D5A76;
extern s16 D_802D5A8E;
extern s16 D_802D5AC0;

void shot_effect_handle_contact(ShotEffect *effect, ShotContact *contact, s32 arg2, s32 *result) __asm__("func_800A06F8");

void shot_effect_handle_contact(ShotEffect *effect, ShotContact *contact, s32 arg2, s32 *result) {
    s32 sound;

    switch (contact->kind) {
    case 2:
    case 12:
    case 22:
    case 34:
    case 44:
        if (effect->value25 != 0) {
            *result = 1;
            break;
        }
        switch (effect->kind) {
        case 0:
            sound = D_802D5A5A;
            break;
        case 2:
            sound = D_802D5A8E;
            break;
        case 1:
            sound = D_802D5A76;
            break;
        default:
            sound = 0;
            break;
        }
        func_800905D8(sound, effect->pos, 0, effect->value1C, 0, effect->value26, 0);
        func_8008B89C(effect);
        *result = 0;
        break;
    case 0:
        if (effect->value25 != 0) {
            *result = 4;
            break;
        }
        if (ai_member_status_is_1(contact->target) == 0 || contact->target->state != 1) {
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
            *result = 5;
        }
        if (effect->kind == 1 && contact->target->state == 2) {
            effect->value25 = 1;
            clear_record_halfword_flags(effect->motion, 20);
            *result = 5;
        } else {
            *result = 0;
        }
        break;
    default:
        *result = 0;
        break;
    }
}
