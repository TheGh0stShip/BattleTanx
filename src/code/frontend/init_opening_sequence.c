#include "types.h"

extern u64 osClockRate __asm__("D_80145DA0");
extern u64 osGetTime(void) __asm__("func_801120A0");
extern void rom_dma_read(u8 *romAddress, u8 *destination, s32 size) __asm__("func_80077930");
extern s32 lzari_decode(u32 sourceSize, u8 *source, u32 destinationSize, u8 *destination) __asm__("func_800F4F60");
extern void func_801053B0(s32);
extern void func_800798C0(s32);
extern void func_80079BB4(s32);
extern void func_80079BD4(void);
extern void func_80079BF4(s32);
extern s32 func_800B9C0C(u8 *);
extern s32 func_800B9C34(s32, s32);
extern s32 D_80125794;
extern u8 D_80132634[];
extern u8 D_80132660[];
extern u8 D_8013269C[];
extern u8 D_80132C9C[];
extern u8 *D_803275F4;
extern u8 *D_80327604;
extern u8 D_803276E0;
extern u8 D_803276E1;
extern u64 D_803276E8;
extern s32 D_803276F0;
extern u64 D_803276F8;
extern u64 D_80327700;
extern s32 D_80327708;
extern u64 D_803277E0;
extern u64 D_803277E8;
extern u64 D_803277F0;
extern u64 D_803277F8;
extern u64 D_80327800;
extern u8 D_80327808;
extern u8 D_80327809;
extern u8 D_8032780A;
extern u8 D_8032780B;
extern s32 D_8032780C;
extern s32 D_80327810;
extern s32 D_80327814;
extern s32 D_80327818;
extern u64 D_803278E0;
extern u64 D_803278E8;
extern s32 D_803278F0;
extern u64 D_80327900;
extern u64 D_80327908;
extern u64 D_80327910;
extern u64 D_80327918;
extern u8 D_80327920;
extern u8 D_80327921;
extern u8 D_80327922;
extern u64 D_80327A58;
extern u64 D_80327A60;
extern s32 D_80327A68;
extern s32 D_80327A6C;
extern u64 D_80327A78;
extern u64 D_80327A80;
extern u64 D_80327A88;
extern u8 D_80327A90;
extern u8 D_80327A91;
extern u8 D_80327A92;
extern u8 D_80327B20;
extern u8 D_80327B21;
extern s32 D_80327B30;
extern s32 D_80327B34;
extern s32 D_80327B38;
extern u8 D_80327B44;
extern u8 D_B04B4B00[];
extern u8 D_B04C1930[];
extern u8 D_B04E46E0[];
extern u8 D_B050D930[];
extern u8 D_B0533870[];

#define TIME_USEC() (osGetTime() * 1000000 / osClockRate)

void init_opening_sequence(void) __asm__("func_800AC2E0");

void init_opening_sequence(void) {
    s32 size;

    D_80327B44 = 0;
    switch (D_803276E0) {
    case 0:
        size = D_B04C1930 - D_B04B4B00;
        rom_dma_read(D_B04B4B00, D_80327604, size);
        lzari_decode(size, D_80327604, 0x3A980, D_803275F4);
        break;
    case 4:
        size = D_B04E46E0 - D_B04C1930;
        rom_dma_read(D_B04C1930, D_80327604, size);
        lzari_decode(size, D_80327604, 0x3A980, D_803275F4);
        break;
    case 9:
        size = D_B050D930 - D_B04E46E0;
        rom_dma_read(D_B04E46E0, D_80327604, size);
        lzari_decode(size, D_80327604, 0x493E0, D_803275F4);
        break;
    case 14:
        size = D_B0533870 - D_B050D930;
        rom_dma_read(D_B050D930, D_80327604, size);
        lzari_decode(size, D_80327604, 0x3A980, D_803275F4);
        break;
    }
    func_801053B0(1);
    D_80327B21 = 0;
    D_80327B20 = 0;
    switch (D_803276E0) {
    case 0:
        func_80079BD4();
        D_80327708 = 0;
        D_803276E1 = 255;
        D_803276F0 = 0;
        D_803276F8 = TIME_USEC() + 7000000;
        D_803276E8 = TIME_USEC() + 2000000;
        D_80327700 = TIME_USEC() + 5000000;
        break;
    case 4:
        D_803276E0 = 5;
        D_8032780C = 0;
        D_803277E0 = TIME_USEC() + 12000000;
        D_803277E8 = TIME_USEC();
        D_803277F0 = TIME_USEC() + 4000000;
        D_803277F8 = TIME_USEC() + 8000000;
        D_80327800 = TIME_USEC() + 9000000;
        D_8032780B = 0;
        D_8032780A = 0;
        D_80327809 = 0;
        D_80327808 = 0;
        D_80327810 = func_800B9C0C(D_80132634);
        D_80327814 = func_800B9C0C(D_80132660);
        D_80327818 = func_800B9C0C(D_8013269C);
        D_80327B30 = 0;
        if (D_80327B34 != -1) {
            func_800798C0(D_80327B34);
        }
        D_80327B38 = func_800B9C34(40, 0x7000);
        D_80327B34 = func_800B9C34(36, 0x7000);
        break;
    case 9:
        D_803276E0 = 10;
        D_803278E8 = TIME_USEC();
        D_803278E0 = TIME_USEC() + 9000000;
        D_80327900 = TIME_USEC();
        D_80327908 = TIME_USEC() + 3000000;
        D_80327910 = TIME_USEC() + 6000000;
        D_80327918 = TIME_USEC() + 6000000;
        D_80327920 = 0;
        D_80327921 = 0;
        D_80327922 = 0;
        D_803278F0 = 0;
        if (D_80327B34 != -1) {
            func_800798C0(D_80327B34);
            D_80327B34 = -1;
        }
        func_80079BD4();
        func_80079BB4(11);
        func_80079BF4((s16)(D_80125794 << 12));
        break;
    case 14:
        D_803276E0 = 15;
        D_80327A6C = func_800B9C0C(D_80132C9C);
        D_80327A60 = TIME_USEC();
        D_80327A58 = TIME_USEC() + 9000000;
        D_80327A78 = TIME_USEC();
        D_80327A80 = TIME_USEC() + 3000000;
        D_80327A88 = TIME_USEC() + 6000000;
        D_80327A92 = 0;
        D_80327A91 = 0;
        D_80327A90 = 0;
        D_80327A68 = 0;
        func_80079BD4();
        func_80079BB4(6);
        func_80079BF4((s16)(D_80125794 << 12));
        break;
    }
}
