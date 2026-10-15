#include "types.h"

#ifndef NULL
#define NULL 0
#endif

extern f32 D_80074480;
extern f32 D_80074484;
extern f32 D_80074488;
extern f32 D_8007448C;
extern f32 D_80074490;
extern f32 D_80074494;
extern f32 D_80074498;
extern f32 D_8007449C;
extern f32 D_800744A0;
extern f32 D_800744A4;
extern f32 D_800744A8;
extern f32 D_800744AC;

typedef struct SegmentWork {
    f32 hitX;
    f32 hitY;
    f32 firstMinY;
    f32 firstMaxY;
    f32 firstMinX;
    f32 firstMaxX;
    f32 secondMinY;
    f32 secondMaxY;
    f32 secondMinX;
    f32 secondMaxX;
} SegmentWork;

typedef struct Point2f {
    f32 x;
    f32 y;
} Point2f;

static inline s32 intersect_lines(Point2f *a0, Point2f *a1, Point2f *b0,
                                  Point2f *b1, Point2f *out)
{
    f32 dy;
    f32 slopeA;
    f32 slopeB;
    f32 interceptA;
    f32 interceptB;
    f32 y;
    Point2f *firstEnd;

    firstEnd = a1;
    dy = firstEnd->y - a0->y;
    if ((dy > 0.0f) ? (dy < D_80074494) : (-dy < D_80074498)) {
        slopeA = D_8007449C;
    } else {
        slopeA = (a1->x - a0->x) / dy;
    }
    dy = b1->y - b0->y;
    if ((dy > 0.0f) ? (dy < D_800744A0) : (-dy < D_800744A4)) {
        slopeB = D_800744A8;
    } else {
        slopeB = (b1->x - b0->x) / dy;
    }
    interceptA = a0->x - a0->y * slopeA;
    interceptB = b0->x - b0->y * slopeB;
    if (slopeA == slopeB) {
        if (interceptA == interceptB) {
            out->y = (a0->y + a1->y) / D_800744AC;
            out->x = (a0->x + a1->x) / D_800744AC;
            return 1;
        }
        return 0;
    }
    dy = slopeA - slopeB;
    y = 0.0f;
    if (dy != 0.0f) {
        y = (slopeA * y - interceptA) / dy;
    }
    out->y = y;
    out->x = slopeA * y + interceptA;
    return 1;
}

s32 intersect_bounded_segments_2d(Point2f *arg0, Point2f *arg1, Point2f *arg2,
                                  Point2f *arg3, Point2f *arg4, s16 *arg5)
    __asm__("func_800E1118");

s32 intersect_bounded_segments_2d(Point2f *arg0, Point2f *arg1, Point2f *arg2,
                                  Point2f *arg3, Point2f *arg4, s16 *arg5)
{
    SegmentWork work;
#define sp0 work.hitX
#define sp4 work.hitY
#define sp8 work.firstMinY
#define spC work.firstMaxY
#define sp10 work.firstMinX
#define sp14 work.firstMaxX
#define sp18 work.secondMinY
#define sp1C work.secondMaxY
#define sp20 work.secondMinX
#define sp24 work.secondMaxX
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f0_4;
    f32 temp_f0_5;
    f32 temp_f0_6;
    f32 temp_f0_7;
    f32 temp_f0_8;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f2_3;
    f32 temp_f2_4;
    f32 temp_f2_5;
    f32 temp_f2_6;
    f32 temp_f2_7;
    f32 temp_f2_8;
    s16 var_t0;
    s32 var_v0;
    s32 var_v1;
    s32 var_v1_2;
    s32 var_v1_3;
    s32 var_v1_4;

    temp_f2 = arg0->y;
    temp_f0 = arg1->y;
    var_t0 = 0;
    if (temp_f2 < temp_f0) {
        sp8 = temp_f2;
    } else {
        sp8 = temp_f0;
    }
    temp_f2_2 = arg0->x;
    temp_f0_2 = arg1->x;
    if (temp_f2_2 < temp_f0_2) {
        sp10 = temp_f2_2;
    } else {
        sp10 = temp_f0_2;
    }
    temp_f2_3 = arg0->y;
    temp_f0_3 = arg1->y;
    if (temp_f0_3 < temp_f2_3) {
        spC = temp_f2_3;
    } else {
        spC = temp_f0_3;
    }
    temp_f2_4 = arg0->x;
    temp_f0_4 = arg1->x;
    if (temp_f0_4 < temp_f2_4) {
        sp14 = temp_f2_4;
    } else {
        sp14 = temp_f0_4;
    }
    temp_f2_5 = arg2->y;
    temp_f0_5 = arg3->y;
    if (temp_f2_5 < temp_f0_5) {
        sp18 = temp_f2_5;
    } else {
        sp18 = temp_f0_5;
    }
    temp_f2_6 = arg2->x;
    temp_f0_6 = arg3->x;
    if (temp_f2_6 < temp_f0_6) {
        sp20 = temp_f2_6;
    } else {
        sp20 = temp_f0_6;
    }
    temp_f2_7 = arg2->y;
    temp_f0_7 = arg3->y;
    if (temp_f0_7 < temp_f2_7) {
        sp1C = temp_f2_7;
    } else {
        sp1C = temp_f0_7;
    }
    temp_f2_8 = arg2->x;
    temp_f0_8 = arg3->x;
    if (temp_f0_8 < temp_f2_8) {
        sp24 = temp_f2_8;
    } else {
        sp24 = temp_f0_8;
    }
    if (spC < (sp8 + D_80074480)) {
        sp8 -= D_80074484;
        spC += D_80074484;
    }
    if (sp14 < (sp10 + D_80074480)) {
        sp10 -= D_80074488;
        sp14 += D_80074488;
    }
    if (sp1C < (sp18 + D_80074480)) {
        sp18 -= D_8007448C;
        sp1C += D_8007448C;
    }
    if (sp24 < (sp20 + D_80074480)) {
        sp20 -= D_80074490;
        sp24 += D_80074490;
    }
    if (!intersect_lines(arg0, arg1, arg2, arg3, (Point2f *)&work)) {
        return 0;
    }
    var_v0 = 0;
    if ((sp8 <= sp4) && (sp4 <= spC) && (sp10 <= sp0) && (sp0 <= sp14) &&
        (sp18 <= sp4) && (sp4 <= sp1C) && (sp20 <= sp0) && (sp0 <= sp24)) {
        var_v0 = 1;
    }
    if (arg5 != NULL) {
        if (var_v0 != 0) {
            var_v1 = 0;
            if ((arg0->y == arg2->y) && (arg0->x == arg2->x)) {
                var_v1 = 1;
            }
            if (var_v1 != 0) {
                var_t0 += 1;
            }
            var_v1_2 = 0;
            if ((arg0->y == arg3->y) && (arg0->x == arg3->x)) {
                var_v1_2 = 1;
            }
            if (var_v1_2 != 0) {
                var_t0 += 1;
            }
            var_v1_3 = 0;
            if ((arg1->y == arg2->y) && (arg1->x == arg2->x)) {
                var_v1_3 = 1;
            }
            if (var_v1_3 != 0) {
                var_t0 += 1;
            }
            var_v1_4 = 0;
            if ((arg1->y == arg3->y) && (arg1->x == arg3->x)) {
                var_v1_4 = 1;
            }
            if (var_v1_4 != 0) {
                var_t0 += 1;
            }
        }
        *arg5 = var_t0;
    }
    if (arg4 != NULL) {
        arg4->y = sp4;
        arg4->x = sp0;
    }
    return var_v0;
}
