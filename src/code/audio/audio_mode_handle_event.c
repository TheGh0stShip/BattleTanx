#include "types.h"

typedef struct AudioModeState {
    s32 mode;
    u8 *currentValue;
    s32 value08;
    u8 *values[5];
    s32 value24;
    s32 value28;
    u8 *bufferEnd;
    u8 *bufferStart;
} AudioModeState;

extern AudioModeState gAudioModeState __asm__("D_803275F0");
extern void process_graphics_messages(void) __asm__("func_80079064");
extern void audio_mode_apply_event(s32 id, s32 event) __asm__("func_800ABAB8");

void audio_mode_handle_event(s32 id, s32 event) __asm__("func_800AB9FC");

void audio_mode_handle_event(s32 id, s32 event) {
    process_graphics_messages();
    switch (event) {
    case 1:
        gAudioModeState.mode = 1;
        gAudioModeState.currentValue = gAudioModeState.values[1];
        break;
    case 2:
        if (id == 15) break;
        if (id == 7) break;
        if (id == 8) break;
        if (id == 1) break;
        if (id == 10) break;
        if (id == 3) break;
    case 5:
    case 6:
    case 9:
        audio_mode_apply_event(id, event);
        break;
    case 10:
        break;
    }
}
