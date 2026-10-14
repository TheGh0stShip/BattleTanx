#include "types.h"

#ifndef NULL
#define NULL 0
#endif

s32 func_80119240(s32 *, s32, s32);
extern s32 D_801529D8;
extern s32 D_80152F90;
extern s32 D_801B4A28;

void audio_drain_message_queues(void) __asm__("func_8007A36C");

void audio_drain_message_queues(void) {
    do {

    } while (func_80119240(&D_801B4A28, 0, 0) == 0);
    do {

    } while (func_80119240(&D_80152F90, 0, 0) == 0);
    do {

    } while (func_80119240(&D_801529D8, 0, 0) == 0);
}
