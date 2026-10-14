#include "types.h"

extern u64 osGetTime(void) __asm__("func_801120A0");
extern void load_texture_draw_font(s32 font) __asm__("func_801053B0");
extern void rom_dma_read(u8 *romAddress, u8 *destination, s32 size) __asm__("func_80077930");
extern s32 lzari_decode(u32 sourceSize, u8 *source, u32 destinationSize, u8 *destination) __asm__("func_800F4F60");
extern void func_80079064(void);
extern void func_8007968C(void);
extern void func_80079BD4(void);
extern void func_8007D850(void);
extern void func_8007D998(void);
extern void func_8007EEF8(s32, s32);
extern void func_800A8ECC(void);
extern void func_800A8EE0(void);
extern void func_800AC2D0(void);
extern void func_800C4254(f32);
extern u8 menu_poll_input_d(void) __asm__("func_800C4DFC");
extern void func_800EC380(s32);
extern void func_8010527C(void);
extern f32 D_800735AC;
extern u64 D_80145DA0;
extern s8 D_80132EF0;
extern u8 D_80135770;
extern u8 *D_803275F4;
extern s32 D_803276D0;
extern u32 *gFrameDisplayList __asm__("D_803276D4");
extern s32 D_803276D8;
extern s32 D_80327B4C;
extern u8 gSequenceDState __asm__("D_80327E50");
extern u64 D_80327E58;
extern s32 D_80327E60;
extern u8 D_80327EB1;
extern u8 D_80327EB2;
extern u8 gScreenCompressed[] __asm__("D_803DA800");
extern u8 gScreenSource[] __asm__("D_803DA800");
extern u8 D_B0596EA0[];
extern u8 D_B05A1110[];

s32 run_sequence_d_loop(void) __asm__("func_800C4AE0");

s32 run_sequence_d_loop(void) {
    s32 size;
    s32 next;
    s32 mask;

    size = D_B05A1110 - D_B0596EA0;
    rom_dma_read(D_B0596EA0, gScreenCompressed, size);
    lzari_decode(size, gScreenSource, 0x25800, D_803275F4);
    load_texture_draw_font(1);
    D_80327EB2 = 0;
    D_80327EB1 = 0;
    switch (gSequenceDState) {
    case 0:
        D_80327E58 = osGetTime() * 1000000 / D_80145DA0 + 12000000;
        D_80327E60 = 0xF0;
        break;
    case 4:
        D_80327EB1 = 1;
        gSequenceDState = 5;
        break;
    }
    D_80132EF0 = 1;
    while (D_80327EB1 == 0) {
        s32 dl;
        s32 base;
        u32 *cmd;

        func_800A8ECC();
        func_800A8EE0();
        D_80327EB1 = menu_poll_input_d();
        func_8007D850();
        gFrameDisplayList = (u32 *)(D_803276D0 + D_803276D8 * 0x11000);
        if (D_80327EB1 == 0) {
            func_800C4254(D_800735AC);
        }
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
    func_80079BD4();
    func_80079064();
    D_80132EF0 = 0;
    if (gSequenceDState == 4) {
        D_80132EF0 = 1;
        D_80327B4C = 0x13;
        func_800EC380(9);
        return 0xD;
    }
    if (D_80135770 != 0) {
        func_800AC2D0();
        return 0xF;
    }
    func_800EC380(0xB);
    func_8010527C();
    D_80327B4C = 2;
    return 0xD;
}
