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

PlayerInput *read_player_controller_raw(s32 player) __asm__("func_8009686C");

/* Same as read_player_controller but without mirroring the C buttons onto the D-pad. */
PlayerInput *read_player_controller_raw(s32 player)
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
