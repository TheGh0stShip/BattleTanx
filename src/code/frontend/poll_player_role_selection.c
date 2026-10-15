#include "types.h"

extern s16 read_player_menu_directions(s32 player, s32 ignoreCButtons) __asm__("func_80096920");
extern s32 func_800D9024(void);
extern s32 D_80327614;
extern s32 gControllerSlotCount __asm__("D_80134E58");
extern s32 D_803283C4;
extern s32 D_803283C8[];
extern s32 D_803283D8[];
extern s32 D_803283E8;
extern s32 D_803283F0[];
extern s32 gMenuOptions[4] __asm__("D_80328400");
extern s32 D_801262C0[];

s32 poll_player_role_selection(void) __asm__("func_800D8C20");

s32 poll_player_role_selection(void) {
    s16 buttons;
    s32 player;
    s32 target;
    s32 delta;

    buttons = read_player_menu_directions(0, 0);
    D_80327614 ^= buttons & 0x80;
    if (D_80327614 != 0) {
        return 0;
    }
    for (player = 0; player < gControllerSlotCount; player++) {
        if (player != 0) {
            buttons = read_player_menu_directions(player, 0);
        }
        if (buttons & 0x10) {
            D_803283C8[player] = D_803283C8[player] == 0;
        }
        if (player == 0 && (buttons & 0x20)) {
            return 2;
        }
        if (D_803283C8[player] != 0) {
            continue;
        }
        if (player == 0) {
            if (buttons & 0x100) {
                D_803283E8--;
            }
            if (buttons & 0x200) {
                D_803283E8++;
            }
            if (D_803283E8 < -2) {
                D_803283E8 = 3;
            }
            if (D_803283E8 == -1) {
                D_803283E8 = gControllerSlotCount;
            }
            if (D_803283E8 < gControllerSlotCount || D_803283E8 == 4) {
                D_803283E8 = -2;
            }
        }
        target = player;
        if ((D_803283E8 != -2) & (player == 0)) {
            target = D_803283E8;
        }
        if (D_803283D8[target] != 2) {
            if (buttons & 1) {
                D_803283F0[target]--;
            }
            if (buttons & 8) {
                D_803283F0[target]++;
            }
            D_803283F0[target] &= 1;
        }
        delta = (buttons & 2) > 0;
        delta -= (buttons & 4) > 0;
        if (delta == 0) {
            continue;
        }
        if (D_803283F0[target] == 0) {
            if (target < gControllerSlotCount) {
                D_801262C0[target] += delta;
                if (D_801262C0[target] >= 3) {
                    D_801262C0[target] = 0;
                }
                if (D_801262C0[target] < 0) {
                    D_801262C0[target] = 2;
                }
            } else if (D_803283D8[target] == 2) {
                D_803283D8[target] = 1;
                gMenuOptions[target] = 0;
                D_801262C0[target] = 3;
                D_803283C4++;
            } else if (D_803283C4 >= 3) {
                delta = gMenuOptions[target];
                gMenuOptions[target] = 4;
                if (func_800D9024() >= 2) {
                    D_803283D8[target] = 2;
                    D_801262C0[target] = 4;
                    D_803283C4--;
                } else {
                    gMenuOptions[target] = delta;
                }
            }
        } else {
            do {
                gMenuOptions[target] = (gMenuOptions[target] + delta) & 3;
            } while (func_800D9024() == 1);
        }
    }
    delta = 0;
    for (player = 0; player < gControllerSlotCount; player++) {
        delta += D_803283C8[player] != 0;
    }
    return delta == gControllerSlotCount;
}
