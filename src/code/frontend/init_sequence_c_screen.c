#include "types.h"

extern u64 osClockRate __asm__("D_80145DA0");
extern u64 osGetTime(void) __asm__("func_801120A0");
extern void rom_dma_read(u8 *romAddress, u8 *destination, s32 size) __asm__("func_80077930");
extern s32 lzari_decode(u32 sourceSize, u8 *source, u32 destinationSize, u8 *destination) __asm__("func_800F4F60");
extern void func_801053B0(s32);
extern s32 func_800C3EA4(s32, s32);
extern u8 *D_803275F4;
extern u8 D_80132EF0;
extern u8 D_80327D40;
extern u8 D_80327D68;
extern u64 D_80327D70;
extern s32 D_80327D78;
extern u64 D_80327D80;
extern u64 D_80327D88;
extern s32 D_80327D90;
extern u64 D_80327DF0;
extern u64 D_80327DF8;
extern u64 D_80327E00;
extern u64 D_80327E08;
extern s32 D_80327E10;
extern u8 D_80327E14;
extern u8 D_80327E15;
extern u8 D_80327E16;
extern u8 D_80327E17;
extern u8 D_80327E18;
extern u8 D_80327E19;
extern u8 D_80327E30;
extern u8 D_80327E31;
extern s32 D_80327E40;
extern u8 gScreenCompressed[] __asm__("D_803DA800");
extern u8 D_B056FDB0[];
extern u8 D_B058AE00[];
extern u8 D_B0596EA0[];

#define TIME_USEC() (osGetTime() * 1000000 / osClockRate)

void init_sequence_c_screen(void) __asm__("func_800C0898");

void init_sequence_c_screen(void) {
    u8 *start;
    register u8 *end __asm__("$2");
    s32 size;

    if (D_80327D40 >= 5) {
        end = D_B0596EA0;
        start = D_B058AE00;
        size = end - start;
    } else {
        end = D_B058AE00;
        start = D_B056FDB0;
        size = end - start;
    }
    rom_dma_read(start, gScreenCompressed, size);
    lzari_decode(size, gScreenCompressed, 0x3A980, D_803275F4);
    func_801053B0(1);
    D_80327E31 = 0;
    D_80327E30 = 0;
    switch (D_80327D40) {
    case 0:
        D_80327D90 = 0;
        D_80327D68 = 255;
        D_80327D78 = 0;
        D_80327D80 = TIME_USEC() + 7000000;
        D_80327D70 = TIME_USEC() + 2000000;
        D_80327D88 = TIME_USEC() + 5000000;
        break;
    case 5:
        D_80327D40 = 6;
        D_80327E10 = 0;
        D_80327DF0 = TIME_USEC() + 12000000;
        D_80327DF8 = TIME_USEC();
        D_80327E00 = TIME_USEC() + 4000000;
        D_80327E08 = TIME_USEC() + 8000000;
        D_80327E16 = 0;
        D_80327E15 = 0;
        D_80327E14 = 255;
        D_80327E19 = 1;
        D_80327E18 = 1;
        D_80327E17 = 1;
        D_80327E40 = func_800C3EA4(42, 0x7000);
        break;
    }
    D_80132EF0 = 1;
}
