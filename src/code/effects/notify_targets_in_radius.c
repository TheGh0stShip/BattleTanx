#include "types.h"

typedef struct NotifyTarget {
    u8 pad00[0x4];
    s32 serial;
    s32 handlerIndex;
} NotifyTarget;

typedef struct NotifyMessage {
    f32 x;
    f32 z;
    s32 radiusSq;
    s32 value;
} NotifyMessage;

typedef void (*NotifyHandler)(NotifyTarget *target, s32 arg1, s32 kind, NotifyMessage *message,
                              s32 arg4);

typedef struct NotifyHandlerEntry {
    NotifyHandler handle;
    u8 pad04[0x8];
} NotifyHandlerEntry;

typedef struct NotifyEntry {
    NotifyTarget *target;
    s32 serial;
    s32 distSq;
} NotifyEntry;

extern s32 D_802C13E4;
extern f32 D_802C13E8;
extern f32 D_802C13EC;
extern s32 D_802C13F0;
extern NotifyEntry D_802C13F8[];
extern s32 D_802C37FC;
extern NotifyHandlerEntry D_802C3804[];

void notify_targets_in_radius(s32 radius, s32 start) __asm__("func_8008C6F0");

void notify_targets_in_radius(s32 radius, s32 start)
{
    NotifyMessage message;
    NotifyTarget *pending;
    NotifyTarget *target;
    s32 radiusSq;
    s32 i;

    message.z = D_802C13EC;
    message.x = D_802C13E8;
    message.value = D_802C13F0;
    radiusSq = radius * radius;
    message.radiusSq = radiusSq;
    for (i = 0; i < D_802C37FC; i++) {
        if (D_802C13F8[i].distSq != -1) {
            break;
        }
        pending = D_802C13F8[i].target;
        if (pending->serial == D_802C13F8[i].serial) {
            if (D_802C3804[pending->handlerIndex].handle != 0) {
                D_802C3804[pending->handlerIndex].handle(pending, 0, 3, &message, 0);
            }
        }
    }
    for (; D_802C13E4 < D_802C37FC; D_802C13E4++) {
        if (radiusSq < D_802C13F8[D_802C13E4].distSq) {
            break;
        }
        target = D_802C13F8[D_802C13E4].target;
        if (target->serial == D_802C13F8[D_802C13E4].serial) {
            if (D_802C3804[target->handlerIndex].handle != 0) {
                D_802C3804[target->handlerIndex].handle(target, 0, 3, &message, 0);
            }
        }
    }
}
