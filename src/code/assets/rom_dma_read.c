#include "types.h"

/* libultra PI DMA types (o32, big-endian). */
typedef void *OSMesg;

typedef struct OSMesgQueue {
    void *mtqueue;
    void *fullqueue;
    s32 validCount;
    s32 first;
    s32 msgCount;
    OSMesg *msg;
} OSMesgQueue;

typedef struct {
    u16 type;
    u8 pri;
    u8 status;
    OSMesgQueue *retQueue;
} OSIoMesgHdr;

typedef struct {
    OSIoMesgHdr hdr;
    void *dramAddr;
    u32 devAddr;
    u32 size;
    void *piHandle;
} OSIoMesg;

extern OSMesgQueue gRomDmaQueue __asm__("D_8014C0B0");

extern void bzero(void *buffer, s32 size) __asm__("func_80110C00");
extern void osInvalDCache(void *address, s32 size) __asm__("func_801124C0");
extern s32 osPiStartDma(OSIoMesg *request, s32 priority, s32 direction, u32 devAddr, void *dramAddr,
                        u32 size, OSMesgQueue *queue) __asm__("func_801185D0");
extern s32 osRecvMesg(OSMesgQueue *queue, OSMesg *message, s32 flags) __asm__("func_80119240");

void rom_dma_read(u32 romAddress, void *destination, u32 size) __asm__("func_80077930");

/* Synchronously copy size bytes of cartridge ROM into RDRAM. */
void rom_dma_read(u32 romAddress, void *destination, u32 size)
{
    OSIoMesg request;
    OSMesg message;

    if (size != 0) {
        bzero(&request, sizeof(request));
        bzero(&message, sizeof(message));
        osInvalDCache(destination, size);
        osPiStartDma(&request, 0, 0, romAddress, destination, size, &gRomDmaQueue);
        osRecvMesg(&gRomDmaQueue, 0, 1);
    }
}
