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
extern u8 D_80327C30;
extern u8 D_80327C58;
extern u64 D_80327C60;
extern s32 D_80327C68;
extern u64 D_80327C70;
extern u64 D_80327C78;
extern s32 D_80327C80;
extern u64 D_80327C88;
extern u64 D_80327C90;
extern u64 D_80327C98;
extern u64 D_80327CA0;
extern s32 D_80327CA8;
extern u8 D_80327CAC;
extern u8 D_80327CAD;
extern u8 D_80327CAE;
extern u64 D_80327CB0;
extern u64 D_80327CB8;
extern u8 D_80327D2C;
extern u8 D_80327D2D;
extern u8 gScreenCompressed[] __asm__("D_803DA800");
extern u8 D_B0554D00[];
extern u8 D_B056FDB0[];

#define TIME_USEC() (osGetTime() * 1000000 / osClockRate)

void init_sequence_b_screen(void) __asm__("func_800BD20C");

void init_sequence_b_screen(void) {
    s32 size = D_B056FDB0 - D_B0554D00;

    rom_dma_read(D_B0554D00, gScreenCompressed, size);
    lzari_decode(size, gScreenCompressed, 0x25800, D_803275F4);
    func_801053B0(1);
    D_80327D2D = 0;
    D_80327D2C = 0;
    switch (D_80327C30) {
    case 255:
        D_80327C30 = 0;
        D_80327C80 = 0;
        D_80327C58 = 255;
        D_80327C68 = 0;
        D_80327C70 = TIME_USEC() + 7000000;
        D_80327C60 = TIME_USEC() + 2000000;
        D_80327C78 = TIME_USEC() + 5000000;
        break;
    case 1:
        D_80327C30 = 2;
        D_80327C88 = TIME_USEC() + 12000000;
        D_80327C90 = TIME_USEC();
        D_80327C98 = TIME_USEC() + 4000000;
        D_80327CA0 = TIME_USEC() + 8000000;
        D_80327CA8 = 0;
        D_80327CAE = 0;
        D_80327CAD = 0;
        D_80327CAC = 255;
        D_80327CB0 = TIME_USEC() + 1000000;
        D_80327CB8 = TIME_USEC() + 7000000;
        func_80079BD4();
        func_80079BB4(13);
        func_80079BF4((s16)(D_80125794 << 12));
        break;
    }
    D_80132EF0 = 1;
}
