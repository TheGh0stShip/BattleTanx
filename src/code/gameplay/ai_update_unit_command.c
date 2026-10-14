#include "types.h"

typedef struct AiUnitCommand {
    s32 value00;
    f32 value04;
    s32 value08;
    s8 value0C;
    s8 value0D;
    s8 value0E;
    s8 value0F;
    s8 value10;
} AiUnitCommand;

typedef struct AiLinkedEntity {
    u8 pad000[0x1A0];
    f32 value1A0;
    u8 value1A4;
} AiLinkedEntity;

typedef struct AiUnit {
    u8 pad00[0x1];
    u8 value01;
    u8 pad02[0x2];
    u8 value04;
    u8 pad05[0x14 - 0x5];
    u16 value14;
    u8 pad16[0x2];
    s32 value18;
    u8 pad1C[0x24 - 0x1C];
    f32 value24;
    u8 pad28[0x4];
    f32 value2C;
    u8 pad30[0x98 - 0x30];
    s32 value98;
    u32 value9C;
    s32 valueA0;
    u8 valueA4[0xAC - 0xA4];
    u8 *valueAC;
    u8 padB0[0x4];
    u32 valueB4;
    void *valueB8;
    u8 padBC[0x34A - 0xBC];
    u8 value34A;
    u8 pad34B[0x35E - 0x34B];
    u16 value35E;
    u8 pad360[0x368 - 0x360];
    s32 value368;
} AiUnit;

extern AiLinkedEntity *get_linked_entity(u8 id) __asm__("func_800A6688");
extern f32 approx_xz_distance(void *a, void *b) __asm__("func_800E0D54");
extern f32 ai_member_horizontal_distance(AiUnit *unit, void *point) __asm__("func_800E1A20");
extern void func_800E1D40(AiUnit *unit, u32 *mode, f32 *point);
extern void func_800E21E4(AiUnit *unit, AiUnitCommand *out, void *target);
extern void func_800E28DC(AiUnit *unit, void *target, s32 *angle, s32 arg3, s32 arg4);
extern void func_800E2AF0(AiUnit *unit, AiUnitCommand *out, void *target);
extern void func_800E2DE8(AiUnit *unit, AiUnitCommand *out);
extern s32 ai_unit_in_expected_state(AiUnit *unit) __asm__("func_800E3BC0");
extern f32 ai_normalized_elapsed_time(s32 startTime) __asm__("func_800E95A8");

static inline void apply_unit_target(AiUnit *unit, AiUnitCommand *out) {
    if (unit->valueB4 != 0) {
        if (unit->valueB4 < 5) {
            func_800E2AF0(unit, out, unit->valueB8);
        }
    } else {
        func_800E2AF0(unit, out, 0);
    }
}

void ai_update_unit_command(AiUnit *unit, AiUnitCommand *out) __asm__("func_800E30F8");

void ai_update_unit_command(AiUnit *unit, AiUnitCommand *out) {
    f32 point[2];
    s32 angle;
    s32 a;
    AiLinkedEntity *linked;
    void *target;
    s32 inRange;
    s32 close;
    s32 near;
    f32 dist;
    f32 value;

    get_linked_entity(unit->value04);
    out->value00 = 0;
    out->value04 = 0.0f;
    out->value08 = 0;
    out->value0C = 0;
    out->value0D = 0;
    out->value0E = 0;
    out->value0F = 0;
    out->value10 = 0;
    if (unit->value01 == 0) {
        return;
    }
    point[1] = unit->value24;
    point[0] = unit->value2C;
    func_800E1D40(unit, &unit->value9C, point);
    if (unit->value14 & 4) {
        ai_normalized_elapsed_time(unit->value368);
        apply_unit_target(unit, out);
        linked = get_linked_entity(unit->value04);
        value = linked->value1A0;
        if (linked->value1A4 != 0) {
            value = -value;
        }
        out->value04 = value;
        return;
    }
    if (unit->value18 == 1) {
        target = unit->valueB8;
        inRange = 0;
        if (target != 0 && ai_member_horizontal_distance(unit, target) <= 500.0f) {
            inRange = 1;
        }
        if (unit->value98 == 0) {
            if (unit->value34A != 0 && unit->valueA0 != 0) {
                switch (unit->value9C) {
                case 6:
                    dist = ai_member_horizontal_distance(unit, unit->valueA4);
                    break;
                case 7:
                    dist = ai_member_horizontal_distance(unit, unit->valueA4);
                    break;
                case 5:
                    dist = approx_xz_distance(&unit->value24, unit->valueAC + 0x24);
                    break;
                default:
                    dist = 16000.0f;
                    break;
                }
                close = 1;
                if (!(dist < unit->value35E)) {
                    close = 0;
                }
                if (close == 0 && (inRange == 0 || ai_unit_in_expected_state(unit) == 0)) {
                    goto chase;
                }
            }
            apply_unit_target(unit, out);
            return;
        }
    chase:
        func_800E2DE8(unit, out);
        if (target != 0) {
            func_800E28DC(unit, target, &angle, 0, 0);
            a = angle;
            if (a < 0) {
                a = -a;
            }
            if (a < 400) {
                func_800E21E4(unit, out, target);
            }
        }
        return;
    }
    near = 0;
    if (unit->valueB8 != 0 && ai_member_horizontal_distance(unit, unit->valueB8) <= 500.0f) {
        near = 1;
    }
    if (unit->value18 == 2) {
        ai_normalized_elapsed_time(unit->value368);
        apply_unit_target(unit, out);
    } else {
        ai_normalized_elapsed_time(unit->value368);
        apply_unit_target(unit, out);
    }
    if (unit->value34A != 0 && (near == 0 || ai_unit_in_expected_state(unit) == 0)) {
        func_800E2DE8(unit, out);
    }
}
