#include "types.h"

extern void func_8007968C(void);
extern void func_8007D850(void);
extern void func_8007D998(void);
extern void func_8007EEF8(s32, s32);
extern void func_800A8ECC(void);
extern void func_800A8EE0(void);
extern void load_resource_bundle_3DC430(void) __asm__("func_800C8210");
extern void func_800C83D4(f32);
extern u8 func_800CA5BC(void);
extern f32 D_80073700;
extern f32 D_80073704;
extern s32 D_80134010[4];
extern s32 D_80134020[4];
extern s32 D_80134A80[];
extern s32 D_803276D0;
extern u32 *gFrameDisplayList __asm__("D_803276D4");
extern s32 D_803276D8;

static inline void draw_frame(f32 *value)
{
    s32 dl;
    s32 base;
    u32 *cmd;
    s32 next;
    s32 mask;

    func_8007D850();
    gFrameDisplayList = (u32 *)(D_803276D0 + D_803276D8 * 0x11000);
    func_800C83D4(*value);
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

s32 run_bundle_3DC430_screen_loop(void) __asm__("func_800CA398");

s32 run_bundle_3DC430_screen_loop(void) {
    u8 result;
    s32 i;

    load_resource_bundle_3DC430();
    do {
        func_800A8ECC();
        func_800A8EE0();
        result = func_800CA5BC();
        draw_frame(&D_80073700);
    } while (result == 0);
    for (i = 0; i < 3; i++) {
        draw_frame(&D_80073704);
    }
    if (result == 2) {
        return 7;
    }
    for (i = 0; i < 4; i++) {
        D_80134020[i] = D_80134A80[D_80134010[i]];
    }
    return 8;
}
