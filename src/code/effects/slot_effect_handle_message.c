#include "types.h"

typedef struct SlotPoint {
    u8 flags;
    u8 pad01[0x57];
} SlotPoint;

typedef struct SlotSession {
    u8 pad000[0x568];
    SlotPoint *points;
} SlotSession;

typedef struct SlotPosition {
    f32 x;
    f32 z;
} SlotPosition;

typedef struct SlotReport {
    u8 active;
    u8 pad01[3];
    f32 x;
    f32 z;
} SlotReport;

typedef struct SlotEffect {
    u8 pad00[0xC];
    f32 x;
    f32 z;
    u8 pad14[2];
    s16 heading;
    u16 released;
    u8 pad1A[2];
    s32 resource;
    s32 slot;
} SlotEffect;

extern f32 sqrtf(f32 value);
extern SlotSession *get_spawn_session(void) __asm__("func_800821C0");
extern s32 radians_to_angle(f32 radians) __asm__("func_800F3BE4");
extern void release_effect(SlotEffect *effect) __asm__("func_8008B89C");
extern void release_effect_resource(s32 resource) __asm__("func_80107170");
extern void start_slot_effect(SlotEffect *effect, s32 arg1, SlotPosition *position)
    __asm__("func_800EFAD8");
extern void settle_slot_effect(SlotEffect *effect, s32 arg1, SlotPosition *position)
    __asm__("func_800EFE4C");

void slot_effect_handle_message(SlotEffect *effect, s32 arg1, u32 message,
                                SlotPosition *position, SlotReport *report)
    __asm__("func_800EFFC8");

void slot_effect_handle_message(SlotEffect *effect, s32 arg1, u32 message,
                                SlotPosition *position, SlotReport *report)
{
    SlotSession *session;
    f32 dz;
    f32 dx;

    switch (message) {
    case 0:
        start_slot_effect(effect, arg1, position);
        break;
    case 2:
        if (effect->released == 0) {
            report->active = 1;
            report->z = effect->z;
            report->x = effect->x;
        }
        break;
    case 3:
        if (effect->released == 0) {
            session = get_spawn_session();
            release_effect(effect);
            effect->released = 1;
            dz = position->z - effect->z;
            dx = position->x - effect->x;
            if ((dz != 0.0f) | (dx != 0.0f)) {
                if (-dz < 0.0f) {
                    effect->heading = -radians_to_angle(-dx / sqrtf(dz * dz + dx * dx));
                } else {
                    effect->heading = radians_to_angle(-dx / sqrtf(dz * dz + dx * dx));
                }
            } else {
                effect->heading = 0;
            }
            session->points[effect->slot].flags &= 0xF;
            if (effect->resource >= 0) {
                release_effect_resource(effect->resource);
                effect->resource = -1;
            }
        }
        break;
    case 7:
        settle_slot_effect(effect, arg1, position);
        break;
    }
}
