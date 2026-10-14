#include "types.h"

extern void func_80079064(void);
extern void func_8007968C(void);
extern void func_800798C0(s32);
extern void func_80079BD4(void);
extern void func_8007D850(void);
extern void func_8007D998(void);
extern void func_8007EEF8(s32, s32);
extern void func_800A8ECC(void);
extern void func_800A8EE0(void);
extern void func_800BD20C(void);
extern void func_800BE99C(f32);
extern u8 menu_poll_input_b(void) __asm__("func_800BFF68");
extern void func_800C0880(void);
extern void func_800EC380(s32);
extern f32 D_800734D0;
extern s8 D_80132EF0;
extern u8 D_80135770;
extern s32 D_803276D0;
extern u32 *gFrameDisplayList __asm__("D_803276D4");
extern s32 D_803276D8;
extern s32 D_80327B4C;
extern u8 gSequenceBIndex __asm__("D_80327C30");
extern u8 gSequenceBState __asm__("D_80327D2C");
extern s32 D_80327D38;

s32 run_sequence_b_loop(void) __asm__("func_800BFDB4");

s32 run_sequence_b_loop(void) {
    s32 next;
    s32 mask;

    func_800BD20C();
    while (gSequenceBState == 0) {
        s32 dl;
        s32 base;
        u32 *cmd;

        func_800A8ECC();
        func_800A8EE0();
        gSequenceBState = menu_poll_input_b();
        func_8007D850();
        gFrameDisplayList = (u32 *)(D_803276D0 + D_803276D8 * 0x11000);
        if (gSequenceBState == 0) {
            func_800BE99C(D_800734D0);
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
    if (D_80327D38 != -1) {
        func_800798C0(D_80327D38);
        D_80327D38 = -1;
    }
    func_80079BD4();
    func_80079064();
    D_80132EF0 = 0;
    if (gSequenceBIndex == 1) {
        D_80132EF0 = 1;
        D_80327B4C = 0x11;
        func_800EC380(7);
        return 0xD;
    }
    if (D_80135770 != 0) {
        func_800C0880();
        return 0x12;
    }
    return 0xB;
}
