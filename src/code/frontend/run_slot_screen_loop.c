#include "types.h"

extern void func_8007968C(void);
extern void func_8007D850(void);
extern void func_8007D998(void);
extern void func_8007EEF8(s32, s32);
extern void func_800A8ECC(void);
extern void func_800A8EE0(void);
extern void load_resource_bundle_3D16D0(void) __asm__("func_800D6908");
extern void load_slot_screen_and_init_slots(void) __asm__("func_800D6A54");
extern void func_800D6BC0(s32 frame);
extern u8 func_800D8C20(void);
extern s32 D_80134E58;
extern s32 D_80134E5C;
extern s32 gMenuSelection __asm__("D_801352A4");
extern s32 D_803276D0;
extern u32 *gFrameDisplayList __asm__("D_803276D4");
extern s32 D_803276D8;

static inline void draw_frame(void)
{
    s32 dl;
    s32 base;
    u32 *cmd;
    s32 next;
    s32 mask;

    func_8007D850();
    gFrameDisplayList = (u32 *)(D_803276D0 + D_803276D8 * 0x11000);
    func_800D6BC0(D_803276D8);
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

s32 run_slot_screen_loop(void) __asm__("func_800D89F4");

/* Loads the slot screen (re-initialising slots when D_80134E58 changed), runs frames until a choice, then returns the next state. */
s32 run_slot_screen_loop(void)
{
    u8 result;
    s32 i;
    s32 ret;

    result = 0;
    if (D_80134E58 == gMenuSelection) {
        load_resource_bundle_3D16D0();
    } else {
        load_slot_screen_and_init_slots();
    }
    gMenuSelection = D_80134E58;
    while (result == 0) {
        func_800A8ECC();
        func_800A8EE0();
        result = func_800D8C20();
        draw_frame();
    }
    for (i = 0; i < 3; i++) {
        draw_frame();
    }
    if (result == 1) {
        if (D_80134E5C == 4) {
            return 8;
        }
        return 4;
    }
    return 2;
}
