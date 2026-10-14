#include "types.h"

extern s32 func_8007B590(s32 mode);
extern s32 func_8007C344(s32 mode);
extern s8 D_8012579D;
extern s8 D_801B4AE0;
extern s32 D_80327B4C;

void run_top_level_state_loop(u16 state) __asm__("func_8007AC20");

void run_top_level_state_loop(u16 state) {
    for (;;) {
        switch (state) {
        case 2:
            func_8007B590(2);
            D_801B4AE0 = D_80327B4C;
            state = 0;
            break;
        case 1:
            D_8012579D = 0;
            state = func_8007B590(1);
            break;
        case 0:
            state = func_8007C344(0);
            break;
        }
    }
}
