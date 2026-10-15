#include "types.h"

typedef struct BulletEffect {
    u8 pad00[0xC];
    f32 x;
    f32 y;
    f32 z;
    f32 vz;
    f32 vx;
    f32 speed;
    f32 travelled;
    f32 range;
    s32 ignore;
    u16 angle;
    s16 life;
    u8 kind;
    u8 trail;
    u8 flags;
    u8 value37;
    u8 owner;
} BulletEffect;

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
    void (*handler)(HitObject *object, BulletEffect *e, s32 arg2, AreaContact *contact, AreaResponse *response);
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
extern s32 D_80125CD0[];
extern ObjectHandlerEntry D_802C3804[];
extern s16 D_802D5A36;

extern void spawn_effect_kind_26(f32 *position, s32 variant) __asm__("func_800ED8C0");
extern s32 find_segment_hit(PointZX *start, PointZX *end, s32 mode, SegmentHit *hit, s32 arg4) __asm__("func_8010874C");
extern f32 random_float_range(f32 range) __asm__("func_800F3880");
extern ModelSession *func_800821C0(void);
extern void func_80093D50(f32 *pos, f32 normalX, f32 normalZ, HitObject *object, void *part);
extern void *func_800A6688(s32 owner);
extern void func_800A51E8(void *unit, s32 arg1, f32 arg2);
extern f32 sinf_u16(u16 angle) __asm__("func_800F3AE0");
extern f32 cosf_u16(u16 angle) __asm__("func_800F3B40");
extern u32 func_800F38F4(void);
extern s32 start_sound_scaled_by_listener_distance(s32 soundId, f32 x, f32 z) __asm__("func_80085B4C");
extern s32 func_80085D84(f32 x, f32 z);
extern BulletEffect *allocate_effect(s32 group, s32 kind, s32 arg2) __asm__("func_8008AD10");
extern f32 sqrtf(f32 x);

static inline void *get_impact_model_part(void)
{
    ModelSession *session = func_800821C0();
    ModelGroupRef *ref = &session->refs[D_802D5A36];
    ModelGroup *group = &session->groups[ref->group];
    ModelPart *part = &session->modelParts[group->first];

    return session->parts[part->part];
}

void update_bullet_effect(void *arg0, s32 *status) __asm__("func_8008E480");

void update_bullet_effect(void *arg0, s32 *status)
{
    BulletEffect *e = arg0;
    SegmentHit hit;
    f32 trail[3];
    PointZX end;
    PointZX start;
    AreaContact contact;
    AreaResponse response;
    f32 splitPos[3];
    f32 splitVel[2];
    PointZX probeStart;
    PointZX probeEnd;
    SegmentHit probeHit;
    BulletEffect *split;
    s32 impact;
    s32 sound;
    f32 scale;

    impact = 0;
    sound = 1;
    if (--e->life > 0) {
        scale = D_801257B0;
        start.x = e->x;
        start.z = e->z;
        end.x = e->x + e->vx * scale;
        end.z = e->z + e->vz * scale;
        e->travelled += e->speed * scale;
        if (e->kind != 1) {
            trail[0] = end.x;
            trail[1] = e->y;
            trail[2] = end.z;
            if (e->trail != 0) {
                spawn_effect_kind_26(trail, e->trail);
            }
        }
        if (find_segment_hit(&start, &end, (e->travelled > e->range) ? 4 : 0x400, &hit, e->ignore)) {
            hit.y = e->y - 5.0f + random_float_range(10.0f);
            if ((u32)hit.object >= 4) {
                response = D_80071AF0;
                contact.x = hit.x;
                contact.y = hit.y;
                contact.z = hit.z;
                contact.angle = e->angle;
                contact.value10 = e->value37;
                contact.owner = e->owner;
                contact.value18 = e->flags & 1;
                if (D_802C3804[hit.object->kind].handler != 0) {
                    D_802C3804[hit.object->kind].handler(hit.object, e, 0, &contact, &response);
                }
                switch (response.result) {
                case 0:
                    impact = 1;
                    break;
                case 6:
                    impact = 1;
                    sound = 0;
                    break;
                case 2:
                    impact = 1;
                    if (e->kind != 1) {
                        func_80093D50(&hit.x, hit.normalX, hit.normalZ, hit.object, get_impact_model_part());
                    }
                    break;
                case 7: {
                    u16 angle;
                    s32 ignore;
                    u8 kind;
                    u8 trailKind;
                    f32 speed;
                    u8 value37;
                    u8 owner;

                    splitPos[0] = hit.x;
                    splitPos[1] = e->y;
                    splitPos[2] = hit.z;
                    splitVel[1] = e->speed * sinf_u16(response.angle);
                    splitVel[0] = e->speed * cosf_u16(response.angle);
                    angle = response.angle;
                    ignore = (s32)hit.object;
                    kind = e->kind;
                    trailKind = e->trail;
                    speed = e->speed;
                    value37 = e->value37;
                    owner = 0xFF;
                    split = allocate_effect(1, 0x22, 0x3C);
                    if (split != 0) {
                        split->flags = 0;
                        split->kind = kind;
                        split->trail = trailKind;
                        split->x = splitPos[0];
                        split->y = splitPos[1];
                        split->z = splitPos[2];
                        split->vx = splitVel[1];
                        split->vz = splitVel[0];
                        split->speed = speed;
                        split->value37 = value37;
                        split->angle = angle;
                        split->life = 0x70;
                        split->owner = owner;
                        split->ignore = ignore;
                        split->travelled = 0.0f;
                        split->range = 10000000.0f;
                        probeStart.x = splitPos[0];
                        probeStart.z = splitPos[2];
                        probeEnd.x = splitPos[0] + sinf_u16(angle) * 10000.0;
                        probeEnd.z = splitPos[2] + cosf_u16(angle) * 10000.0;
                        if (find_segment_hit(&probeStart, &probeEnd, 4, &probeHit, split->ignore)) {
                            split->range = sqrtf((probeHit.x - probeStart.x) * (probeHit.x - probeStart.x) +
                                                 (probeHit.z - probeStart.z) * (probeHit.z - probeStart.z));
                        }
                    }
                    *status = 2;
                    return;
                }
                }
            } else {
                impact = 1;
                if (e->kind != 1 && (u32)hit.object != 1) {
                    func_80093D50(&hit.x, hit.normalX, hit.normalZ, 0, get_impact_model_part());
                }
                if ((u32)hit.object == 2) {
                    func_800A51E8(func_800A6688(e->owner), 0x25, 3.0f);
                }
            }
        }
        if (impact) {
            *status = 2;
            if (sound) {
                if (e->kind == 1) {
                    start_sound_scaled_by_listener_distance(D_80125CD0[func_800F38F4() & 3], hit.x, hit.z);
                } else if ((u32)hit.object >= 4 && hit.object->kind == 0) {
                    start_sound_scaled_by_listener_distance(0xE, hit.x, hit.z);
                } else {
                    start_sound_scaled_by_listener_distance(3, hit.x, hit.z);
                }
                switch (e->kind) {
                case 0:
                    hit.x -= e->vx * 35.0f / e->speed;
                    hit.z -= e->vz * 35.0f / e->speed;
                    spawn_effect_kind_26(&hit.x, 0xB);
                    break;
                case 2:
                    spawn_effect_kind_26(&hit.x, 9);
                    break;
                case 1:
                    if ((u32)hit.object < 3 || hit.object->kind != 0) {
                        hit.x -= e->vx * 35.0f / e->speed;
                        hit.z -= e->vz * 35.0f / e->speed;
                    }
                    spawn_effect_kind_26(&hit.x, 0x17);
                    break;
                }
            }
        } else {
            e->x = end.x;
            e->z = end.z;
            if (!func_80085D84(end.x, end.z)) {
                *status = 2;
            }
        }
    } else {
        *status = 2;
    }
}
