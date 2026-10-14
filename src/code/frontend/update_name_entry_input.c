#include "types.h"

extern s32 read_player_menu_directions(s32 player, s32 ignoreCButtons) __asm__("func_80096920");
extern void find_sound_38(void) __asm__("func_800ABF1C");
extern void set_sound_38_value_19114(void) __asm__("func_800ABF40");
extern void set_sound_38_value_25088(void) __asm__("func_800ABF70");
extern void confirm_name_entry(void) __asm__("func_800DCA7C");

extern u8 D_80135680[];
extern u8 D_8013568C[];
extern s32 D_80327614;
extern s32 D_80328420;
extern s32 D_80328424;
extern s32 D_80328428;
extern u8 D_8032842F[];
extern u8 D_80328430[];
extern u8 D_80328439;
extern u8 D_8032843A;
extern s32 D_80328440;

s32 update_name_entry_input(void) __asm__("func_800DCCC0");

s32 update_name_entry_input(void) {
    s32 count = 0;
    s32 buttons;
    s32 delta;
    s32 toggle;
    s32 input;
    s32 i;
    u8 *p;

    input = read_player_menu_directions(0, 0);
    toggle = D_80327614 ^ (input & 0x80);
    D_80327614 = toggle;
    buttons = input;
    if (toggle != 0) {
        return 0;
    }
    switch (D_80328424) {
    case 1:
        count = 10;
        break;
    case 2:
        count = 2;
        break;
    case 0:
        count = 11;
        break;
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
    D_80328424 += delta;
    if (D_80328424 < 0) {
        D_80328424 = 2;
    }
    if (D_80328424 >= 3) {
        D_80328424 = 0;
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
    D_80328420 += delta;
    if (D_80328420 < 0) {
        D_80328420 = count - 1;
    }
    if (D_80328420 >= count) {
        D_80328420 = 0;
    }
    if (buttons & 0x50) {
        find_sound_38();
        switch (D_80328424) {
        case 2:
            if (D_80328420 == 0) {
                if (D_80328428 > 0) {
                    D_8032842F[D_80328428] = ' ';
                    D_80328428--;
                }
                D_80328440 = -1;
            } else {
                confirm_name_entry();
            }
            break;
        case 1:
            if (D_8032843A != 0) {
                i = 9;
                p = &D_80328439;
                D_8032843A = 0;
                D_80328428 = 0;
                do {
                    *p = ' ';
                    i--;
                    p--;
                } while (i >= 0);
            }
            if (D_80328428 < 10) {
                D_80328430[D_80328428++] = D_8013568C[D_80328420];
            }
            break;
        case 0:
            if (D_8032843A != 0) {
                i = 9;
                p = &D_80328439;
                D_8032843A = 0;
                D_80328428 = 0;
                do {
                    *p = ' ';
                    i--;
                    p--;
                } while (i >= 0);
            }
            if (D_80328428 < 10) {
                D_80328430[D_80328428++] = D_80135680[D_80328420];
            }
            break;
        }
    }
    return buttons & 0x20;
}
