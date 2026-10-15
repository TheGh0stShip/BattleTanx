#include "types.h"

extern void func_80079BB4(s32 arg0);
extern void func_80079BD4(void);
extern void func_80079BF4(s32 arg0);
extern s32 gResourceFadeNibble __asm__("D_80125794");

void select_screen_transition(u32 id) __asm__("func_8007D2A0");

void select_screen_transition(u32 id) {
    s32 transition = -1;

    switch (id) {
        case 1: transition = 7; break;
        case 2: transition = 2; break;
        case 4: transition = 0x11; break;
        case 6: transition = 3; break;
        case 7: transition = 1; break;
        case 8: transition = 0x12; break;
        case 10: transition = 0x10; break;
        case 11: transition = 4; break;
        case 12: transition = 5; break;
        case 14: transition = 8; break;
        case 16: transition = 0xA; break;
        case 5:
        case 9:
        case 13:
        case 15:
        case 17: transition = 6; break;
        case 0: transition = -1; break;
        case 18:
        case 19: break;
        default: transition = 0; break;
    }
    if (transition != -1) {
        func_80079BB4(transition);
        func_80079BF4((gResourceFadeNibble << 28) >> 16);
    } else {
        func_80079BD4();
    }
}
