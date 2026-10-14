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
extern void *gSerialMessages[] __asm__("D_802DF380");
extern ContStatus gContStatus[4] __asm__("D_802DF390");
extern PakFilesystem gPakFilesystems[4] __asm__("D_802DF3A0");
extern s32 gRumblePakChannels[4] __asm__("D_802DF540");
extern s32 gControllerPakChannels[4] __asm__("D_802DF550");
extern s32 D_802DF560[4];
extern s32 D_802DF570[4];
extern u8 gPakLockQueue[] __asm__("D_802DF5B0");
extern void *gPakLockMessages[] __asm__("D_802DF5C8");
extern u8 D_802DF5D0[];
extern void *D_802DF5E8[];
extern u8 gPakThread[] __asm__("D_802DF5F0");
extern void *gPakLockMessage __asm__("D_802E17A0");
extern s32 gControllerChannels[4] __asm__("D_802E17A8");
extern u8 D_802E17B8[];
extern u8 D_802E17D8[];
extern s32 D_8000030C;
extern s32 gControllerCount __asm__("D_80126714");

extern void create_message_queue(void *queue, void *messages, s32 count) __asm__("func_80111510");
extern void osCreateThread(void *thread, s32 id, void (*entry)(void *), void *arg, void *stack, s32 priority)
    __asm__("func_80111540");
extern void osStartThread(void *thread) __asm__("func_8011D1A0");
extern void osSetEventMesg(s32 event, void *queue, s32 message) __asm__("func_8011BA10");
extern u64 osGetTime(void) __asm__("func_801120A0");
extern s32 osContInit(void *queue, u8 *pattern, ContStatus *status) __asm__("func_80110FE0");
extern void bzero(void *buffer, s32 size) __asm__("func_80110C00");
extern s32 osRecvMesg(void *queue, void **message, s32 flags) __asm__("func_80119240");
extern s32 osSendMesg(void *queue, void *message, s32 flags) __asm__("func_801193E0");
extern s32 osMotorInit(void *queue, PakFilesystem *pfs, s32 channel) __asm__("func_80113C40");
extern s32 osPfsInitPak(void *queue, PakFilesystem *pfs, s32 channel) __asm__("func_80116C70");
extern void func_800A8C88(void *arg);

s32 init_controllers_and_paks(void) __asm__("func_800A8940");

s32 init_controllers_and_paks(void) {
    u8 pattern;
    s32 i;
    s32 result;

    create_message_queue(gPakLockQueue, gPakLockMessages, 1);
    create_message_queue(D_802DF5D0, D_802DF5E8, 2);
    osCreateThread(gPakThread, 5, func_800A8C88, 0, &gPakLockMessage, 0x10);
    osStartThread(gPakThread);
    create_message_queue(gSerialQueue, gSerialMessages, 4);
    osSetEventMesg(5, gSerialQueue, 1);
    if (D_8000030C != 0) {
        while (osGetTime() < 0x2000000) {
        }
    }
    osContInit(gSerialQueue, &pattern, gContStatus);
    bzero(D_802E17B8, 0x18);
    bzero(D_802E17D8, 0x18);
    for (i = 0; i < 4; i++) {
        gRumblePakChannels[i] = -1;
        D_802DF560[i] = 1;
        D_802DF570[i] = 0;
        gControllerPakChannels[i] = -1;
        gControllerChannels[i] = -1;
    }
    gControllerCount = 0;
    for (i = 0; i < 4; i++) {
        if (((pattern >> i) & 1) && !(gContStatus[i].errnum & 8) && (gContStatus[i].type & 4)
            && (gContStatus[i].type & 1)) {
            gControllerChannels[gControllerCount] = i;
            if (gContStatus[i].status & 1) {
                result = osPfsInitPak(gSerialQueue, &gPakFilesystems[i], i);
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
    while (osRecvMesg(gSerialQueue, 0, 0) == 0) {
    }
    osSendMesg(gPakLockQueue, &gPakLockMessage, 0);
    return gControllerCount;
}
