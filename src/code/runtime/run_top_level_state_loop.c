#include "types.h"

extern s32 start_skirmish_wave(u16 mode) __asm__("func_8007B590");
extern s32 func_8007C344(s32 mode);
extern s8 D_8012579D;
extern s8 D_801B4AE0;
extern s32 D_80327B4C;

void run_top_level_state_loop(u16 state) __asm__("func_8007AC20");

void run_top_level_state_loop(u16 state) {
    for (;;) {
        switch (state) {
        case 2:
            start_skirmish_wave(2);
            D_801B4AE0 = D_80327B4C;
            state = 0;
            break;
        case 1:
            D_8012579D = 0;
            state = start_skirmish_wave(1);
            break;
        case 0:
            state = func_8007C344(0);
            break;
        }
    }
}
