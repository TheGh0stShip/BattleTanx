#include "types.h"

typedef struct GridEffect {
    u8 pad00[0xC];
    s32 value0C;
    s32 value10;
    u8 pad14[0x8];
    u8 value1C;
    u8 flags;
    s16 heading;
} GridEffect;

typedef struct GridContact {
    u8 pad00[0x8];
    u32 kind;
    s32 source;
} GridContact;

typedef struct GridMessageArg {
    f32 value00;
    f32 value04;
    u8 pad08[0x4];
    u16 value0C;
    u8 pad0E[0xA];
    u8 value18;
} GridMessageArg;

typedef struct GridReport {
    s8 valid;
    u8 pad01[0x3];
    f32 value04;
    f32 value08;
} GridReport;

extern float sqrtf(float);
extern void release_effect(GridEffect *effect) __asm__("func_8008B89C");
extern void unit_update_sound_ramp(s32 unit, s32 soundId) __asm__("func_80099CD8");
extern s32 radians_to_angle(f32 radians) __asm__("func_800F3BE4");

void grid_effect_handle_message(GridEffect *effect, GridContact *contact, u32 message, GridMessageArg *arg, s32 *result)
    __asm__("func_80090BE0");

void grid_effect_handle_message(GridEffect *effect, GridContact *contact, u32 message, GridMessageArg *arg, s32 *result)
{
    f32 dz;
    f32 dx;

    switch (message) {
    case 0:
        switch (contact->kind) {
        case 34:
            if ((effect->flags & 4) && arg->value18 == 0) {
                break;
            }
        case 2:
        case 12:
        case 22:
            release_effect(effect);
            *result = 0;
            break;
        case 0:
            unit_update_sound_ramp(contact->source, 0x23);
            effect->value1C = 1;
            effect->heading = arg->value0C;
            release_effect(effect);
            *result = 4;
            break;
        case 5:
        case 18:
            release_effect(effect);
            break;
        }
        break;
    case 2:
        ((GridReport *)result)->valid = 1;
        ((GridReport *)result)->value08 = effect->value0C;
        ((GridReport *)result)->value04 = effect->value10;
        break;
    case 3:
        dz = arg->value04 - (f32)effect->value0C;
        dx = arg->value00 - (f32)effect->value10;
        if ((dz != 0.0f) | (dx != 0.0f)) {
            effect->value1C = 1;
            if (-dz < 0.0f) {
                effect->heading = -radians_to_angle(-dx / sqrtf(dz * dz + dx * dx));
            } else {
                effect->heading = radians_to_angle(-dx / sqrtf(dz * dz + dx * dx));
            }
        }
        effect->flags |= 8;
        release_effect(effect);
        break;
    case 7:
        dz = arg->value04 - (f32)effect->value0C;
        dx = arg->value00 - (f32)effect->value10;
        if ((dz != 0.0f) | (dx != 0.0f)) {
            effect->value1C = 1;
            if (-dz < 0.0f) {
                effect->heading = -radians_to_angle(-dx / sqrtf(dz * dz + dx * dx));
            } else {
                effect->heading = radians_to_angle(-dx / sqrtf(dz * dz + dx * dx));
            }
        }
        release_effect(effect);
        break;
    }
}
