#include "types.h"

typedef struct PakFilesystem {
    u8 bytes[0x68];
} PakFilesystem;

extern PakFilesystem gPakFilesystems[4] __asm__("D_802DF3A0");
extern u8 gPakLockQueue[] __asm__("D_802DF5B0");
extern void *gPakLockMessage __asm__("D_802E17A0");

extern s32 osRecvMesg(void *queue, void **message, s32 flags) __asm__("func_80119240");
extern s32 osSendMesg(void *queue, void *message, s32 flags) __asm__("func_801193E0");
extern s32 osPfsFreeBlocks(PakFilesystem *pfs, s32 *freeBytes) __asm__("func_80116A10");

s32 controller_pak_free_blocks(s32 channel, s32 *freeBytes) __asm__("func_800A9B70");

s32 controller_pak_free_blocks(s32 channel, s32 *freeBytes)
{
    s32 status;

    osRecvMesg(gPakLockQueue, &gPakLockMessage, 1);
    channel--;
    status = osPfsFreeBlocks(&gPakFilesystems[channel], freeBytes);
    osSendMesg(gPakLockQueue, &gPakLockMessage, 0);
    return status;
}
