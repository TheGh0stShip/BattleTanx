#include "types.h"

#define HEADING_TURN_STEP 0.0f

typedef struct UnitVec3 {
    f32 x;
    f32 y;
    f32 z;
} UnitVec3;

typedef struct UnitMatrix {
    f32 m[4][4];
} UnitMatrix;

typedef struct MessageUnit {
    u8 pad000[0x1C];
    s32 value1C;
    u8 pad020[0x4];
    UnitVec3 position;
    UnitVec3 rotation;
    u8 pad03C[0x3D8 - 0x3C];
    f32 tiltX;
    f32 tiltZ;
    f32 value3E0;
    f32 value3E4;
    u8 pad3E8[0x3F8 - 0x3E8];
    f32 heading;
    f32 targetHeading;
    u8 pad400[0x40C - 0x400];
    UnitMatrix transform;
    u8 pad44C[0x458 - 0x44C];
    s32 sound458;
    s32 sound45C;
    u8 pad460[0x4F0 - 0x460];
    s32 sound4F0;
} MessageUnit;

typedef struct MessageContext {
    u8 pad00[0xC];
    MessageUnit *unit;
    u8 value10;
} MessageContext;

typedef struct DamageMessage {
    u8 pad00[0x8];
    s32 amount;
    u32 attacker;
} DamageMessage;

extern void unit_handle_hit_message(MessageContext *context, void *message, void *data, void *report)
    __asm__("func_8009EEC0");
extern void apply_proximity_hit_to_target(MessageContext *context, s32 arg1, void *data, s32 arg3)
    __asm__("func_8009F36C");
extern s32 set_and_trigger_sound(s32 id) __asm__("func_800798C0");
extern s32 apply_unit_damage(MessageUnit *unit, s32 amount, u32 attacker, s32 direct) __asm__("func_800983E0");
extern void euler_angles_to_matrix(void *matrix, UnitVec3 *angles) __asm__("func_800A7964");
extern void load_render_translation(void *matrix, UnitVec3 *vector) __asm__("func_800A76A0");

void unit_handle_message(MessageContext *context, void *message, u32 kind, void *data, void *report)
    __asm__("func_8009F5E0");

void unit_handle_message(MessageContext *context, void *message, u32 kind, void *data, void *report) {
    switch (kind) {
    case 0:
        unit_handle_hit_message(context, message, data, report);
        break;
    case 1: {
        u32 mode = *(u32 *)data;
        MessageUnit *unit = context->unit;

        switch (mode) {
        case 0:
            euler_angles_to_matrix(report, &unit->rotation);
            load_render_translation(report, &unit->position);
            break;
        case 1:
            *(UnitMatrix *)report = unit->transform;
            break;
        case 2: {
            UnitVec3 angles = { unit->tiltX, 0.0f, unit->tiltZ };
            f32 diff;

            diff = unit->targetHeading - unit->heading;

            while (diff > 180.0) {
                diff -= 360.0;
            }
            while (diff < -180.0) {
                diff += 360.0;
            }
            if (diff > HEADING_TURN_STEP) {
                unit->heading = unit->targetHeading - HEADING_TURN_STEP;
            } else if (diff < -HEADING_TURN_STEP) {
                unit->heading = unit->targetHeading + HEADING_TURN_STEP;
            }
            angles.y = unit->heading;
            euler_angles_to_matrix(report, &angles);
            load_render_translation(report, &unit->position);
            break;
        }
        }
        break;
    }
    case 2:
        if (context->unit->value1C > 0) {
            *(u8 *)report = 2;
            context->value10 = 0;
        }
        break;
    case 3:
        apply_proximity_hit_to_target(context, 0, data, 0);
        break;
    case 4: {
        MessageUnit *unit = context->unit;

        if (unit->sound458 != -1) {
            set_and_trigger_sound(unit->sound458);
            unit->sound458 = -1;
        }
        if (unit->sound45C != -1) {
            set_and_trigger_sound(unit->sound45C);
            unit->sound45C = -1;
        }
        if (unit->sound4F0 != -1) {
            set_and_trigger_sound(unit->sound4F0);
            unit->sound4F0 = -1;
        }
        break;
    }
    case 6:
        *(UnitVec3 *)report = context->unit->position;
        break;
    case 7: {
        MessageUnit *unit = context->unit;

        apply_unit_damage(unit, ((DamageMessage *)data)->amount, ((DamageMessage *)data)->attacker, 0);
        unit->value3E0 += ((DamageMessage *)data)->amount / 4;
        unit->value3E4 += ((DamageMessage *)data)->amount / 4;
        break;
    }
    }
}
