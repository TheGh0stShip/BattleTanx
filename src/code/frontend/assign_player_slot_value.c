#include "types.h"

extern u32 D_803282A8[][17];
extern u8 D_803283B8[];
extern s32 D_80135034[];

static inline u8 find_slot(s32 player, s32 n) {
    u8 i;

    for (i = 0; i < 17; i++) {
        if (D_803282A8[player][i] <= 0xFFFFF) {
            if (--n == -1) {
                break;
            }
        }
    }
    return i;
}

void assign_player_slot_value(s32 player, s32 n, u32 value) __asm__("func_800D6274");

void assign_player_slot_value(s32 player, s32 n, u32 value) {
    s32 ok = 1;
    u8 slot = find_slot(player, n);
    s32 other = -1;
    u32 old = D_803282A8[player][slot];
    s32 i;

    for (i = 0; i < D_80135034[D_803283B8[player]]; i++) {
        if (D_803282A8[player][find_slot(player, i)] == value) {
            other = find_slot(player, i);
            break;
        }
    }
    if (other == -1) {
        for (i = 0; i < 17; i++) {
            if (D_803282A8[player][i] == value) {
                ok = 0;
                break;
            }
        }
    }
    if (ok) {
        D_803282A8[player][slot] = value;
        if (other >= 0) {
            D_803282A8[player][other] = old;
        }
        if (slot == 10) {
            D_803282A8[player][12] = value;
        }
        if (slot == 11) {
            D_803282A8[player][13] = value;
        }
    }
}
