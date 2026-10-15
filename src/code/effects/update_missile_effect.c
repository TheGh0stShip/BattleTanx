#include "types.h"

typedef struct MissileEffect {
    u8 pad00[0xC];
    f32 x;
    f32 y;
    f32 z;
    f32 speed;
    u16 heading;
    u16 turn;
    s16 trail;
    s16 life;
    u8 active;
    u8 value25;
    u8 owner;
    u8 homing;
    u8 pad28[0x18];
    s32 ignore;
    s16 bursts;
    u8 wobble;
    u8 pad47;
} MissileEffect;

typedef struct HomingTarget {
    s8 steer;
    u8 pad01[0x7];
    u32 burstMask;
    u32 breakMask;
} HomingTarget;

typedef struct OwnerUnit {
    u8 pad000[0x60];
    MissileEffect *missile;
    u8 pad064[0x142];
    u8 value1A6;
    u8 pad1A7[0x19];
    u32 burstMask;
    u32 breakMask;
} OwnerUnit;

typedef struct PointZX {
    f32 z;
    f32 x;
} PointZX;

typedef struct HitObject {
    u8 pad00[0x8];
    s32 kind;
} HitObject;

typedef struct SegmentHit {
    HitObject *object;
    f32 x;
    f32 y;
    f32 z;
    f32 normalZ;
    f32 normalX;
} SegmentHit;

typedef struct AreaContact {
    f32 x;
    f32 y;
    f32 z;
    u16 angle;
    s32 value10;
    s32 owner;
    u8 value18;
} AreaContact;

typedef struct AreaResponse {
    u32 result;
    s32 value04;
    s32 value08;
    u16 angle;
} AreaResponse;

typedef struct ObjectHandlerEntry {
    void (*handler)(HitObject *object, MissileEffect *e, s32 arg2, AreaContact *contact, AreaResponse *response);
    u8 pad04[0x8];
} ObjectHandlerEntry;

typedef struct ModelGroupRef {
    u8 pad00[0x2];
    u16 group;
    u8 pad04[0x8];
} ModelGroupRef;

typedef struct ModelGroup {
    u8 count;
    u8 pad01;
    u16 first;
} ModelGroup;

typedef struct ModelPart {
    u32 frame;
    u32 part;
    u16 animation;
    u8 pad0A[0x2];
} ModelPart;

typedef struct ModelSession {
    u8 pad000[0x570];
    ModelGroupRef *refs;
    ModelGroup *groups;
    ModelPart *modelParts;
    u8 (*frames)[8];
    u8 (*parts)[8];
} ModelSession;

extern const AreaResponse D_80071AF0;
extern f32 D_801257B0;
extern ObjectHandlerEntry D_802C3804[];
extern s16 D_802D5A36;

extern void spawn_effect_kind_26(f32 *position, s32 variant) __asm__("func_800ED8C0");
extern s32 find_segment_hit(PointZX *start, PointZX *end, s32 mode, SegmentHit *hit, s32 arg4) __asm__("func_8010874C");
extern f32 random_float_range(f32 range) __asm__("func_800F3880");
extern ModelSession *func_800821C0(void);
extern void func_80093D50(f32 *pos, f32 normalX, f32 normalZ, HitObject *object, void *part);
extern OwnerUnit *func_800A6688(s32 owner);
extern void func_800A51E8(OwnerUnit *unit, s32 arg1, f32 arg2);
extern HomingTarget *func_80096784(s32 owner);
extern void func_800A4F44(OwnerUnit *unit);
extern f32 sinf_u16(u16 angle) __asm__("func_800F3AE0");
extern f32 cosf_u16(u16 angle) __asm__("func_800F3B40");
extern s32 start_sound_scaled_by_listener_distance(s32 soundId, f32 x, f32 z) __asm__("func_80085B4C");
extern s32 func_80085D84(f32 x, f32 z);
extern s32 func_800F0FD8(f32 *pos, u16 heading, s32 owner, s32 arg3, s32 arg4, s32 arg5, MissileEffect *e, s32 arg7);

static inline void *get_impact_model_part(void)
{
    ModelSession *session = func_800821C0();
    ModelGroupRef *ref = &session->refs[D_802D5A36];
    ModelGroup *group = &session->groups[ref->group];
    ModelPart *part = &session->modelParts[group->first];

    return session->parts[part->part];
}

void update_missile_effect(void *arg0, s32 *status) __asm__("func_8008D768");

void update_missile_effect(void *arg0, s32 *status)
{
    MissileEffect *e = arg0;
    SegmentHit hit;
    f32 trail[3];
    PointZX end;
    PointZX start;
    AreaContact contact;
    AreaResponse response;
    OwnerUnit *unit;
    HomingTarget *target;
    s32 impact;
    s32 sound;

    unit = func_800A6688(e->owner);
    impact = 0;
    sound = 1;
    if (--e->life > 0) {
        if (e->active != 0) {
            target = 0;
            if (e->homing != 0) {
                target = func_80096784(e->owner);
                if (target->breakMask & unit->breakMask) {
                    e->homing = 0;
                    if (unit->value1A6 == 0 && unit->missile == e) {
                        func_800A4F44(unit);
                    }
                } else {
                    e->heading -= (u32)(target->steer * 10 * D_801257B0);
                    e->turn = (u32)(-target->steer * 10 * D_801257B0);
                }
            }
            start.x = e->x;
            start.z = e->z;
            end.x = e->x + e->speed * sinf_u16(e->heading) * D_801257B0;
            end.z = e->z + e->speed * cosf_u16(e->heading) * D_801257B0;
            trail[0] = end.x;
            trail[1] = e->y;
            trail[2] = end.z;
            if (e->wobble != 0) {
                trail[0] += sinf_u16(e->heading) * -45.0f;
                trail[2] += cosf_u16(e->heading) * -45.0f;
            }
            if (e->trail != 0) {
                spawn_effect_kind_26(trail, e->trail);
            }
            if (find_segment_hit(&start, &end, 4, &hit, e->ignore)) {
                hit.y = e->y - 5.0f + random_float_range(10.0f);
                if ((u32)hit.object >= 4) {
                    response = D_80071AF0;
                    contact.x = hit.x;
                    contact.y = hit.y;
                    contact.z = hit.z;
                    contact.angle = e->heading;
                    contact.value10 = e->value25;
                    contact.owner = e->owner;
                    contact.value18 = 1;
                    if (D_802C3804[hit.object->kind].handler != 0) {
                        D_802C3804[hit.object->kind].handler(hit.object, e, 0, &contact, &response);
                    }
                    switch (response.result) {
                    case 0:
                    case 7:
                        impact = 1;
                        break;
                    case 6:
                        impact = 1;
                        sound = 0;
                        break;
                    case 2:
                        impact = 1;
                        func_80093D50(&hit.x, hit.normalX, hit.normalZ, hit.object, get_impact_model_part());
                        break;
                    }
                } else {
                    impact = 1;
                    if ((u32)hit.object != 1) {
                        func_80093D50(&hit.x, hit.normalX, hit.normalZ, 0, get_impact_model_part());
                    }
                    if ((u32)hit.object == 2) {
                        func_800A51E8(func_800A6688(e->owner), 0x25, 3.0f);
                    }
                }
            }
            if (impact) {
                e->life = 15;
                e->active = 0;
                if (sound) {
                    if ((u32)hit.object >= 4 && hit.object->kind == 0) {
                        start_sound_scaled_by_listener_distance(0xE, hit.x, hit.z);
                    } else {
                        start_sound_scaled_by_listener_distance(3, hit.x, hit.z);
                    }
                    spawn_effect_kind_26(&hit.x, 0xB);
                }
            } else if (!func_80085D84(end.x, end.z)) {
                spawn_effect_kind_26(&e->x, 0xB);
                *status = 2;
            } else {
                e->x = end.x;
                e->z = end.z;
            }
            if (e->homing != 0 && e->bursts > 0 && (target->burstMask & unit->burstMask)) {
                if (func_800F0FD8(&e->x, e->heading, e->owner, 0x12, e->value25, 5, e, 1) >= 0) {
                    start_sound_scaled_by_listener_distance(9, e->x, e->z);
                    e->bursts--;
                }
            }
        }
    } else {
        *status = 2;
    }
    if (*status == 2 && unit->value1A6 == 0 && unit->missile == e) {
        func_800A4F44(unit);
    }
}
