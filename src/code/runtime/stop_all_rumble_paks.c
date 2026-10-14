#include "types.h"

typedef struct RumblePakHandle {
    u8 pad00[0x68];
} RumblePakHandle;

extern s32 osRecvMesg(void *queue, void *message, s32 flags) __asm__("func_80119240");
extern s32 osSendMesg(void *queue, void *message, s32 flags) __asm__("func_801193E0");
extern s32 osMotorInit(void *queue, RumblePakHandle *pfs, s32 channel) __asm__("func_80113C40");
extern s32 osMotorStop(RumblePakHandle *pfs) __asm__("func_801137F0");

extern u8 gSiMessageQueue[] __asm__("D_802DF360");
extern RumblePakHandle gRumblePaks[4] __asm__("D_802DF3A0");
extern s32 gControllerStatus[] __asm__("D_802DF540");
extern s32 gRumbleActive[4] __asm__("D_802DF570");
extern u8 gSiAccessQueue[] __asm__("D_802DF5B0");
extern u8 gSiAccessMessage[] __asm__("D_802E17A0");

void stop_all_rumble_paks(void) __asm__("func_800A9010");

void stop_all_rumble_paks(void) {
    s32 i;

    osRecvMesg(gSiAccessQueue, gSiAccessMessage, 1);
    for (i = 0; i < 4; i++) {
        if (gControllerStatus[i] != -1) {
            gRumbleActive[i] = 0;
            osMotorInit(gSiMessageQueue, &gRumblePaks[i], i);
            osMotorStop(&gRumblePaks[i]);
        }
    }
    osSendMesg(gSiAccessQueue, gSiAccessMessage, 0);
}
