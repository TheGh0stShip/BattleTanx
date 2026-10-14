#include "types.h"

#ifndef NULL
#define NULL 0
#endif

u32 func_80110480();
extern s32 D_80125778;

void audio_poll_dma_idle(void) __asm__("func_8007A758");

void audio_poll_dma_idle(void) {
    if (((func_80110480() >> 2) == 0) && (D_80125778 == 0)) {
        D_80125778 = 0;
    }
}
