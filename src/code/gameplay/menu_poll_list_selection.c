#include "types.h"

extern s32 func_80096920(s32, s32);
extern void set_sound_38_value_25088(void) __asm__("func_800ABF70");
extern u8 D_801352B0[];
extern s32 D_8013566C;
extern s32 D_80135674;
extern s32 D_80327614;
extern s32 D_80328410;

s32 menu_poll_list_selection(void) __asm__("func_800DAC4C");

s32 menu_poll_list_selection(void)
{
    s32 buttons;
    s32 result;
    s32 delta;
    s32 index;

    buttons = func_80096920(0, 0);
    D_80327614 ^= buttons & 0x80;
    if (D_80327614 != 0) {
        return 0;
    }
    result = 0;
    delta = 0;
    if (buttons & 2) {
        delta = -1;
        set_sound_38_value_25088();
    }
    if (buttons & 4) {
        delta++;
        set_sound_38_value_25088();
    }
    index = D_8013566C += delta;
    if (index < 0) {
        index = D_80328410 - 1;
    }
    D_8013566C = index;
    if (index >= D_80328410) {
        index = 0;
    }
    D_8013566C = index;
    if (buttons & 0x50) {
        result = 1;
        D_80135674 = D_801352B0[index];
    }
    if (buttons & 0x20) {
        result = 2;
    }
    return result;
}
