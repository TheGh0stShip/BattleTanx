#include "types.h"

typedef void (*ScreenInitFunc)(void);
typedef void (*ScreenDrawFunc)(f32 alpha);

extern void func_8007968C(void);
extern void func_8007D850(void);
extern void func_8007D998(void);
extern void func_8007EEF8(s32 dl, s32 index);
extern s32 D_803275F0;
extern u8 *D_803275F4;
extern s32 D_803275F8;
extern u8 *D_803275FC[5];
extern s32 D_80327610;
extern ScreenDrawFunc D_80327620[];
extern s32 D_80327674;
extern ScreenInitFunc D_80327678[];
extern s32 D_803276D0;
extern u32 *gFrameDisplayList __asm__("D_803276D4");
extern s32 D_803276D8;

static inline void select_screen_buffer(s32 n) {
    switch (n) {
    case 0:
        D_803275F0 = 0;
        D_803275F4 = D_803275FC[0];
        break;
    case 1:
        D_803275F0 = 1;
        D_803275F4 = D_803275FC[1];
        break;
    case 2:
        D_803275F0 = 2;
        D_803275F4 = D_803275FC[2];
        break;
    case 3:
        D_803275F0 = 3;
        D_803275F4 = D_803275FC[3];
        break;
    case 4:
        D_803275F0 = 4;
        D_803275F4 = D_803275FC[4];
        break;
    }
}

void slide_screen_transition(s32 from, s32 to) __asm__("func_800ABAB8");

void slide_screen_transition(s32 from, s32 to) {
    s32 cur = D_80327610 + 1;
    s32 other;
    s32 forward;
    s32 x;
    s32 offset;
    s32 offset2;
    s32 next;
    s32 mask;
    u32 *cmd;
    s32 index;

    D_80327610 = cur & 1;
    other = (cur & 1) + 1;
    select_screen_buffer(cur);
    D_80327678[from]();
    select_screen_buffer(other);
    forward = from < to;
    D_80327678[to]();
    for (x = 0; x < 320; x += 8) {
        func_8007D850();
        gFrameDisplayList = (u32 *)(D_803276D0 + D_803276D8 * 0x11000);
        offset = x;
        if (forward) {
            offset = -x;
            offset2 = offset + 320;
        } else {
            offset2 = x - 320;
        }
        D_803275F8 = offset;
        select_screen_buffer(cur);
        D_80327674 = 1;
        D_80327620[from](1.0f);
        D_803275F8 = offset2;
        select_screen_buffer(other);
        D_80327674 = 0;
        D_80327620[to](0.0f);
        cmd = gFrameDisplayList;
        index = D_803276D8;
        gFrameDisplayList = cmd + 2;
        cmd[0] = 0xB8000000;
        cmd[1] = 0;
        func_8007EEF8(D_803276D0 + index * 0x11000, index);
        next = D_803276D8 + 1;
        mask = -(next < 3);
        D_803276D8 = next & mask;
        func_8007968C();
        func_8007D998();
    }
    D_803275F8 = 0;
    D_80327674 = 1;
}
