#include "types.h"

typedef struct RuntimeFlagRecord {
    u16 flags;
    s16 next;
    s16 prev;
    u8 pad06[2];
    s32 owner;
    u8 segment[0x1C];
} RuntimeFlagRecord;

typedef struct SegmentHit {
    s32 owner;
    f32 y;
    f32 pad08;
    f32 x;
    f32 value10;
    f32 value14;
} SegmentHit;

extern u32 integer_sqrt(u32 value) __asm__("func_80109094");
extern u8 func_801095D0(f32 *from, f32 *to, void *segment, f32 *point, f32 *extra);
extern s32 D_803B8240;
extern RuntimeFlagRecord gRuntimeFlagRecords[] __asm__("D_803B8248");

static inline s32 square(s32 value) {
    return value * value;
}

s32 find_nearest_segment_hit(f32 *from, f32 *to, u16 mask, SegmentHit *hit, s32 ignore) __asm__("func_80108538");

s32 find_nearest_segment_hit(f32 *from, f32 *to, u16 mask, SegmentHit *hit, s32 ignore) {
    f32 point[2];
    f32 extra[2];
    f32 best;
    f32 distance;
    s32 found;
    s16 i;

    if (integer_sqrt(square(to[1] - from[1]) + square(to[0] - from[0])) == 0) {
        return 0;
    }
    best = 3.4e38f;
    found = 0;
    for (i = D_803B8240; i != -1; i = gRuntimeFlagRecords[i].next) {
        if (!(mask & gRuntimeFlagRecords[i].flags)) {
            continue;
        }
        if (gRuntimeFlagRecords[i].owner == ignore) {
            continue;
        }
        if (func_801095D0(from, to, gRuntimeFlagRecords[i].segment, point, extra)) {
            found = 1;
            distance = square(from[1] - point[1]) + square(from[0] - point[0]);
            if (distance < best) {
                hit->owner = gRuntimeFlagRecords[i].owner;
                hit->y = point[1];
                hit->x = point[0];
                hit->value14 = extra[1];
                hit->value10 = extra[0];
                best = distance;
            }
        }
    }
    return found;
}
