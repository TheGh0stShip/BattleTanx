#include "types.h"

extern u8 D_80150398;
extern u8 D_80152F80;
extern s32 D_80152F84;
extern u8 *D_80152F88;
extern void audio_dma_callback(void) __asm__("func_8007A7E0");

void *init_audio_dma_state(u8 **state) __asm__("func_8007A79C");

void *init_audio_dma_state(u8 **state)
{
    u8 *initialized;

    initialized = &D_80152F80;
    if (*initialized == 0) {
        D_80152F88 = &D_80150398;
        D_80152F84 = 0;
        *initialized = 1;
    }
    *state = initialized;
    return audio_dma_callback;
}
