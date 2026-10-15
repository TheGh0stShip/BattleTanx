#include "types.h"

extern s32 read_controller_buttons(s32 controller, s32 repeat) __asm__("func_80096920");
extern void stop_opening_sequence_audio(s32 handle) __asm__("func_800798C0");
extern u8 gOpeningSequenceFinished __asm__("D_80327B20");
extern s8 gOpeningSequenceSkipRequested __asm__("D_80327B21");
extern s32 gOpeningSequenceAudioHandle __asm__("D_80327B34");

u8 menu_poll_input_with_sound(void) __asm__("func_800B8750");

u8 menu_poll_input_with_sound(void)
{
    s32 buttons;

    buttons = read_controller_buttons(0, 0);
    if (buttons & 0x40) {
        gOpeningSequenceFinished = 1;
    }
    if (buttons & 0x20) {
        gOpeningSequenceFinished = 2;
    }
    gOpeningSequenceSkipRequested = 0;
    if (buttons & 0x10) {
        gOpeningSequenceSkipRequested = 1;
    }
    if (buttons != 0 && gOpeningSequenceAudioHandle != -1) {
        stop_opening_sequence_audio(gOpeningSequenceAudioHandle);
        gOpeningSequenceAudioHandle = -1;
    }
    return gOpeningSequenceFinished;
}
