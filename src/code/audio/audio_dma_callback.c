#include "types.h"

#define AUDIO_DMA_BUFFER_LENGTH 0xA00

typedef struct AudioDmaBuffer {
    struct AudioDmaBuffer *next;
    struct AudioDmaBuffer *prev;
    s32 startAddr;
    u32 lastFrame;
    u8 *ptr;
} AudioDmaBuffer;

typedef struct AudioDmaLists {
    AudioDmaBuffer *firstUsed;
    AudioDmaBuffer *firstFree;
} AudioDmaLists;

typedef struct AudioIoMesg {
    u8 pad00[0x18];
} AudioIoMesg;

extern void audio_dma_unlink(AudioDmaBuffer *node) __asm__("func_8011C150");
extern void audio_dma_link(AudioDmaBuffer *node, AudioDmaBuffer *after) __asm__("func_8011C180");
extern s32 osPiStartDma(AudioIoMesg *request, s32 priority, s32 direction, u32 devAddr, void *dramAddr, u32 size,
                        void *queue) __asm__("func_801185D0");
extern s32 osVirtualToPhysical(void *address) __asm__("func_80121F10");
extern u32 D_80125768;
extern s32 D_8012576C;
extern u8 D_801529D8;
extern AudioIoMesg D_80152BE8[];
extern AudioDmaLists D_80152F84;

s32 audio_dma_callback(s32 addr, s32 len) __asm__("func_8007A7E0");

s32 audio_dma_callback(s32 addr, s32 len) {
    void *foundBuffer;
    s32 delta;
    s32 addrEnd;
    s32 buffEnd;
    AudioDmaBuffer *dmaPtr;
    AudioDmaBuffer *lastDmaPtr;

    lastDmaPtr = 0;
    dmaPtr = D_80152F84.firstUsed;
    addrEnd = addr + len;
    while (dmaPtr != 0) {
        buffEnd = dmaPtr->startAddr + AUDIO_DMA_BUFFER_LENGTH;
        if (dmaPtr->startAddr > addr) {
            break;
        } else if (addrEnd <= buffEnd) {
            dmaPtr->lastFrame = D_80125768;
            foundBuffer = dmaPtr->ptr + addr - dmaPtr->startAddr;
            return osVirtualToPhysical(foundBuffer);
        }
        lastDmaPtr = dmaPtr;
        dmaPtr = dmaPtr->next;
    }
    dmaPtr = D_80152F84.firstFree;
    D_80152F84.firstFree = dmaPtr->next;
    audio_dma_unlink(dmaPtr);
    if (lastDmaPtr != 0) {
        audio_dma_link(dmaPtr, lastDmaPtr);
    } else if (D_80152F84.firstUsed != 0) {
        lastDmaPtr = D_80152F84.firstUsed;
        D_80152F84.firstUsed = dmaPtr;
        dmaPtr->next = lastDmaPtr;
        dmaPtr->prev = 0;
        lastDmaPtr->prev = dmaPtr;
    } else {
        D_80152F84.firstUsed = dmaPtr;
        dmaPtr->next = 0;
        dmaPtr->prev = 0;
    }
    foundBuffer = dmaPtr->ptr;
    delta = addr & 1;
    addr -= delta;
    dmaPtr->startAddr = addr;
    dmaPtr->lastFrame = D_80125768;
    osPiStartDma(&D_80152BE8[D_8012576C++], 0, 0, addr, foundBuffer, AUDIO_DMA_BUFFER_LENGTH, &D_801529D8);
    return osVirtualToPhysical(foundBuffer) + delta;
}
