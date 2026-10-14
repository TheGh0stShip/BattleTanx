#include "types.h"

extern u64 osGetTime(void) __asm__("func_801120A0");
extern void load_texture_draw_font(s32 font) __asm__("func_801053B0");
extern void rom_dma_read(u8 *romAddress, u8 *destination, s32 size) __asm__("func_80077930");
extern s32 lzari_decode(u32 sourceSize, u8 *source, u32 destinationSize, u8 *destination) __asm__("func_800F4F60");
extern s32 find_sound_instance(s32 soundId, s32 index) __asm__("func_800796F0");
extern void func_8007968C(void);
extern void func_8007D850(void);
extern void func_8007D998(void);
extern void func_8007EEF8(s32, u32 *);
extern void func_800D0DAC(s32);
extern u64 D_80145DA0;
extern u8 *D_803275F4;
extern s32 D_803276D0;
extern u32 *gFrameDisplayList __asm__("D_803276D4");
extern s32 D_803276D8;
extern u8 D_80328280;
extern u8 gSplashCompressed[] __asm__("D_803DA800");
extern u8 gSplashSource[] __asm__("D_803DA800");
extern u8 D_B04B3280[];
extern u8 D_B04B39B0[];

s32 show_timed_splash_image(void) __asm__("func_800D11B0");

s32 show_timed_splash_image(void) {
    u8 done = 0;
    u64 start;
    s32 size;
    u64 elapsed;
    s32 next;
    s32 mask;
    s32 dl;
    u32 *cmd;

    start = osGetTime();
    load_texture_draw_font(1);
    size = D_B04B39B0 - D_B04B3280;
    rom_dma_read(D_B04B3280, gSplashCompressed, size);
    lzari_decode(size, gSplashSource, 0x25800, D_803275F4);
    D_80328280 = 0;
    find_sound_instance(0x30, 0);
    do {
        func_8007D850();
        gFrameDisplayList = (u32 *)(D_803276D0 + D_803276D8 * 0x11000);
        func_800D0DAC(D_803276D8);
        cmd = gFrameDisplayList;
        dl = D_803276D0 + D_803276D8 * 0x11000;
        gFrameDisplayList = cmd + 2;
        cmd[0] = 0xB8000000;
        cmd[1] = 0;
        func_8007EEF8(dl, cmd);
        next = D_803276D8 + 1;
        mask = -(next < 3);
        D_803276D8 = next & mask;
        func_8007968C();
        func_8007D998();
        elapsed = (osGetTime() - start) * 1000000 / D_80145DA0;
        if (elapsed > 2000000) {
            D_80328280 = 1;
        }
        if (elapsed > 4000000) {
            done = 1;
        }
    } while (!done);
    return 1;
}
