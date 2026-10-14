#include "types.h"

typedef struct ControllerPad {
    u16 buttons;
    s8 stickX;
    s8 stickY;
    u8 errorNo;
    u8 pad05;
} ControllerPad;

typedef struct PlayerInput {
    s8 stickX;
    s8 stickY;
    u8 pad02[0x2];
    u32 held;
    u32 pressed;
    u32 released;
} PlayerInput;

typedef struct MenuRepeatState {
    u32 upTick;
    u32 leftTick;
    u32 rightTick;
    u32 downTick;
    s8 lastStickX;
    s8 lastStickY;
    u8 pad12[0x2];
} MenuRepeatState;

#define MENU_STICK_DEADZONE 40
#define MENU_REPEAT_DELAY 20

extern s32 D_802E17A8[];
extern ControllerPad D_802E17B8[];
extern ControllerPad D_802E17D8[];
extern PlayerInput D_802D8140;
extern MenuRepeatState D_80125E60[];
extern u32 D_80125EB0;

s32 read_player_menu_directions(s32 player, s32 ignoreCButtons) __asm__("func_80096920");

static inline PlayerInput *read_raw_input(s32 player)
{
    ControllerPad *current;
    ControllerPad *previous;
    s32 channel;

    channel = D_802E17A8[player];
    current = &D_802E17D8[channel];
    D_802D8140.held = current->buttons;
    previous = &D_802E17B8[channel];
    D_802D8140.pressed = current->buttons & ~previous->buttons;
    D_802D8140.released = previous->buttons & ~current->buttons;
    D_802D8140.stickX = current->stickX;
    D_802D8140.stickY = current->stickY;
    return &D_802D8140;
}

/* Folds stick, D-pad and C buttons into menu direction/action bits with auto-repeat. */
s32 read_player_menu_directions(s32 player, s32 ignoreCButtons)
{
    PlayerInput *input = read_raw_input(player);
    u32 held = input->held;
    u32 pressed = input->pressed;
    s32 out = 0;
    s32 magnitude;

    if (ignoreCButtons != 0) {
        pressed &= ~0xF;
        held &= ~0xF;
    }

    magnitude = input->stickX;
    if (magnitude < 0) {
        magnitude = -magnitude;
    }
    if (magnitude < MENU_STICK_DEADZONE) {
        input->stickX = 0;
    }
    magnitude = input->stickY;
    if (magnitude < 0) {
        magnitude = -magnitude;
    }
    if (magnitude < MENU_STICK_DEADZONE) {
        input->stickY = 0;
    }

    if (input->stickX < 0) {
        if (D_80125E60[player].lastStickX < 0) {
            held |= 0x202;
        } else {
            pressed |= 0x202;
        }
    }
    if (input->stickX > 0) {
        if (D_80125E60[player].lastStickX > 0) {
            held |= 0x101;
        } else {
            pressed |= 0x101;
        }
    }
    if (input->stickY < 0) {
        if (D_80125E60[player].lastStickY < 0) {
            held |= 0x404;
        } else {
            pressed |= 0x404;
        }
    }
    if (input->stickY > 0) {
        if (D_80125E60[player].lastStickY > 0) {
            held |= 0x808;
        } else {
            pressed |= 0x808;
        }
    }
    D_80125E60[player].lastStickX = input->stickX;
    D_80125E60[player].lastStickY = input->stickY;

    if ((held & 0x808) && (held & 0x404)) {
        held &= ~0xC0C;
    }
    if ((held & 0x202) && (held & 0x101)) {
        held &= ~0x303;
    }

    D_80125EB0++;
    if (pressed & 0x20) {
        out |= 0x100;
    }
    if (pressed & 0x10) {
        out |= 0x200;
    }
    if (pressed & 0x2000) {
        out |= 0x80;
    }
    if (pressed & 0x1000) {
        out |= 0x40;
    }
    if (pressed & 0x8000) {
        out |= 0x10;
    }
    if (pressed & 0x4000) {
        out |= 0x20;
    }

    if ((pressed & 0x808)
        || (D_80125E60[player].upTick + MENU_REPEAT_DELAY < D_80125EB0 && (held & 0x808))) {
        D_80125E60[player].upTick = D_80125EB0;
        out |= 1;
    }
    if ((pressed & 0x404)
        || (D_80125E60[player].downTick + MENU_REPEAT_DELAY < D_80125EB0 && (held & 0x404))) {
        out |= 8;
        D_80125E60[player].downTick = D_80125EB0;
    }
    if ((pressed & 0x101)
        || (D_80125E60[player].rightTick + MENU_REPEAT_DELAY < D_80125EB0 && (held & 0x101))) {
        out |= 4;
        D_80125E60[player].rightTick = D_80125EB0;
    }
    if ((pressed & 0x202)
        || (D_80125E60[player].leftTick + MENU_REPEAT_DELAY < D_80125EB0 && (held & 0x202))) {
        out |= 2;
        D_80125E60[player].leftTick = D_80125EB0;
    }
    return out;
}
