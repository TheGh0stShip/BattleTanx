#include "types.h"

typedef struct NotifyTarget {
    s16 next;
    u8 pad02[2];
    s32 serial;
    s32 handlerIndex;
    u8 pad0C[0x3C];
} NotifyTarget;

typedef struct NotifyReply {
    u8 kind;
    u8 pad01[3];
    f32 x;
    f32 z;
} NotifyReply;

typedef void (*NotifyHandler)(NotifyTarget *target, s32 arg1, s32 kind, s32 arg3, NotifyReply *reply);

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
extern f32 D_802C13E8[2];
extern s16 D_802C13F4;
extern NotifyEntry D_802C13F8[];
extern s32 D_802C37F8;
extern s32 D_802C37FC;
extern NotifyHandlerEntry D_802C3804[];
extern s16 D_802C3A28;
extern NotifyTarget D_802C3A30[];
extern u8 D_801259DC[][3];
extern void sort_notify_entries(NotifyEntry *entries, s32 count) __asm__("func_8008C09C");
extern void spawn_effect_kind_19(s32 a, s32 b, s32 c, s32 d, s32 e) __asm__("func_800F2E50");
extern s32 fade_owner_is_available(void) __asm__("func_800EC644");
extern s32 *get_game_mode(void) __asm__("func_8007AAF4");
extern void func_800F3014(s32 a, s32 b, s32 c, s32 d, s32 e, s32 f, s32 g, s32 h);

void begin_radius_notification(f32 *position, s32 radius) __asm__("func_8008C2EC");

void begin_radius_notification(f32 *position, s32 radius)
{
    NotifyReply reply;
    NotifyTarget *target;
    s32 id;
    f32 *center = &D_802C13E8[1];

    *center = position[0];
    D_802C37FC = 0;
    D_802C37F8 = 0;
    D_802C13E8[0] = position[2];
    {
        f32 *center;

        for (id = D_802C13F4; id != -1; id = target->next) {
            target = &D_802C3A30[id];
            reply.kind = 0;
            if (D_802C3804[target->handlerIndex].handle != 0) {
                D_802C3804[target->handlerIndex].handle(target, 0, 2, 0, &reply);
            }
            if (reply.kind != 0 && D_802C37FC != 0x300) {
                D_802C13F8[D_802C37FC].target = target;
                D_802C13F8[D_802C37FC].serial = target->serial;
                if (reply.kind == 2) {
                    D_802C13F8[D_802C37FC].distSq = -1;
                } else {
                    D_802C13F8[D_802C37FC].distSq =
                        ((s32)((&D_802C13E8[1])[0] - reply.z) *
                         (s32)((&D_802C13E8[1])[0] - reply.z)) +
                        ((s32)((&D_802C13E8[1])[-1] - reply.x) *
                         (s32)((&D_802C13E8[1])[-1] - reply.x));
                }
                D_802C37FC++;
            }
        }
    }
    {
        f32 *center = &D_802C13E8[1];

        for (id = D_802C3A28; id != -1; id = target->next) {
            target = &D_802C3A30[id];
            reply.kind = 0;
            if (D_802C3804[target->handlerIndex].handle != 0) {
                D_802C3804[target->handlerIndex].handle(target, 0, 2, 0, &reply);
            }
            if (reply.kind != 0 && D_802C37FC != 0x300) {
                D_802C13F8[D_802C37FC].target = target;
                D_802C13F8[D_802C37FC].serial = target->serial;
                if (reply.kind == 2) {
                    D_802C13F8[D_802C37FC].distSq = -1;
                } else {
                    D_802C13F8[D_802C37FC].distSq =
                        ((s32)((&D_802C13E8[1])[0] - reply.z) *
                         (s32)((&D_802C13E8[1])[0] - reply.z)) +
                        ((s32)((&D_802C13E8[1])[-1] - reply.x) *
                         (s32)((&D_802C13E8[1])[-1] - reply.x));
                }
                D_802C37FC++;
            }
        }
    }
    sort_notify_entries(D_802C13F8, D_802C37FC);
    for (D_802C13E4 = 0; D_802C13E4 < D_802C37FC; D_802C13E4++) {
        if (D_802C13F8[D_802C13E4].distSq != -1) {
            break;
        }
    }
    if (radius > 2000) {
        spawn_effect_kind_19(0xFF, 0xFF, 0xFF, 0xC, -1);
        if (fade_owner_is_available() == 0) {
            s32 mode = get_game_mode()[1];

            func_800F3014(0xE2, 0xDA, 0, D_801259DC[mode][0], D_801259DC[mode][1],
                          D_801259DC[mode][2], 0xF0, 0);
        }
    }
}
