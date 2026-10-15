#include "types.h"

typedef struct RomSpan16 {
    u8 *start;
    u8 *end;
    u8 pad08[8];
} RomSpan16;

typedef struct RomSpan28 {
    u8 *start;
    u8 *end;
    u8 pad08[0x20];
} RomSpan28;

extern s32 *get_game_mode(void) __asm__("func_8007AAF4");
extern s32 game_mode_is_3_through_6(void) __asm__("func_8007C6D8");
extern void rom_dma_read(u8 *romAddress, u8 *destination, u32 size) __asm__("func_80077930");
extern void func_800F45C8(void);
extern u8 D_8037FD78;
extern u8 D_8037A170;
extern s32 D_8037A160;
extern s32 D_8037A164;
extern s32 D_8037A168;
extern s32 D_8037A16C;
extern s32 D_80134E58;
extern s32 D_801427C8[];
extern s32 D_80142894[];
extern s32 D_801416F8[];
extern s32 D_80141560[];
extern RomSpan16 D_80141768[];
extern RomSpan28 D_80141308[];
extern u8 D_8037FD80[];
extern u8 D_8037AD78[];
extern u8 D_80382D80[];
extern u8 D_8037A178[];
extern u8 D_B0308290[];
extern u8 D_B030BFE0[];
extern u8 D_B03102D0[];
extern u8 D_B0312D90[];
extern u8 D_B0316C60[];
extern u8 D_B0319B30[];

void load_level_support_assets(void) __asm__("func_800F5960");

void load_level_support_assets(void) {
    s32 *mode = get_game_mode();
    u8 *start;
    u8 *end;
    u32 size;
    s32 index;
    s32 slot;

    D_8037FD78 = 0;
    D_8037A170 = 0x80;
    D_8037A160 = mode[1];
    func_800F45C8();
    if (game_mode_is_3_through_6()) {
        D_8037A168 = D_801427C8[mode[2]];
        D_8037A16C = D_80142894[mode[2]];
    }
    size = D_B0319B30 - D_B0316C60;
    if (size > 0x3000) {
        return;
    }
    rom_dma_read(D_B0316C60, D_8037FD80, size);
    if (D_80134E58 > 0) {
        if (D_80134E58 < 3) {
            end = D_B030BFE0;
            start = D_B0308290;
        } else if (D_80134E58 < 5) {
            end = D_B0312D90;
            start = D_B03102D0;
        } else {
            goto skip;
        }
        size = end - start;
        if (size > 0x5000) {
            return;
        }
        rom_dma_read(start, D_8037AD78, size);
    }
skip:
    index = D_801416F8[D_8037A160];
    D_8037A164 = -1;
    if (index != -1) {
        D_8037A164 = index;
        size = D_80141768[index].end - D_80141768[index].start;
        if (size > 0x5000) {
            return;
        }
        if (size != 0) {
            rom_dma_read(D_80141768[index].start, D_80382D80, size);
        }
    }
    slot = D_80141560[D_8037A160];
    if (slot != 0) {
        size = D_80141308[slot].end - D_80141308[slot].start;
        if (size > 0xC00) {
            return;
        }
        if (size != 0) {
            rom_dma_read(D_80141308[slot].start, D_8037A178, size);
        }
    }
}
