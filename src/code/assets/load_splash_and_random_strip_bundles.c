#include "types.h"

extern void rom_dma_read(u8 *romAddress, u8 *destination, s32 size) __asm__("func_80077930");
extern void load_strip_bundle(s32 index) __asm__("func_800CA8C0");
extern u32 func_800F38F4(void);
extern s32 lzari_decode(u32 sourceSize, u8 *source, u32 destinationSize, u8 *destination) __asm__("func_800F4F60");
extern void load_texture_draw_font(u8 font) __asm__("func_801053B0");
extern s32 gRandomStripBundles[4] __asm__("D_80134010");
extern u32 gRandomStripBundleRange __asm__("D_80134AA8");
extern s32 gControllerSlotCount __asm__("D_80134E58");
extern u8 D_80135773;
extern u8 *gResourceTarget __asm__("D_803275F4");
extern s32 D_80327F00;
extern s32 D_80327F04;
extern s32 D_80327F08;
extern s32 D_80327F0C;
extern s32 D_80327F10;
extern s32 D_80327F14;
extern s32 D_80327F18;
extern s32 D_80327F1C;
extern s8 D_80327F20;
extern s8 D_80327F21;
extern s8 D_80327F22;
extern s8 D_80327F23;
extern u8 gStripBundleLoaded[] __asm__("D_80327F30");
extern s32 D_80327F3C;
extern u8 gSplashCompressed[] __asm__("D_803DA800");
extern u8 D_B03DC430[];
extern u8 D_B03DFD10[];

void load_splash_and_random_strip_bundles(void) __asm__("func_800C8218");

void load_splash_and_random_strip_bundles(void)
{
    /* The retail code tests a register that is never assigned on entry. */
    s32 flag;
    s32 i;
    s32 size;
    u32 value;
    u8 *p;

    if (flag) {
        gRandomStripBundleRange = 10;
    } else {
        gRandomStripBundleRange = 9;
    }
    for (i = gControllerSlotCount; i < 4; i++) {
        value = func_800F38F4() % gRandomStripBundleRange;
        gRandomStripBundles[i] = value;
        if (D_80135773 == 0) {
            if ((s32)value > 0) {
                gRandomStripBundles[i] = value + 1;
            }
        }
    }
    size = D_B03DFD10 - D_B03DC430;
    rom_dma_read(D_B03DC430, gSplashCompressed, size);
    lzari_decode(size, gSplashCompressed, 0x25800, gResourceTarget);
    for (i = 9, p = &gStripBundleLoaded[9]; i >= 0; i--) {
        *p-- = 0;
    }
    for (i = 0; i < 4; i++) {
        load_strip_bundle(gRandomStripBundles[i]);
    }
    load_texture_draw_font(1);
    D_80327F3C = -2;
    D_80327F00 = D_80327F04 = D_80327F08 = D_80327F0C = 0xFF;
    D_80327F20 = D_80327F21 = D_80327F22 = D_80327F23 = 0;
    D_80327F10 = D_80327F14 = D_80327F18 = D_80327F1C = -15;
}
