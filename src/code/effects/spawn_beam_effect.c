#include "types.h"

typedef struct BeamEffect {
    u8 pad00[0xC];
    f32 x;
    f32 y;
    f32 z;
    s16 heading;
    u8 pad1A[0x2];
    f32 length;
    f32 maxLength;
    s32 value24;
    u8 owner;
    u8 pad29[0x3];
} BeamEffect;

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
    void (*handler)(HitObject *object, void *source, s32 event, AreaContact *contact, AreaResponse *response);
    u8 pad04[0x8];
} ObjectHandlerEntry;

extern const AreaResponse D_80074DAC;
extern ObjectHandlerEntry D_802C3804[];

extern BeamEffect *allocate_effect(s32 group, s32 kind, s32 size) __asm__("func_8008AD10");
extern void *func_8008CED0(void);
extern void func_80093D50(f32 *pos, f32 normalX, f32 normalZ, HitObject *object, void *part);
extern void *func_800A6688(s32 owner);
extern void func_800A51E8(void *unit, s32 arg1, f32 arg2);
extern void spawn_effect_kind_26(f32 *position, s32 variant) __asm__("func_800ED8C0");
extern s32 spawn_effect_kind_0d(f32 *pos, u16 value18, u8 value1A, s16 value1C, s32 value20, s32 value24,
                                s32 value28, s32 value2C) __asm__("func_800F15A0");
extern u32 func_800F38F4(void);
extern f32 sinf_u16(u16 angle) __asm__("func_800F3AE0");
extern f32 cosf_u16(u16 angle) __asm__("func_800F3B40");
extern s32 radians_to_angle(f32 radians) __asm__("func_800F3BE4");
extern s32 find_segment_hit(PointZX *start, PointZX *end, s32 mode, SegmentHit *hit, s32 arg4) __asm__("func_8010874C");
extern f32 sqrtf(f32 x);

s32 spawn_beam_effect(f32 *pos, u16 heading, u8 owner, s16 kind, s32 arg4, s32 depth, s32 ignore, u8 arg7)
    __asm__("func_800F0FD8");

s32 spawn_beam_effect(f32 *pos, u16 heading, u8 owner, s16 kind, s32 arg4, s32 depth, s32 ignore, u8 arg7)
{
    PointZX start;
    PointZX end;
    SegmentHit hit;
    AreaContact contact;
    AreaResponse response;
    f32 spawn[3];
    AreaResponse *responsePtr;
    BeamEffect *e;
    s32 done;
    s32 angle;
    u16 a;
    s32 found;
    f32 dx;
    f32 dz;

    done = 0;
    if (depth <= 0 || (e = allocate_effect(1, 0xC, 0x2C)) == 0) {
        return -1;
    }
    e->heading = heading + 0x8000;
    e->owner = owner;
    e->value24 = -1;
    start.x = pos[0];
    start.z = pos[2];
    end.x = start.x + sinf_u16(heading) * 4000.0f;
    responsePtr = &response;
    end.z = start.z + cosf_u16(heading) * 4000.0f;
    do {
        found = find_segment_hit(&start, &end, 4, &hit, ignore);
        if (found != 0) {
            if ((u32)hit.object >= 4) {
            response = D_80074DAC;
            contact.x = hit.x;
            contact.y = pos[1];
            contact.z = hit.z;
            contact.angle = heading;
            contact.owner = owner;
            contact.value10 = arg4;
            contact.value18 = arg7;
            if (D_802C3804[hit.object->kind].handler != 0) {
                D_802C3804[hit.object->kind].handler(hit.object, e, 0, &contact, responsePtr);
            }
            switch (response.result) {
            case 1:
                start.x = hit.x + sinf_u16(heading);
                start.z = hit.z + cosf_u16(heading);
                found = 0;
                if ((start.x - end.x) * (start.x - end.x) + (start.z - end.z) * (start.z - end.z) < 100.0f) {
                    do {
                        done = 1;
                    } while (0);
                }
                break;
            case 0:
                goto miss;
            case 2:
                hit.y = pos[1];
                done = 1;
                func_80093D50(&hit.x, hit.normalX, hit.normalZ, hit.object, func_8008CED0());
                break;
            case 7:
                spawn[1] = pos[1];
                spawn[0] = hit.x + sinf_u16(response.angle);
                spawn[2] = hit.z + cosf_u16(response.angle);
                spawn_beam_effect(spawn, response.angle, 0xFF, kind, arg4, depth - 1, -1, arg7);
                found = 0;
                done = 1;
                end.x = hit.x;
                end.z = hit.z;
                break;
            }
        } else {
            done = 1;
            hit.y = pos[1];
            if ((u32)hit.object != 1) {
                func_80093D50(&hit.x, hit.normalX, hit.normalZ, hit.object, func_8008CED0());
            }
            if ((u32)hit.object == 2) {
                func_800A51E8(func_800A6688(e->owner), 0x25, 3.0f);
            }
            }
        } else {
        miss:
            done = 1;
        }
    } while (done == 0);
    if (found != 0) {
        hit.y = pos[1];
        spawn_effect_kind_26(&hit.x, kind);
        if (kind == 8) {
            e->value24 = 0xB;
        }
        end.x = hit.x;
        end.z = hit.z;
        if (depth > 16) {
            if (hit.normalX < 0.0f) {
                angle = -radians_to_angle(hit.normalZ);
            } else {
                angle = radians_to_angle(hit.normalZ);
            }
            a = angle + (func_800F38F4() & 0x1FFF) - 0x1000;
            contact.y = pos[1];
            contact.x = hit.x + sinf_u16(a);
            contact.z = hit.z + cosf_u16(a);
            spawn_effect_kind_0d(&contact.x, a, owner, kind, arg4, depth - 1, ignore, func_800F38F4() % 3);
            a = angle + (func_800F38F4() & 0xFFF) - 0x800;
            contact.x = hit.x + sinf_u16(a);
            contact.z = hit.z + cosf_u16(a);
            spawn_effect_kind_0d(&contact.x, a, owner, kind, arg4, depth - 1, ignore, func_800F38F4() % 3);
        }
    }
    dx = end.x - pos[0];
    dz = end.z - pos[2];
    e->length = e->maxLength = sqrtf(dx * dx + dz * dz);
    e->x = end.x;
    e->y = pos[1];
    e->z = end.z;
    return 0;
}
