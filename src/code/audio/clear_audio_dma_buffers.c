#include "types.h"

typedef struct AudioDmaBuffer {
    struct AudioDmaBuffer *next;
    struct AudioDmaBuffer *prev;
    u32 startAddr;
    u32 lastFrame;
} AudioDmaBuffer;

typedef struct AudioDmaLists {
    AudioDmaBuffer *firstUsed;
    AudioDmaBuffer *firstFree;
} AudioDmaLists;

extern s32 osRecvMesg(void *queue, void **message, s32 flags) __asm__("func_80119240");
extern void audio_dma_unlink(AudioDmaBuffer *node) __asm__("func_8011C150");
extern void audio_dma_link(AudioDmaBuffer *node, AudioDmaBuffer *after) __asm__("func_8011C180");
extern u32 D_80125768;
extern u32 D_8012576C;
extern u8 D_801529D8;
extern AudioDmaLists D_80152F84;

void clear_audio_dma_buffers(void) __asm__("func_8007A968");

void clear_audio_dma_buffers(void) {
    u32 i;
    void *message = 0;
    AudioDmaBuffer *buffer;
    AudioDmaBuffer *next;

    for (i = 0; i < D_8012576C; i++) {
        osRecvMesg(&D_801529D8, &message, 0);
    }

    buffer = D_80152F84.firstUsed;
    while (buffer != 0) {
        next = buffer->next;
        if (buffer->lastFrame + 1 < D_80125768) {
            if (D_80152F84.firstUsed == buffer) {
                D_80152F84.firstUsed = next;
            }
            audio_dma_unlink(buffer);
            if (D_80152F84.firstFree != 0) {
                audio_dma_link(buffer, D_80152F84.firstFree);
            } else {
                D_80152F84.firstFree = buffer;
                buffer->next = 0;
                buffer->prev = 0;
            }
        }
        buffer = next;
    }
    D_8012576C = 0;
    D_80125768++;
}
