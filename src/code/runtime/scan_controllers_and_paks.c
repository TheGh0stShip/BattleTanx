#include "types.h"

typedef struct ContStatus {
    u16 type;
    u8 status;
    u8 errnum;
} ContStatus;

typedef struct PakFilesystem {
    u8 bytes[0x68];
} PakFilesystem;

extern u8 gSerialQueue[] __asm__("D_802DF360");
extern ContStatus gContStatus[4] __asm__("D_802DF390");
extern PakFilesystem gPakFilesystems[4] __asm__("D_802DF3A0");
extern s32 gRumblePakChannels[4] __asm__("D_802DF540");
extern s32 gControllerPakChannels[4] __asm__("D_802DF550");
extern u8 gPakLockQueue[] __asm__("D_802DF5B0");
extern void *gPakLockMessage __asm__("D_802E17A0");
extern s32 gControllerChannels[4] __asm__("D_802E17A8");
extern s32 D_80126710;
extern s32 gControllerCount __asm__("D_80126714");

extern s32 osRecvMesg(void *queue, void **message, s32 flags) __asm__("func_80119240");
extern s32 osSendMesg(void *queue, void *message, s32 flags) __asm__("func_801193E0");
extern s32 osContStartQuery(void *queue) __asm__("func_80110CA0");
extern void osContGetQuery(ContStatus *status) __asm__("func_80110D24");
extern s32 osMotorInit(void *queue, PakFilesystem *pfs, s32 channel) __asm__("func_80113C40");
extern s32 osPfsInitPak(void *queue, PakFilesystem *pfs, s32 channel) __asm__("func_80116C70");

s32 scan_controllers_and_paks(void) __asm__("func_800A90E0");

s32 scan_controllers_and_paks(void)
{
    s32 i;
    s32 result;

    osRecvMesg(gPakLockQueue, &gPakLockMessage, 1);
    while (osRecvMesg(gSerialQueue, 0, 0) == 0) {
    }
    osContStartQuery(gSerialQueue);
    osRecvMesg(gSerialQueue, 0, 1);
    osContGetQuery(gContStatus);
    for (i = 0; i < 4; i++) {
        gRumblePakChannels[i] = -1;
        gControllerPakChannels[i] = -1;
        gControllerChannels[i] = -1;
    }
    gControllerCount = 0;
    for (i = 0; i < 4; i++) {
        if (!(gContStatus[i].errnum & 8) && (gContStatus[i].type & 4) && (gContStatus[i].type & 1)) {
            gControllerChannels[gControllerCount] = i;
            if (gContStatus[i].status & 1) {
                result = osPfsInitPak(gSerialQueue, &gPakFilesystems[i], i);
                if (result == 2) {
                    D_80126710 = result;
                }
                if (result == 10) {
                    if (osMotorInit(gSerialQueue, &gPakFilesystems[i], i) == 0) {
                        gRumblePakChannels[gControllerCount] = i;
                    } else {
                        gControllerPakChannels[gControllerCount] = i;
                    }
                } else if (result != 11) {
                    gControllerPakChannels[gControllerCount] = i;
                }
            }
            gControllerCount++;
        }
    }
    osSendMesg(gPakLockQueue, &gPakLockMessage, 0);
    return gControllerCount;
}
