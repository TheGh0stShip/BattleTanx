#include "types.h"

typedef struct BoundsRecord {
    u8 pad00[0xC];
    u16 flags;
    s16 x;
    s16 y;
    s16 minX;
    s16 maxX;
    s16 minY;
    s16 maxY;
    u8 pad1A[0x2];
    u16 angle;
    u8 pad1E[0xA];
} BoundsRecord;

typedef struct BoundsCorner {
    f32 y;
    f32 x;
} BoundsCorner;

extern f32 angle_sin(u16 angle) __asm__("func_800F3AE0");
extern f32 angle_cos(u16 angle) __asm__("func_800F3B40");
extern BoundsRecord D_803B8248[];

void get_record_bounds_corners(s32 index, BoundsCorner *corners) __asm__("func_80107754");

void get_record_bounds_corners(s32 index, BoundsCorner *corners) {
    BoundsRecord *record;
    f32 x;
    f32 y;
    f32 sine;
    f32 cosine;

    if (index == -1) {
        return;
    }
    record = &D_803B8248[index];
    x = record->x;
    y = record->y;
    if (record->flags & 1) {
        goto unrotated;
    }
    if (record->flags & 2) {
        goto unrotated;
    }
    if (record->flags & 4) {
        goto unrotated;
    }
    if (record->flags & 8) {
    unrotated:
        corners[0].x = record->minX + x;
        corners[0].y = record->minY + y;
        corners[1].x = record->minX + x;
        corners[1].y = record->maxY + y;
        corners[2].x = record->maxX + x;
        corners[2].y = record->maxY + y;
        corners[3].x = record->maxX + x;
        corners[3].y = record->minY + y;
        return;
    }
    sine = -angle_sin(record->angle);
    cosine = angle_cos(record->angle);
    corners[0].x = cosine * record->minX - sine * record->minY + x;
    corners[0].y = sine * record->minX + cosine * record->minY + y;
    corners[1].x = cosine * record->minX - sine * record->maxY + x;
    corners[1].y = sine * record->minX + cosine * record->maxY + y;
    corners[2].x = cosine * record->maxX - sine * record->maxY + x;
    corners[2].y = sine * record->maxX + cosine * record->maxY + y;
    corners[3].x = cosine * record->maxX - sine * record->minY + x;
    corners[3].y = sine * record->maxX + cosine * record->minY + y;
}
