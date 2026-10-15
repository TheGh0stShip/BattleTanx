#include "types.h"

typedef struct SessionRecord {
    u32 words[17];
} SessionRecord;

typedef struct SessionState {
    u8 pad00[0x8];
    u8 value08;
    u8 pad09[0xD];
    u8 value16;
    u8 pad17[0x2];
    u8 value19;
    u8 pad1A[0xA];
    SessionRecord record;
} SessionState;

extern void rom_dma_read(u8 *romAddress, u8 *destination, s32 size) __asm__("func_80077930");
extern void load_texture_draw_font(s32 font) __asm__("func_801053B0");
extern void func_80079BB4(s32 arg0);
extern void func_80079BF4(s32 arg0);
extern void func_8007968C(void);
extern void func_8007D850(void);
extern void func_8007D998(void);
extern void func_8007EEF8(s32, s32);
extern void func_800A8ECC(void);
extern void func_800A8EE0(void);
extern void func_800CAA04(void);
extern u8 update_game_setup_menu_input(void) __asm__("func_800CC1A8");
extern void func_800D05DC(void);
extern s32 func_800D0994(void);
extern void func_800DAD60(void);
extern void func_800EC380(s32);
extern void func_8010527C(void);
extern s32 D_80125794;
extern u8 D_8012579A;
extern u8 D_8012579D;
extern s32 D_80134E54;
extern s32 D_80134E5C;
extern u8 D_80134E64;
extern u8 D_80134E75;
extern SessionState *D_80134E78;
extern u8 D_80135767;
extern u8 D_80135768;
extern u8 D_80135769;
extern u8 D_8013576F;
extern u8 D_80135774;
extern u8 *D_803275F4;
extern s32 D_803276D0;
extern u32 *gFrameDisplayList __asm__("D_803276D4");
extern s32 D_803276D8;
extern s32 D_80327B4C;
extern s32 D_80327F40;
extern u8 D_80327F44;
extern SessionRecord D_803282A8[];
extern u8 D_803283B8[];
extern u8 D_B049C740[];
extern u8 D_B049DCD0[];

static inline void draw_setup_frame(void)
{
    s32 dl;
    s32 base;
    u32 *cmd;
    s32 next;
    s32 mask;

    func_8007D850();
    gFrameDisplayList = (u32 *)(D_803276D0 + D_803276D8 * 0x11000);
    func_800CAA04();
    cmd = gFrameDisplayList;
    dl = D_803276D0 + D_803276D8 * 0x11000;
    base = D_803276D0;
    gFrameDisplayList = cmd + 2;
    cmd[0] = 0xB8000000;
    cmd[1] = 0;
    func_8007EEF8(dl, base);
    next = D_803276D8 + 1;
    mask = -(next < 3);
    D_803276D8 = next & mask;
    func_8007968C();
    func_8007D998();
}

s32 run_game_setup_screen(void) __asm__("func_800CBDBC");

s32 run_game_setup_screen(void)
{
    s32 result = 2;
    u32 size;
    u8 input;
    s32 i;

    size = D_B049DCD0 - D_B049C740;
    if (size <= 0x3A980) {
        rom_dma_read(D_B049C740, D_803275F4, size);
        load_texture_draw_font(1);
        D_80327F40 = 0;
        D_80327F44 = 1;
        func_80079BB4(6);
        func_80079BF4((D_80125794 << 28) >> 16);
    }
    do {
        func_800A8ECC();
        func_800A8EE0();
        input = update_game_setup_menu_input();
        draw_setup_frame();
    } while (!input && result);
    for (i = 0; i < 3; i++) {
        draw_setup_frame();
    }
    switch (D_80134E54) {
    case 2:
        result = 5;
        break;
    case 4:
        result = 9;
        func_800DAD60();
        break;
    case 5:
        if (func_800D0994() == 0) {
            result = 0xB;
            if (D_8012579D != 0) {
                break;
            }
            D_803283B8[0] = D_80134E78->value19;
            D_803282A8[0] = D_80134E78->record;
            goto saved;
        } else {
            D_80134E75 = 2;
            result = 0xA;
        }
        break;
    case 6:
        if (D_80134E5C == 4) {
            return 7;
        }
        result = 7;
        if (D_80134E5C != 0) {
            break;
        }
        result = 3;
        if (D_8012579A != 0) {
            break;
        }
        if (D_80135774 == 0) {
            func_800D05DC();
        } else {
            D_80134E64 = D_80134E78->value16;
        }
        D_80135774 = 0;
        result = 8;
        if (D_80135767 != 0) {
            break;
        }
        if (D_80135769 != 0xFF) {
            D_80134E78->value08 = D_80135769;
        }
        if (D_80135768 != 0) {
        saved:
            result = 0xB;
            break;
        }
        result = 0xC;
        if (D_8013576F != 0) {
            result = 0x13;
        }
        break;
    case 3:
        func_800EC380(0xB);
        func_8010527C();
        result = 0xD;
        D_80327B4C = 2;
        break;
    }
    return result;
}
