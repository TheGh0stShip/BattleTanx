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

extern s32 D_802E17A8[];
extern ControllerPad D_802E17B8[];
extern ControllerPad D_802E17D8[];
extern PlayerInput D_802D8140;

/* Mirrors the C buttons (low nibble) onto the D-pad (bits 8-11) and back. */
#define MERGE_DPAD_AND_C(b) ((b) | (((b) & 0xF00) >> 8) | (((b) & 0xF) << 8))

PlayerInput *read_player_controller(s32 player) __asm__("func_80096784");

PlayerInput *read_player_controller(s32 player)
{
    ControllerPad *current;
    u32 held;
    u32 previous;
    s32 channel;
    u16 buttons;
    u16 lastButtons;

    channel = D_802E17A8[player];
    current = &D_802E17D8[channel];
    buttons = current->buttons;
    lastButtons = D_802E17B8[channel].buttons;
    held = MERGE_DPAD_AND_C(buttons);
    previous = MERGE_DPAD_AND_C(lastButtons);
    D_802D8140.held = held;
    D_802D8140.pressed = held & ~previous;
    D_802D8140.released = previous & ~held;
    D_802D8140.stickX = current->stickX;
    D_802D8140.stickY = current->stickY;
    return &D_802D8140;
}
