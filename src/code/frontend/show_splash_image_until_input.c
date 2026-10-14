#include "types.h"

extern void rom_dma_read(u8 *romAddress, u8 *destination, s32 size) __asm__("func_80077930");
extern void func_8007968C(void);
extern void func_8007D850(void);
extern void func_8007D998(void);
extern void func_8007EEF8(s32, s32);
extern void func_800A8ECC(void);
extern void func_800A8EE0(void);
extern void func_800D455C(s32);
extern u8 func_800D64CC(void);
extern s32 lzari_decode(u32 sourceSize, u8 *source, u32 destinationSize, u8 *destination) __asm__("func_800F4F60");
extern u8 *D_803275F4;
extern s32 D_803276D0;
extern u32 *gFrameDisplayList __asm__("D_803276D4");
extern s32 D_803276D8;
extern s32 D_80328290;
extern s32 D_80328294;
extern s32 D_80328298;
extern s32 D_8032829C;
extern u8 gSplashCompressed[] __asm__("D_803DA800");
extern u8 gSplashSource[] __asm__("D_803DA800");
extern u8 D_B04AD7E0[];
extern u8 D_B04B1300[];

s32 show_splash_image_until_input(void) __asm__("func_800D6060");

static inline void render_splash_frame(void) {
    s32 next;
    s32 mask;
    s32 dl;
    s32 base;
    u32 *cmd;

    func_8007D850();
    gFrameDisplayList = (u32 *)(D_803276D0 + D_803276D8 * 0x11000);
    func_800D455C(D_803276D8);
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

s32 show_splash_image_until_input(void) {
    s32 size = D_B04B1300 - D_B04AD7E0;
    u8 done;
    s32 i;

    rom_dma_read(D_B04AD7E0, gSplashCompressed, size);
    lzari_decode(size, gSplashSource, 0x25800, D_803275F4);
    D_8032829C = 10;
    D_80328298 = 10;
    D_80328294 = 10;
    D_80328290 = 10;
    do {
        func_800A8ECC();
        func_800A8EE0();
        done = func_800D64CC();
        render_splash_frame();
    } while (!done);
    for (i = 0; i < 3; i++) {
        render_splash_frame();
    }
    return 5;
}
