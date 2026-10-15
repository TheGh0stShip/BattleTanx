#include "types.h"

typedef struct RumblePakHandle {
    u8 pad00[0x68];
} RumblePakHandle;

typedef struct ControllerPad {
    u16 button;
    s8 stickX;
    s8 stickY;
    u8 errorNumber;
} ControllerPad;

typedef struct ControllerPads {
    ControllerPad pads[4];
} ControllerPads;

extern s32 osRecvMesg(void *queue, void *message, s32 flags) __asm__("func_80119240");
extern s32 osSendMesg(void *queue, void *message, s32 flags) __asm__("func_801193E0");
extern s32 osContStartReadData(void *queue) __asm__("func_80110D80");
extern void osContGetReadData(ControllerPads *pads) __asm__("func_80110E44");
extern s32 osMotorStop(RumblePakHandle *pfs) __asm__("func_801137F0");
extern s32 osMotorStart(RumblePakHandle *pfs) __asm__("func_80113958");

extern u8 gSiMessageQueue[] __asm__("D_802DF360");
extern RumblePakHandle gRumblePaks[4] __asm__("D_802DF3A0");
extern s32 gRumbleActive[4] __asm__("D_802DF570");
extern s32 gRumbleOnTime[4] __asm__("D_802DF580");
extern s32 gRumbleOffTime[4] __asm__("D_802DF590");
extern s32 gRumblePhase[4] __asm__("D_802DF5A0");
extern u8 gSiAccessQueue[] __asm__("D_802DF5B0");
extern u8 gControllerFrameQueue[] __asm__("D_802DF5D0");
extern u8 gSiAccessMessage[] __asm__("D_802E17A0");
extern ControllerPads gPreviousPads __asm__("D_802E17B8");
extern volatile s32 gControllerReadPending __asm__("D_802E17D0");
extern ControllerPads gCurrentPads __asm__("D_802E17D8");

void controller_rumble_thread(void *arg) __asm__("func_800A8C88");

void controller_rumble_thread(void *arg) {
    s32 i;

    for (;;) {
        osRecvMesg(gControllerFrameQueue, gSiAccessMessage, 1);
        osRecvMesg(gSiAccessQueue, gSiAccessMessage, 1);
        if (gControllerReadPending != 0) {
            osContStartReadData(gSiMessageQueue);
            osRecvMesg(gSiMessageQueue, 0, 1);
            gPreviousPads = gCurrentPads;
            osContGetReadData(&gCurrentPads);
            gControllerReadPending = 0;
        }
        for (i = 0; i < 4; i++) {
            if (gRumbleActive[i] != 0) {
                if (--gRumbleActive[i] != 0) {
                    if (gRumblePhase[i] > 0) {
                        if (--gRumblePhase[i] == 0) {
                            osMotorStop(&gRumblePaks[i]);
                            gRumblePhase[i] = gRumbleOffTime[i];
                        }
                    } else if (++gRumblePhase[i] == 0) {
                        osMotorStart(&gRumblePaks[i]);
                        gRumblePhase[i] = gRumbleOnTime[i];
                    }
                } else {
                    osMotorStop(&gRumblePaks[i]);
                }
            }
        }
        osSendMesg(gSiAccessQueue, gSiAccessMessage, 0);
    }
}
