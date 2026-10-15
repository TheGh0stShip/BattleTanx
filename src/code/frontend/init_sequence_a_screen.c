#include "types.h"

extern u64 osClockRate __asm__("D_80145DA0");
extern u64 osGetTime(void) __asm__("func_801120A0");
extern void rom_dma_read(u8 *romAddress, u8 *destination, s32 size) __asm__("func_80077930");
extern s32 lzari_decode(u32 sourceSize, u8 *source, u32 destinationSize, u8 *destination) __asm__("func_800F4F60");
extern void func_801053B0(s32);
extern void func_80079BB4(s32);
extern void func_80079BD4(void);
extern void func_80079BF4(s32);
extern s32 D_80125794;
extern u8 *D_803275F4;
extern u8 D_80132EF0;
extern u8 D_80327B50;
extern u8 D_80327B51;
extern u64 D_80327B58;
extern s32 D_80327B60;
extern u64 D_80327B68;
extern u64 D_80327B70;
extern s32 D_80327B78;
extern u64 D_80327B80;
extern u64 D_80327B98;
extern u64 D_80327BA0;
extern u64 D_80327BA8;
extern u64 D_80327BB0;
extern s32 D_80327BB8;
extern u8 D_80327BBC;
extern u8 D_80327BBD;
extern u8 D_80327BBE;
extern u64 D_80327BC0;
extern u64 D_80327BE8;
extern u64 D_80327BF0;
extern u64 D_80327BF8;
extern u64 D_80327C00;
extern s32 D_80327C08;
extern u8 D_80327C0C;
extern u8 D_80327C0D;
extern u8 D_80327C0E;
extern u8 D_80327C0F;
extern u8 D_80327C10;
extern u8 gScreenCompressed[] __asm__("D_803DA800");
extern u8 D_B0533870[];
extern u8 D_B0554D00[];

#define TIME_USEC() (osGetTime() * 1000000 / osClockRate)

void init_sequence_a_screen(void) __asm__("func_800B9C9C");

void init_sequence_a_screen(void) {
    s32 size = D_B0554D00 - D_B0533870;

    rom_dma_read(D_B0533870, gScreenCompressed, size);
    lzari_decode(size, gScreenCompressed, 0x3A980, D_803275F4);
    func_801053B0(1);
    D_80327C10 = 0;
    D_80327C0F = 0;
    switch (D_80327B50) {
    case 255:
        D_80327B78 = 0;
        D_80327B51 = 255;
        D_80327B60 = 0;
        D_80327B68 = TIME_USEC() + 7000000;
        D_80327B58 = TIME_USEC() + 2000000;
        D_80327B70 = TIME_USEC() + 5000000;
        break;
    case 0:
        D_80327B80 = TIME_USEC() + 5000000;
        D_80327B50 = 1;
        break;
    case 4:
        D_80327B50 = 5;
        D_80327B98 = TIME_USEC() + 12000000;
        D_80327BB8 = 0;
        D_80327BA0 = TIME_USEC();
        D_80327BA8 = TIME_USEC() + 4000000;
        D_80327BB0 = TIME_USEC() + 8000000;
        D_80327BBE = 0;
        D_80327BBD = 0;
        D_80327BBC = 0;
        func_80079BD4();
        break;
    case 6:
        D_80327B50 = 7;
        D_80327BC0 = TIME_USEC() + 5000000;
        func_80079BD4();
        func_80079BB4(6);
        func_80079BF4((s16)(D_80125794 << 12));
        break;
    case 8:
        D_80327B50 = 9;
        D_80327BE8 = TIME_USEC() + 9000000;
        D_80327C08 = 0;
        D_80327BF0 = TIME_USEC();
        D_80327BF8 = TIME_USEC() + 3000000;
        D_80327C00 = TIME_USEC() + 6000000;
        D_80327C0E = 0;
        D_80327C0D = 0;
        D_80327C0C = 0;
        break;
    }
    D_80132EF0 = 1;
}
