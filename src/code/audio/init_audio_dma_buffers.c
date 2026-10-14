#include "types.h"

typedef struct AudioDmaBuffer {
    struct AudioDmaBuffer *next;
    struct AudioDmaBuffer *prev;
    u32 startAddr;
    u32 lastFrame;
    void *ptr;
} AudioDmaBuffer;

#define AUDIO_DMA_BUFFER_COUNT 0x50
#define AUDIO_DMA_BUFFER_SIZE 0xA00

extern void *alHeapDBAlloc(u8 *file, s32 line, void *heap, s32 num, s32 size) __asm__("func_80112140");
extern void audio_dma_link(AudioDmaBuffer *node, AudioDmaBuffer *after) __asm__("func_8011C180");
extern u8 D_80150340[];
extern AudioDmaBuffer D_80150398[AUDIO_DMA_BUFFER_COUNT];
extern u8 D_80152F80;

void init_audio_dma_buffers(void) __asm__("func_8007A178");

void init_audio_dma_buffers(void)
{
    u32 i;

    D_80150398[0].prev = 0;
    D_80150398[0].next = 0;
    for (i = 0; i < AUDIO_DMA_BUFFER_COUNT - 1; i++) {
        audio_dma_link(&D_80150398[i + 1], &D_80150398[i]);
        D_80150398[i].ptr = alHeapDBAlloc(0, 0, D_80150340, 1, AUDIO_DMA_BUFFER_SIZE);
    }
    D_80150398[i].ptr = alHeapDBAlloc(0, 0, D_80150340, 1, AUDIO_DMA_BUFFER_SIZE);
    D_80152F80 = 0;
}
