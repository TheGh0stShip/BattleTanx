#include "types.h"

typedef struct SegmentPoint {
    f32 x;
    f32 z;
} SegmentPoint;

typedef struct SegmentMember {
    u8 pad000[0x4D0];
    SegmentPoint origin;
    SegmentPoint direction;
    f32 length;
} SegmentMember;

extern f32 D_800746C4;

extern f32 func_800E1A20(s32 query, SegmentPoint *point);

s32 ai_point_near_member_segment(SegmentMember *member, s32 query) __asm__("func_800E6CA4");

s32 ai_point_near_member_segment(SegmentMember *member, s32 query)
{
    SegmentPoint start;
    SegmentPoint end;
    f32 distance;

    start.z = member->origin.z;
    start.x = member->origin.x;
    end.z = start.z + member->direction.z * member->length;
    end.x = start.x + member->direction.x * member->length;
    distance = func_800E1A20(query, &start);
    return distance + func_800E1A20(query, &end) < member->length * D_800746C4;
}
