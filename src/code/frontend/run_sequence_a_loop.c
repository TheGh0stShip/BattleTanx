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
extern void func_800B9C9C(void);
extern void func_800BB69C(f32);
extern u8 menu_poll_input_a(void) __asm__("func_800BC448");
extern void reset_sequence_b(void) __asm__("func_800BD1F0");
extern void func_800EC380(s32);
extern f32 D_80073440;
extern s8 D_80132EF0;
extern u8 D_80135770;
extern s32 D_803276D0;
extern u32 *gFrameDisplayList __asm__("D_803276D4");
extern s32 D_803276D8;
extern s32 D_80327B4C;
extern u8 gSequenceAIndex __asm__("D_80327B50");
extern u8 gSequenceAState __asm__("D_80327C0F");
extern s32 D_80327C20;

s32 run_sequence_a_loop(void) __asm__("func_800BC214");

s32 run_sequence_a_loop(void) {
    s32 next;
    s32 mask;
    u8 result;
    s32 arg;

    func_800B9C9C();
    result = 0;
    while (gSequenceAState == 0) {
        s32 dl;
        s32 base;
        u32 *cmd;

        func_800A8ECC();
        func_800A8EE0();
        result = menu_poll_input_a();
        func_8007D850();
        gFrameDisplayList = (u32 *)(D_803276D0 + D_803276D8 * 0x11000);
        if (gSequenceAState == 0) {
            func_800BB69C(D_80073440);
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
    if (D_80327C20 != -1) {
        func_800798C0(D_80327C20);
        D_80327C20 = -1;
    }
    func_80079BD4();
    func_80079064();
    D_80132EF0 = 0;
    if (result == 0 && ((gSequenceAIndex == 0 | gSequenceAIndex == 4) || (gSequenceAIndex == 6 | gSequenceAIndex == 8))) {
        D_80132EF0 = 1;
        D_80327B4C = 0x10;
        switch (gSequenceAIndex) {
            case 0:
                arg = 4;
                break;
            case 4:
                arg = 0xA;
                break;
            case 6:
                arg = 5;
                break;
            case 8:
                arg = 6;
                break;
            default:
                return 0xD;
        }
        func_800EC380(arg);
        return 0xD;
    }
    if (D_80135770 != 0) {
        reset_sequence_b();
        return 0x11;
    }
    return 0xB;
}
