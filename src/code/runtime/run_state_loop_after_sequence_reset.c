#include "types.h"

extern void reset_audio_sequence_state(void) __asm__("func_800AC2D0");
extern void reset_sequence_a(void) __asm__("func_800B9C80");
extern void reset_sequence_b(void) __asm__("func_800BD1F0");
extern void reset_sequence_c(void) __asm__("func_800C0880");
extern void reset_sequence_d(void) __asm__("func_800C3EF0");
extern void trigger_all_sound_ids(void) __asm__("func_80079948");
extern s32 func_8007B590(s32 mode);
extern s32 func_8007C344(s32 mode);
extern s8 D_801B4AE0;
extern s32 D_80327B4C;

s32 run_state_loop_after_sequence_reset(s32 state) __asm__("func_8007C58C");

s32 run_state_loop_after_sequence_reset(s32 state) {
    u16 result;

    switch (state) {
    case 15:
        reset_audio_sequence_state();
        break;
    case 16:
        reset_sequence_a();
        break;
    case 17:
        reset_sequence_b();
        break;
    case 18:
        reset_sequence_c();
        break;
    case 19:
        reset_sequence_d();
        break;
    default:
        return;
    }
    D_801B4AE0 = state;
    do {
        result = func_8007C344(0);
        if (result == 2) {
            func_8007B590(2);
            D_801B4AE0 = D_80327B4C;
        }
    } while (result >= 2);
    trigger_all_sound_ids();
    return -(result == 0);
}
