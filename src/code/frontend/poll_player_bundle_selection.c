#include "types.h"

extern s32 read_player_menu_directions(s32 player, s32 ignoreCButtons) __asm__("func_80096920");
extern void load_strip_bundle(s32 index) __asm__("func_800CA8C0");
extern s32 D_80327614;
extern s32 gControllerSlotCount __asm__("D_80134E58");
extern u8 D_80327F20[];
extern s32 D_80327F3C;
extern s32 gMenuOptions[4] __asm__("D_80328400");
extern s32 D_80327F10[];
extern s32 D_80134010[];
extern u8 D_80135773;

s32 poll_player_bundle_selection(void) __asm__("func_800CA5BC");

s32 poll_player_bundle_selection(void) {
    s32 buttons;
    s32 player;
    s32 target;
    s32 delta;
    s32 value;
    s32 raw;
    u8 flag;

    buttons = read_player_menu_directions(0, 0);
    D_80327614 ^= buttons & 0x80;
    if (D_80327614 != 0) {
        return 0;
    }
    for (player = 0; player < gControllerSlotCount; player++) {
        if (player != 0) {
            buttons = read_player_menu_directions(player, 0);
        }
        delta = 0;
        if (D_80327F20[player] == 0) {
            if (player == 0) {
                do {
                    if (buttons & 0x100) {
                        D_80327F3C--;
                    }
                    if (buttons & 0x200) {
                        D_80327F3C++;
                    }
                    if (D_80327F3C < -2) {
                        D_80327F3C = 3;
                    }
                    if (D_80327F3C == -1) {
                        D_80327F3C = gControllerSlotCount;
                    }
                    if (D_80327F3C < gControllerSlotCount || D_80327F3C == 4) {
                        D_80327F3C = -2;
                    }
                } while (D_80327F3C != -2 && gMenuOptions[D_80327F3C] == 4);
            }
            target = player;
            if ((D_80327F3C != -2) & (player == 0)) {
                target = D_80327F3C;
            }
            if (buttons & 1) {
                D_80327F10[target] = -D_80327F10[target];
            }
            if (buttons & 8) {
                D_80327F10[target] = -D_80327F10[target];
            }
            delta -= (buttons & 2) > 0;
            delta += (buttons & 4) > 0;
            flag = D_80135773;
            D_80134010[target] += delta;
            if (flag == 0) {
                if (D_80134010[target] == 1) {
                    D_80134010[target] = delta + 1;
                }
            }
            value = D_80134010[target];
            if (value < 0) {
                value = 9;
            }
            raw = value & -(value < 10);
            D_80134010[target] = raw;
            load_strip_bundle(raw);
        }
        if (buttons & 0x10) {
            D_80327F20[player] ^= 1;
        }
        if (player == 0 && (buttons & 0x20)) {
            return 2;
        }
    }
    for (player = 0; player < gControllerSlotCount; player++) {
        if (D_80327F20[player] == 0) {
            return 0;
        }
    }
    return 1;
}
