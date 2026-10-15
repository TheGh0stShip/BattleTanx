#include "types.h"

typedef struct EffectKind22 {
    u8 pad00[0xC];
    f32 x;
    f32 y;
    f32 z;
    f32 value18;
    f32 value1C;
    f32 value20;
    s32 value24;
    f32 range;
    s32 value2C;
    s16 heading;
    s16 value32;
    u8 value34;
    u8 value35;
    u8 value36;
    u8 value37;
    u8 value38;
} EffectKind22;

typedef struct PointZX {
    f32 z;
    f32 x;
} PointZX;

typedef struct SegmentHit {
    f32 value00;
    f32 x;
    f32 value08;
    f32 z;
    f32 value10;
    f32 value14;
} SegmentHit;

extern float sqrtf(float);
extern EffectKind22 *allocate_effect(s32 group, s32 kind, s32 size) __asm__("func_8008AD10");
extern f32 angle_sin(u16 angle) __asm__("func_800F3AE0");
extern f32 angle_cos(u16 angle) __asm__("func_800F3B40");
extern s32 find_segment_hit(PointZX *start, PointZX *end, s32 mode, SegmentHit *hit, s32 arg4) __asm__("func_8010874C");
extern f64 D_80071BB8;

s32 spawn_effect_kind_22(f32 *pos, f32 *target, f32 value20, s16 heading, u8 value38, u8 value37, u16 value34,
                         u16 value35, s32 value2C, u8 flag) __asm__("func_8008E29C");

s32 spawn_effect_kind_22(f32 *pos, f32 *target, f32 value20, s16 heading, u8 value38, u8 value37, u16 value34,
                         u16 value35, s32 value2C, u8 flag) {
    EffectKind22 *e;
    PointZX start;
    PointZX end;
    SegmentHit hit;
    f32 dx;
    f32 dz;
    f64 radius;

    e = allocate_effect(1, 0x22, 0x3C);
    if (e == 0) {
        return -1;
    }
    e->value36 = flag != 0;
    e->value34 = value34;
    e->value35 = value35;
    e->x = pos[0];
    e->y = pos[1];
    e->z = pos[2];
    e->value1C = target[1];
    e->value18 = target[0];
    e->value20 = value20;
    e->value37 = value37;
    e->heading = heading;
    e->value32 = 0x70;
    e->value38 = value38;
    e->value2C = value2C;
    radius = D_80071BB8;
    e->value24 = 0;
    e->range = 10000000.0f;
    start.x = pos[0];
    start.z = pos[2];
    end.x = pos[0] + angle_sin(heading) * radius;
    end.z = pos[2] + angle_cos(heading) * radius;
    if (find_segment_hit(&start, &end, 4, &hit, e->value2C) != 0) {
        dx = hit.x - start.x;
        dz = hit.z - start.z;
        e->range = sqrtf(dx * dx + dz * dz);
    }
    return 0;
}
