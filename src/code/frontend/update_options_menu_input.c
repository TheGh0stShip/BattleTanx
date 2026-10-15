#include "types.h"

extern s32 func_80096920(s32, s32);
extern void set_audio_control_value(s32 value) __asm__("func_800799C0");
extern void func_80079BF4(s32 arg0);
extern void set_sound_38_value_19114(void) __asm__("func_800ABF40");
extern void set_sound_38_value_25088(void) __asm__("func_800ABF70");
extern s32 D_80125790;
extern s32 D_80125794;
extern s32 D_80134E60;
extern u8 D_80134E64;
extern u8 D_80134E65;
extern u8 D_80134E66;
extern u8 D_80134E67;
extern u8 D_80134E69;
extern s32 D_80327614;

s32 update_options_menu_input(void) __asm__("func_800CE214");

s32 update_options_menu_input(void)
{
    s32 buttons;
    s32 result;
    s32 delta;
    s32 value;

    buttons = func_80096920(0, 0);
    D_80327614 ^= buttons & 0x80;
    if (D_80327614 != 0) {
        return 0;
    }
    result = 0;
    delta = 0;
    if (buttons & 1) {
        delta = -1;
        set_sound_38_value_19114();
    }
    if (buttons & 8) {
        delta++;
        set_sound_38_value_19114();
    }
    D_80134E60 += delta;
    if (D_80134E60 < 0) {
        D_80134E60 = 7;
    }
    if (D_80134E60 >= 8) {
        D_80134E60 = 0;
    }
    delta = 0;
    if (buttons & 2) {
        delta = -1;
        set_sound_38_value_25088();
    }
    if (buttons & 4) {
        delta++;
        set_sound_38_value_25088();
    }
    switch (D_80134E60) {
    case 0:
        D_80125790 += delta;
        D_80125790 = (D_80125790 < 0) ? 0 : D_80125790;
        D_80125790 = (D_80125790 >= 8) ? 7 : D_80125790;
        set_audio_control_value((D_80125790 << 12) & 0xF000);
        break;
    case 1:
        D_80125794 += delta;
        D_80125794 = (D_80125794 < 0) ? 0 : D_80125794;
        D_80125794 = (D_80125794 >= 8) ? 7 : D_80125794;
        func_80079BF4((D_80125794 << 28) >> 16);
        break;
    case 2:
        D_80134E64 += delta;
        if (D_80134E64 == 0xFF) {
            D_80134E64 = 2;
        }
        if (D_80134E64 >= 3) {
            D_80134E64 = 0;
        }
        break;
    case 3:
        D_80134E65 = (D_80134E65 + delta) & 1;
        break;
    case 4:
        D_80134E66 = (D_80134E66 + delta) & 1;
        break;
    case 5:
        D_80134E67 = (D_80134E67 + delta) & 1;
        break;
    case 6:
        D_80134E69 = (D_80134E69 + delta) & 1;
        break;
    case 7:
        if (buttons & 0x54) {
            result = 2;
        }
        break;
    }
    if (buttons & 0x20) {
        result = 1;
    }
    return result;
}
