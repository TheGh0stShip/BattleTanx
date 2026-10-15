#include "types.h"

extern u64 osClockRate __asm__("D_80145DA0");
extern u64 osGetTime(void) __asm__("func_801120A0");
extern void rom_dma_read(u8 *romAddress, u8 *destination, s32 size) __asm__("func_80077930");
extern s32 lzari_decode(u32 sourceSize, u8 *source, u32 destinationSize, u8 *destination) __asm__("func_800F4F60");
extern void func_8007968C(void);
extern void func_800796F0(s32, s32);
extern void func_80079BB4(s32);
extern void func_80079BF4(s32);
extern void func_8007D850(void);
extern void func_8007D998(void);
extern void func_8007EEF8(s32);
extern void func_800A8ECC(void);
extern void func_800A8EE0(void);
extern u8 func_800C5B64(void);
extern void func_800C5580(void);
extern void func_801053B0(s32);
extern s32 D_80125794;
extern u8 D_80134E75;
extern u8 *D_803275F4;
extern s32 D_803276D0;
extern u32 *gFrameDisplayList __asm__("D_803276D4");
extern s32 D_803276D8;
extern s32 D_80327B4C;
extern u8 D_80327EC0;
extern u8 gScreenCompressed[] __asm__("D_803DA800");
extern u8 gScreenSource[] __asm__("D_803DA800");
extern u8 D_B049DCD0[];
extern u8 D_B04AC150[];

#define TIME_USEC() (osGetTime() * 1000000 / osClockRate)

s32 run_attract_screen_loop(void) __asm__("func_800C5848");

s32 run_attract_screen_loop(void) {
    s32 size = D_B04AC150 - D_B049DCD0;
    u64 end;
    s32 next;
    s32 mask;
    s32 dl;
    s32 base;
    u32 *cmd;

    rom_dma_read(D_B049DCD0, gScreenCompressed, size);
    lzari_decode(size, gScreenSource, 0x25800, D_803275F4);
    func_80079BB4(6);
    func_80079BF4((s16)(D_80125794 << 12));
    func_801053B0(1);
    end = TIME_USEC() + 7000000;
    D_80327EC0 = 0;
    while (TIME_USEC() < end) {
        func_800A8ECC();
        func_800A8EE0();
        D_80327EC0 = func_800C5B64();
        func_8007D850();
        gFrameDisplayList = (u32 *)(D_803276D0 + D_803276D8 * 0x11000);
        func_800C5580();
        cmd = gFrameDisplayList;
        dl = D_803276D0 + D_803276D8 * 0x11000;
        gFrameDisplayList = cmd + 2;
        cmd[0] = 0xB8000000;
        cmd[1] = 0;
        func_8007EEF8(dl);
        next = D_803276D8 + 1;
        mask = -(next < 3);
        D_803276D8 = next & mask;
        func_8007968C();
        func_8007D998();
        if (D_80327EC0 != 0 && ++D_80327EC0 != 0) {
            break;
        }
    }
    func_800796F0(1, 0);
    if (D_80327EC0 != 0) {
        D_80134E75 = 1;
        return 10;
    }
    D_80327B4C = 1;
    return 13;
}
