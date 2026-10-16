#include "types.h"

extern void rom_dma_read(u8 *romAddress, u8 *destination, s32 size) __asm__("func_80077930");
extern void func_8007968C(void);
extern void func_8007D850(void);
extern void func_8007D998(void);
extern void func_8007EEF8(s32, s32);
extern void func_800A8ECC(void);
extern void func_800A8EE0(void);
extern void draw_options_screen(s32) __asm__("func_800CC4E4");
extern u8 func_800CE214(void);
extern s32 lzari_decode(u32 sourceSize, u8 *source, u32 destinationSize, u8 *destination) __asm__("func_800F4F60");
extern void load_texture_draw_font(s32 font) __asm__("func_801053B0");
extern u8 *D_803275F4;
extern s32 D_803276D0;
extern u32 *gFrameDisplayList __asm__("D_803276D4");
extern s32 D_803276D8;
extern u8 gChoiceCompressed[] __asm__("D_803DA800");
extern u8 gChoiceSource[] __asm__("D_803DA800");
extern u8 D_B04B39B0[];
extern u8 D_B04B4B00[];

s32 run_compressed_choice_screen(void) __asm__("func_800CDFFC");

static inline void render_choice_frame(void) {
    s32 next;
    s32 mask;
    s32 dl;
    s32 base;
    u32 *cmd;

    func_8007D850();
    gFrameDisplayList = (u32 *)(D_803276D0 + D_803276D8 * 0x11000);
    draw_options_screen(D_803276D8);
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

s32 run_compressed_choice_screen(void) {
    s32 size = D_B04B4B00 - D_B04B39B0;
    u8 choice;
    s32 i;

    rom_dma_read(D_B04B39B0, gChoiceCompressed, size);
    lzari_decode(size, gChoiceSource, 0x25800, D_803275F4);
    load_texture_draw_font(1);
    do {
        func_800A8ECC();
        func_800A8EE0();
        choice = func_800CE214();
        render_choice_frame();
    } while (!choice);
    for (i = 0; i < 3; i++) {
        render_choice_frame();
    }
    return (-(choice == 2) & 6) | 2;
}
