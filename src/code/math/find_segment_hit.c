#include "types.h"

typedef struct RuntimeFlagRecord {
    u16 flags;
    s16 next;
    s16 prev;
    u8 pad06[2];
    s32 owner;
    u8 segment[0x12];
    u16 cellLinks[4];
    u8 pad26[2];
} RuntimeFlagRecord;

typedef struct SegmentHit {
    s32 owner;
    f32 y;
    f32 pad08;
    f32 x;
    f32 value10;
    f32 value14;
} SegmentHit;

extern u8 func_801095D0(f32 *from, f32 *to, void *segment, f32 *point, f32 *extra);
extern s32 D_80142B50[4];
extern s32 D_80142B60[4];
extern u16 D_803B75B0[4][20][20];
extern u16 D_803B8230;
extern s32 D_803B8238;
extern s32 D_803B823C;
extern RuntimeFlagRecord gRuntimeFlagRecords[] __asm__("D_803B8248");

s32 find_segment_hit(f32 *from, f32 *to, u16 mask, SegmentHit *hit, s32 ignore) __asm__("func_8010874C");

s32 find_segment_hit(f32 *from, f32 *to, u16 mask, SegmentHit *hit, s32 ignore)
{
    f32 point[2];
    f32 extra[2];
    f32 fromY;
    f32 fromX;
    f32 best;
    f32 dy;
    f32 dx;
    f32 ny;
    f32 nx;
    f32 stepY;
    f32 stepX;
    f32 distance;
    s32 found;
    s32 count;
    s32 step;
    s32 py;
    s32 px;
    s32 i;
    s32 row;
    s32 col;
    s16 cur;
    RuntimeFlagRecord *record;

    best = 3.4e38f;
    dx = to[0] - from[0];
    dy = to[1] - from[1];
    found = 0;
    fromY = from[1];
    fromX = from[0];
    if (dy < 0.0f) {
        ny = -dy / 1024.0f;
    } else {
        ny = dy / 1024.0f;
    }
    if (dx < 0.0f) {
        nx = -dx / 1024.0f;
    } else {
        nx = dx / 1024.0f;
    }
    ny = (ny < 1.0f) ? 1.0f : ny;
    nx = (nx < 1.0f) ? 1.0f : nx;
    stepX = 0.0f;
    stepY = 0.0f;
    if (nx <= ny) {
        count = ny;
        if (ny != 0.0f) {
            stepY = dy / ny;
            stepX = dx / ny;
            dy = stepY;
            dx = stepX;
        }
    } else {
        count = nx;
        if (nx != 0.0f) {
            stepY = dy / nx;
            stepX = dx / nx;
            dy = stepY;
            dx = stepX;
        }
    }
    ny = 2.0f;
    nx = dy / ny;
    ny = dx / ny;
    py = (s32)(from[1] + nx) + D_803B8238;
    px = (s32)(from[0] + ny) + D_803B823C;
    if (count >= 0) {
    step = 0;
    do {
        i = 0;
        do {
            if (i < 4) {
                row = (py + D_80142B50[i]) >> 11;
                col = (px + D_80142B60[i]) >> 11;
                if ((row >= 20) | (col >= 20)) {
                    continue;
                }
                if ((row < 0) | (col < 0)) {
                    continue;
                }
                cur = D_803B75B0[i][row][col];
            } else {
                cur = D_803B8230;
            }
            while (cur != -1) {
                record = &gRuntimeFlagRecords[cur];
                if ((record->flags & mask) && record->owner != ignore) {
                    if (func_801095D0(from, to, record->segment, point, extra)) {
                        found = 1;
                        distance = (fromY - point[1]) * (fromY - point[1]) +
                                   (fromX - point[0]) * (fromX - point[0]);
                        if (distance < best) {
                            hit->owner = record->owner;
                            hit->y = point[1];
                            hit->x = point[0];
                            hit->value14 = extra[1];
                            hit->value10 = extra[0];
                            best = distance;
                        }
                    }
                }
                cur = record->cellLinks[i & 3];
            }
        } while (++i < 5);
        py = (f32)py + stepY;
        px = (f32)px + stepX;
    } while (++step <= count);
    }
    return found;
}
