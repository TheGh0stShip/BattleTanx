#include "types.h"

typedef struct PadState {
    s8 stickX;
    s8 stickY;
    u8 pad02[2];
    u32 held;
    u32 pressed;
    u8 pad0C[4];
} PadState;

typedef struct InputBindings {
    u32 fire;
    u32 special;
    u32 alt;
    u8 pad0C[8];
    u32 boost;
    u32 axis18;
    u32 axis18Neg;
    u32 axis20;
    u32 axis20Neg;
    u32 axis28;
    u32 axis28Neg;
    u32 axis30;
    u32 axis30Neg;
    u32 axis38;
    u32 axis38Neg;
    u32 brake;
} InputBindings;

typedef struct OwnerRecord {
    u8 pad000[0x23];
    u8 status;
    u8 pad024[0xCC];
    u8 active;
    u8 pad0F1[0xCF];
    InputBindings bindings;
    u8 value204;
} OwnerRecord;

typedef struct DriveInput {
    f32 turn;
    f32 move;
    f32 aim;
    u8 fire;
    u8 firePressed;
    u8 special;
    u8 specialPressed;
    u8 boost;
    u8 brake;
} DriveInput;

typedef struct DriveUnit {
    u8 pad00;
    u8 alive;
    u8 pad02;
    u8 local;
    u8 owner;
    u8 pad05[0xF];
    u16 flags;
    u8 pad16[2];
    s32 value18;
    u8 pad1C[3];
    u8 value23;
} DriveUnit;

typedef struct UnitTask {
    u8 pad00[0xC];
    DriveUnit *unit;
    u8 pad10;
    u8 replay;
    u16 replayIndex;
} UnitTask;

extern u8 D_80134E68;
extern OwnerRecord *get_entity_record(u16 index) __asm__("func_800A6688");
extern PadState *read_player_controller(s32 player) __asm__("func_80096784");
extern u16 func_80096834(s32 player);
extern void bzero(void *ptr, s32 size) __asm__("func_80110C00");
extern s32 func_800EC700(u16 index);
extern void update_unit_from_pose(DriveUnit *unit, s32 pose) __asm__("func_8009CA6C");
extern s32 func_800E3460(DriveUnit *unit);
extern void func_800E30F8(DriveUnit *unit, DriveInput *input);
extern void func_8009BBC0(DriveUnit *unit, DriveInput *input);
extern void func_8009A354(DriveUnit *unit, DriveInput *input, s32 mode);
extern void func_8009EDD0(DriveUnit *unit);
extern void destroy_unit(DriveUnit *unit, u32 killer, s32 spawnWreck) __asm__("func_80097DD0");
extern s32 *get_game_mode(void) __asm__("func_8007AAF4");
extern void func_800A5B6C(s32 player, s32 value);

#define READ_AXIS(bind, neg)                                              \
    binding = (bind);                                                     \
    switch (binding) {                                                    \
    case 0x200000:                                                        \
        if (pad->stickX >= 0 ? 3.0 < pad->stickX : 3.0 < -pad->stickX) {  \
            value = pad->stickX;                                          \
        } else {                                                          \
        case 0x100000:                                                    \
            value = 0.0f;                                                 \
        }                                                                 \
        break;                                                            \
    case 0x400000:                                                        \
        if (pad->stickY >= 0 ? 3.0 < pad->stickY : 3.0 < -pad->stickY) {  \
            value = pad->stickY;                                          \
        } else {                                                          \
            value = 0.0f;                                                 \
        }                                                                 \
        break;                                                            \
    default: {                                                            \
        f32 digital = 0.0f;                                               \
                                                                          \
        if (pad->held & binding) {                                        \
            digital = 80.0f;                                              \
        }                                                                 \
        if (pad->held & (neg)) {                                          \
            digital -= 80.0f;                                             \
        }                                                                 \
        value = digital;                                                  \
        break;                                                            \
    }                                                                     \
    }

void update_unit_control(UnitTask *task, s32 *state) __asm__("func_8009E3A4");

void update_unit_control(UnitTask *task, s32 *state)
{
    PadState empty;
    DriveInput input;
    PadState *pad;
    InputBindings *bindings;
    DriveUnit *unit;
    s32 mode;
    f32 value;
    u32 binding;

    unit = task->unit;
    pad = &empty;
    if (unit->alive == 0) {
        *state = 2;
        return;
    }
    if (task->replay != 0) {
        update_unit_from_pose(task->unit, func_800EC700(task->replayIndex));
    } else if (func_800E3460(unit) != 0) {
        DriveInput *in = &input;

        func_800E30F8(task->unit, in);
        unit = task->unit;
        if (unit->value18 == 1) {
            func_8009A354(unit, in, 1);
        } else if (unit->flags & 4) {
            func_8009BBC0(unit, in);
        } else {
            func_8009A354(unit, in, 0);
        }
    } else {
        bindings = &get_entity_record(task->unit->owner)->bindings;
        mode = get_entity_record(task->unit->owner)->value204;
        if (task->unit->local != 0 && get_entity_record(task->unit->owner)->active != 0) {
            pad = read_player_controller(task->unit->owner);
            if ((pad->held & 0x300) == 0x300 && (pad->pressed & 0x800) && (pad->held & 0x400) &&
                func_80096834(task->unit->owner)) {
                func_8009EDD0(task->unit);
                destroy_unit(task->unit, -1, 0);
                get_entity_record(task->unit->owner)->status |= 4;
                if (*get_game_mode() == 9) {
                    func_800A5B6C(task->unit->owner, -1);
                }
            }
        } else {
            bzero(pad, sizeof(PadState));
        }
        if (D_80134E68 != 0) {
            input.fire = (pad->held & 0x2000) || (pad->held & bindings->special) || (pad->held & bindings->alt);
            input.firePressed = (pad->pressed & 0x2000) || (pad->pressed & bindings->special) ||
                                (pad->pressed & bindings->alt);
        } else {
            input.fire = (pad->held & bindings->fire) != 0;
            input.firePressed = (pad->pressed & bindings->fire) != 0;
        }
        input.special = (pad->held & bindings->special) != 0;
        input.specialPressed = (pad->pressed & bindings->special) != 0;
        if (task->unit->flags & 4) {
            READ_AXIS(bindings->axis30, bindings->axis30Neg);
            input.move = value;
            READ_AXIS(bindings->axis38, bindings->axis38Neg);
            input.aim = -value / 80.0f;
            input.boost = (pad->held & bindings->boost) != 0;
            func_8009BBC0(task->unit, &input);
        } else {
            READ_AXIS(bindings->axis20, bindings->axis20Neg);
            input.turn = value;
            READ_AXIS(bindings->axis28, bindings->axis28Neg);
            input.move = value;
            READ_AXIS(bindings->axis18, bindings->axis18Neg);
            input.aim = -value;
            input.brake = (pad->held & bindings->brake) != 0;
            func_8009A354(task->unit, &input, mode);
        }
    }
    if (task->unit->alive == 0) {
        *state = 2;
    }
}
