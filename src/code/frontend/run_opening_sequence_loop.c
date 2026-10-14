#include "types.h"

extern void func_80079064(void);
extern void func_8007968C(void);
extern void func_800798C0(s32);
extern void func_8007D850(void);
extern void func_8007D998(void);
extern void func_8007EEF8(s32, s32);
extern void func_800A8ECC(void);
extern void func_800A8EE0(void);
extern void func_800AC2E0(void);
extern void render_opening_sequence(f32 time) __asm__("func_800B1520");
extern u8 menu_poll_input_with_sound(void) __asm__("func_800B8750");
extern void func_800B9C80(u8);
extern void func_800EC380(s32);
extern f32 D_800733B4;
extern s8 D_80132EF0;
extern u8 D_80135770;
extern s32 D_803276D0;
extern u32 *gFrameDisplayList __asm__("D_803276D4");
extern s32 D_803276D8;
extern u8 gOpeningSequencePhase __asm__("D_803276E0");
extern u8 gOpeningSequenceFinished __asm__("D_80327B20");
extern s32 gOpeningSequenceAudioHandle __asm__("D_80327B34");
extern s32 D_80327B38;
extern s8 D_80327B44;
extern s32 D_80327B4C;

s32 run_opening_sequence_loop(void) __asm__("func_800B850C");

s32 run_opening_sequence_loop(void) {
    s32 next;
    s32 mask;
    s32 arg;

    func_800AC2E0();
    while (gOpeningSequenceFinished == 0) {
        s32 dl;
        s32 base;
        u32 *cmd;

        func_800A8ECC();
        func_800A8EE0();
        gOpeningSequenceFinished = menu_poll_input_with_sound();
        func_8007D850();
        gFrameDisplayList = (u32 *)(D_803276D0 + D_803276D8 * 0x11000);
        if (gOpeningSequenceFinished == 0) {
            render_opening_sequence(D_800733B4);
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
    if (gOpeningSequenceAudioHandle != -1) {
        func_800798C0(gOpeningSequenceAudioHandle);
        gOpeningSequenceAudioHandle = -1;
    }
    if (D_80327B38 != -1) {
        func_800798C0(D_80327B38);
        D_80327B38 = -1;
    }
    func_80079064();
    D_80132EF0 = 0;
    if ((gOpeningSequencePhase == 4 | gOpeningSequencePhase == 9) || gOpeningSequencePhase == 14) {
        D_80132EF0 = 1;
        D_80327B4C = 0xF;
        D_80327B44 = 0;
        switch (gOpeningSequencePhase) {
            case 4:
                arg = 1;
                break;
            case 9:
                arg = 2;
                break;
            case 14:
                arg = 3;
                break;
            default:
                return 0xD;
        }
        func_800EC380(arg);
        return 0xD;
    }
    if (D_80135770 != 0) {
        func_800B9C80(gOpeningSequencePhase);
        return 0x10;
    }
    if (gOpeningSequenceFinished == 2) {
        return 0x14;
    }
    return 0xB;
}
