#include "types.h"

extern s32 func_80096920(s32, s32);
extern void func_800A90E0(void);
extern void find_sound_38(void) __asm__("func_800ABF1C");
extern void set_sound_38_value_19114(void) __asm__("func_800ABF40");
extern void set_sound_38_value_25088(void) __asm__("func_800ABF70");
extern s32 gControllerCount __asm__("D_80126714");
extern s32 D_80134E54;
extern s32 D_80134E58;
extern s32 D_80134E5C;
extern u8 D_80134E74;
extern s32 D_80327614;

s32 update_game_setup_menu_input(void) __asm__("func_800CC1A8");

s32 update_game_setup_menu_input(void)
{
    s32 buttons;
    s32 delta;
    s32 item;

    buttons = func_80096920(0, 0);
    D_80327614 ^= buttons & 0x80;
    if (D_80327614 != 0) {
        return 0;
    }
    delta = 0;
    if (buttons & 1) {
        delta = -1;
        set_sound_38_value_19114();
    }
    if (buttons & 8) {
        delta++;
        set_sound_38_value_19114();
    }
    D_80134E54 += delta;
    if ((D_80134E74 == 0 || D_80134E5C != 0) && D_80134E54 == 5) {
        D_80134E54 = delta + 5;
    }
    if (D_80134E54 < 0) {
        D_80134E54 = 6;
    }
    if (D_80134E54 >= 7) {
        D_80134E54 = 0;
    }
    delta = 0;
    if (buttons & 2) {
        delta--;
    }
    if (buttons & 4) {
        delta++;
    }
    item = D_80134E54;
    switch (item) {
    case 0:
        if (delta != 0) {
            set_sound_38_value_25088();
            D_80134E58 += delta;
            func_800A90E0();
            if (D_80134E58 <= 0) {
                D_80134E58 = gControllerCount;
            }
            if (D_80134E58 > gControllerCount) {
                D_80134E58 = 1;
            }
            if (D_80134E58 >= 2) {
                D_80134E5C = (D_80134E5C <= 0) ? 1 : D_80134E5C;
            }
        }
        break;
    case 1:
        if (delta != 0) {
            set_sound_38_value_25088();
        }
        if (D_80134E58 >= 2) {
            D_80134E5C += delta;
            if (D_80134E5C >= 5) {
                D_80134E5C = item;
            }
            if (D_80134E5C <= 0) {
                D_80134E5C = 4;
            }
        } else {
            D_80134E5C += delta;
            if (D_80134E5C >= 5) {
                D_80134E5C = 0;
            }
            if (D_80134E5C < 0) {
                D_80134E5C = 4;
            }
        }
        break;
    }
    if (buttons & 0x40) {
        D_80134E54 = 6;
        find_sound_38();
        return 1;
    }
    if (D_80134E54 >= 2) {
        delta = buttons & 0x10;
        if (delta) {
            find_sound_38();
        }
        return delta;
    }
    return 0;
}
