#include "resource_bundle_common.h"

extern u8 gBundle3DC430Start[] __asm__("D_B03DC430");
extern u8 gBundle3DC430End[] __asm__("D_B03DFD10");
extern u32 next_random_u32(void) __asm__("func_800F38F4");
extern void load_strip_bundle(u32 value) __asm__("func_800CA8C0");
extern void set_frontend_state(s32 state) __asm__("func_801053B0");
extern u8 D_80135773;
extern u32 D_80134AA8;
extern s32 D_80134E58;
extern u32 D_80134010[4];
extern s8 D_80327F30[10];
extern s32 D_80327F3C;
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

void load_resource_bundle_3dc430(void) __asm__("func_800C8210");

void load_resource_bundle_3dc430(void)
{
    s32 i;
    u32 size;
    u32 pick;
    s8 *clear;

    if (D_80135773 != 0) {
        D_80134AA8 = 10;
    } else {
        D_80134AA8 = 9;
    }
    for (i = D_80134E58; i < 4; i++) {
        pick = next_random_u32() % D_80134AA8;
        D_80134010[i] = pick;
        if (D_80135773 == 0) {
            if ((s32)pick > 0) {
                D_80134010[i] = pick + 1;
            }
        }
    }
    size = gBundle3DC430End - gBundle3DC430Start;
    rom_dma_read((u32)gBundle3DC430Start, gResourceScratch, size);
    lzari_decode(size, gResourceScratch, RESOURCE_BUNDLE_CAPACITY, gResourceTarget);
    clear = &D_80327F30[9];
    for (i = 9; i >= 0; i--) {
        *clear-- = 0;
    }
    for (i = 0; i < 4; i++) {
        load_strip_bundle(D_80134010[i]);
    }
    set_frontend_state(1);
    D_80327F3C = -2;
    D_80327F0C = 0xFF;
    D_80327F08 = 0xFF;
    D_80327F04 = 0xFF;
    D_80327F00 = 0xFF;
    D_80327F23 = 0;
    D_80327F22 = 0;
    D_80327F21 = 0;
    D_80327F20 = 0;
    D_80327F1C = -15;
    D_80327F18 = -15;
    D_80327F14 = -15;
    D_80327F10 = -15;
}
