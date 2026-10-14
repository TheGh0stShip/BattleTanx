#include "types.h"

extern void func_80079064(void);
extern void func_8007968C(void);
extern s32 set_and_trigger_sound(s32 id) __asm__("func_800798C0");
extern void func_80079BD4(void);
extern void func_8007D850(void);
extern void func_8007D998(void);
extern void func_8007EEF8(s32, s32);
extern void func_800A8ECC(void);
extern void func_800A8EE0(void);
extern void func_800C0898(void);
extern void func_800C224C(f32);
extern u8 menu_poll_input_c(void) __asm__("func_800C36E8");
extern void func_800C3EF0(void);
extern void func_800EC380(s32);
extern f32 D_80073570;
extern s8 D_80132EF0;
extern u8 D_80135770;
extern s32 D_803276D0;
extern u32 *gFrameDisplayList __asm__("D_803276D4");
extern s32 D_803276D8;
extern s32 D_80327B4C;
extern u8 D_80327D40;
extern u8 D_80327E30;
extern s32 D_80327E40;

s32 run_menu_c_screen_loop(void) __asm__("func_800C3534");

/* Draws frames until menu_poll_input_c reports a choice, then returns the next state id. */
s32 run_menu_c_screen_loop(void)
{
    s32 dl;
    s32 base;
    u32 *cmd;
    s32 next;
    s32 mask;

    func_800C0898();
    while (D_80327E30 == 0) {
        func_800A8ECC();
        func_800A8EE0();
        D_80327E30 = menu_poll_input_c();
        func_8007D850();
        gFrameDisplayList = (u32 *)(D_803276D0 + D_803276D8 * 0x11000);
        if (D_80327E30 == 0) {
            func_800C224C(D_80073570);
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
    if (D_80327E40 != -1) {
        set_and_trigger_sound(D_80327E40);
        D_80327E40 = -1;
    }
    func_80079BD4();
    func_80079064();
    D_80132EF0 = 0;
    if (D_80327D40 == 5) {
        D_80132EF0 = 1;
        D_80327B4C = 0x12;
        func_800EC380(8);
        return 0xD;
    }
    if (D_80135770 != 0) {
        func_800C3EF0();
        return 0x13;
    }
    return 0xB;
}
