#include "types.h"

typedef struct RollingMine {
    u8 pad00[0xC];
    f32 z;
    f32 x;
    u8 pad14[0x2];
    u16 heading;
    u16 phase;
    u8 pad1A[0x6];
    s32 slotIndex;
    u8 pad24[0x4];
    s16 radius;
    u8 pad2A[0x2];
    u8 turn;
    u8 flags;
} RollingMine;

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
    u8 pad19[0x7];
} AreaContact;

typedef struct AreaResponse {
    u32 result;
    s32 value04;
    s32 value08;
    u16 angle;
} AreaResponse;

typedef struct BlastInfo {
    f32 z;
    f32 x;
    s32 value08;
    s32 value0C;
    s32 radius;
    s32 pad14;
} BlastInfo;

typedef struct ObjectHandlerEntry {
    s32 (*handler)(HitObject *object, void *source, s32 event, void *contact, void *response);
    u8 pad04[0x8];
} ObjectHandlerEntry;

typedef struct AreaBox {
    u8 data[0x18];
} AreaBox;

typedef struct RenderSlot {
    u8 pad00[0x8];
    u8 matrix[0x40];
    u8 pad48[0xA];
    s16 entryIndex;
    s16 displayValue;
    u8 pad56[0x2];
} RenderSlot;

typedef struct RenderEntry {
    u16 value;
    u16 baseDisplayValue;
} RenderEntry;

typedef struct RenderSession {
    u8 pad000[0x568];
    RenderSlot *slots;
    RenderEntry *entries;
} RenderSession;

typedef struct RenderOwner {
    u8 pad00[0xC];
    s32 z;
    s32 x;
    u8 pad14[0x2];
    u16 heading;
    u8 pad18[0x8];
    s32 slotIndex;
    u8 pad24[0x9];
    u8 flags;
} RenderOwner;

extern const AreaResponse D_80074C10;
extern ObjectHandlerEntry D_802C3804[];

extern f32 sinf_u16(u16 angle) __asm__("func_800F3AE0");
extern f32 cosf_u16(u16 angle) __asm__("func_800F3B40");
extern u16 func_800F3BA8(f32 value);
extern s32 radians_to_angle(f32 radians) __asm__("func_800F3BE4");
extern s32 find_segment_hit(PointZX *start, PointZX *end, s32 mode, SegmentHit *hit, s32 arg4) __asm__("func_8010874C");
extern void init_area_box(AreaBox *box, s32 x, s32 z, s32 a, s32 b, s32 c, s32 d, u16 angle) __asm__("func_80109268");
extern u8 find_objects_in_area(AreaBox *box, s32 capacity, void **results, s32 *count) __asm__("func_80107A14");
extern s32 start_sound_scaled_by_listener_distance(s32 soundId, f32 x, f32 z) __asm__("func_80085B4C");
extern RenderSession *get_render_session(void) __asm__("func_800821C0");
extern void matrix_identity(f32 matrix[4][4]) __asm__("func_800A7650");
extern void matrix_set_transform(f32 matrix[4][4], s32 x, s32 z, u16 heading) __asm__("func_800A76BC");
extern void guMtxF2L(f32 matrix[4][4], void *output) __asm__("func_801146A0");
extern f32 sqrtf(f32 x);

static inline void update_owner_slot_matrix(RenderOwner *owner)
{
    s16 displayValue;
    f32 matrix[4][4];
    RenderSession *session = get_render_session();
    RenderSlot *slot;
    s16 entryIndex;

    slot = &session->slots[owner->slotIndex];
    entryIndex = slot->entryIndex;
    if (entryIndex != -1) {
        u16 baseDisplayValue = ((RenderEntry *)((u32)session->entries + ((u32)entryIndex << 2)))->baseDisplayValue;
        u8 flags = owner->flags;

        if (flags & 1) {
            displayValue = baseDisplayValue + 3;
        } else {
            displayValue = baseDisplayValue + 1;
        }
        slot->displayValue = displayValue;
        matrix_identity(matrix);
        matrix_set_transform(matrix, owner->x, owner->z, owner->heading);
        guMtxF2L(matrix, slot->matrix);
    }
}

void update_rolling_mine(RollingMine *e, s32 *status) __asm__("func_800EF440");

void update_rolling_mine(RollingMine *e, s32 *status)
{
    SegmentHit hit;
    PointZX end;
    f32 reach;
    s32 blocked;
    s32 blocked2;
    s32 angle;
    s32 diff;

    e->phase += 0x800;
    reach = sinf_u16(e->phase) * e->radius;
    end.x = e->x + reach * sinf_u16(e->heading);
    blocked = 0;
    blocked2 = 0;
    end.z = e->z + reach * cosf_u16(e->heading);
    if (find_segment_hit((PointZX *)&e->z, &end, 8, &hit, -1)) {
        if ((u32)hit.object < 4) {
            blocked = 1;
        } else {
            AreaContact contact;
            AreaResponse response;

            response = D_80074C10;
            if (D_802C3804[hit.object->kind].handler != 0)
                D_802C3804[hit.object->kind].handler(hit.object, e, 0, &contact, &response);
            if (response.result == 0) {
                blocked = 1;
            }
        }
        if (blocked) {
            if (e->turn == 0) {
                if (hit.normalX < 0.0f) {
                    angle = -radians_to_angle(hit.normalZ);
                } else {
                    angle = radians_to_angle(hit.normalZ);
                }
                diff = e->heading - (angle | 0xFFFF0000);
                e->turn = (u16)(diff % 0x10000) > 0x8000 ? 1 : 2;
            }
            e->heading += (e->turn == 1) ? 0x400 : -0x400;
            end.x = e->x + reach * sinf_u16(e->heading);
            end.z = e->z + reach * cosf_u16(e->heading);
            if (find_segment_hit((PointZX *)&e->z, &end, 8, &hit, -1)) {
                if ((u32)hit.object < 4) {
                    blocked2 = 1;
                } else {
                    AreaContact contact2;
                    AreaResponse response2;

                    response2 = D_80074C10;
                    if (D_802C3804[hit.object->kind].handler != 0)
                        D_802C3804[hit.object->kind].handler(hit.object, e, 0, &contact2, &response2);
                    if (response2.result == 0) {
                        blocked2 = 1;
                    }
                }
                if (blocked2) {
                    f32 dx = hit.x - e->x;
                    f32 dz = hit.z - e->z;

                    e->phase = func_800F3BA8(sqrtf(dx * dx + dz * dz) / e->radius);
                }
            }
        }
    }
    if (e->phase >= 0x4000) {
        AreaBox box;
        void *results[18];
        BlastInfo blast;
        s32 count;
        s32 i;

        init_area_box(&box, e->x, e->z, -20, 20, 0, e->radius, e->heading);
        find_objects_in_area(&box, 0x200, results, &count);
        blast.value08 = 1;
        blast.value0C = -1;
        blast.x = e->x;
        blast.z = e->z;
        blast.radius = e->radius;
        for (i = 0; i < count; i++) {
            HitObject *object = results[i];

            if ((u32)object >= 4 && D_802C3804[object->kind].handler != 0) {
                D_802C3804[object->kind].handler(results[i], e, 7, &blast, 0);
            }
        }
        start_sound_scaled_by_listener_distance((e->flags & 1) ? 0x25 : 8, e->x, e->z);
        update_owner_slot_matrix((RenderOwner *)e);
        *status = 2;
        get_render_session()->slots[e->slotIndex].pad00[0] |= 0xF0;
    }
}
